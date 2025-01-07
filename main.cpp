#include <iostream>
#include "window.h"
using namespace std;

int rectX{ 50 }, rectY{ 50 }, rectWidth{ 150 }, rectHeight{ 100 }, speed{ 5 };

int main()
{

	cout << "Creating Window...\n";

	Window* pWindow = new Window();

	bool running = true;

	while (running)
	{
		if (!pWindow->ProcessMessages())
		{
			cout << "Closing Window\n";
			running = false;
		}

		if (GetAsyncKeyState('A') & 0x8000)
		{
			if (!(rectX <= 0)) rectX -= speed;
		}

		if (GetAsyncKeyState('W') & 0x8000)
		{
			if (!(rectY <= 0)) rectY -= speed;
		}

		if (GetAsyncKeyState('S') & 0x8000)
		{
			if (!(rectY + rectHeight >= 480)) rectY += speed;
		}

		if (GetAsyncKeyState('D') & 0x8000)
		{
			if (!(rectX + rectWidth >= 640)) rectX += speed;
		}

		HDC hdc = GetDC(pWindow->GetWindowHandle());

		HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
		RECT clearRect = { 0, 0, 640, 480 };
		FillRect(hdc, &clearRect, blackBrush);
		DeleteObject(blackBrush);

		HBRUSH rectBrush = CreateSolidBrush(RGB(128, 128, 128));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, rectBrush);

		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, hPen);

		Rectangle(hdc, rectX, rectY, rectX + rectWidth, rectY + rectHeight);

		SelectObject(hdc, oldBrush);
		DeleteObject(rectBrush);

		SelectObject(hdc, oldPen);
		DeleteObject(hPen);

		ReleaseDC(pWindow->GetWindowHandle(), hdc);

		Sleep(16);

	}

	delete pWindow;

	return 0;

}
