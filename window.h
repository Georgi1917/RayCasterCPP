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
	int GetWindowWidth();
	int GetWindowHeight();
private:
	HINSTANCE hInstance;
	HWND hWnd;
};