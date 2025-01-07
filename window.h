#pragma once

#include <Windows.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	Window();
	~Window();

	bool ProcessMessages();
	HWND GetWindowHandle() const { return hWnd; };
private:
	HINSTANCE hInstance;
	HWND hWnd;
};