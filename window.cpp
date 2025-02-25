#include "window.h"

int WIDTH{ 640 }, HEIGHT{ 480 };

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) 
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window()
	: hInstance(GetModuleHandle(nullptr))
{
	const wchar_t* CLASS_NAME = L"Ray Caster";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;
	wndClass.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));

	RegisterClass(&wndClass);

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + WIDTH;
	rect.bottom = rect.top + HEIGHT;

	AdjustWindowRect(&rect, style, false);

	hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"RayCaster",
		style,
		rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, SW_SHOW);

}

Window::~Window() 
{
	const wchar_t* CLASS_NAME = L"Ray Caster";

	UnregisterClass(CLASS_NAME, hInstance);
}

bool Window::ProcessMessages() 
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
	{
		if (msg.message == WM_QUIT) {
			
			return false;

		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

int Window::GetWindowWidth()
{

	return WIDTH;

}

int Window::GetWindowHeight()
{

	return HEIGHT;

}