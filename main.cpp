#include <iostream>
#include <chrono>
#include <vector>
#include "window.h"
using namespace std;

int rectX{ 50 }, rectY{ 50 }, rectWidth{ 150 }, rectHeight{ 100 }, speed{ 5 };

int mapWidth{ 16 }, mapHeight{ 16 };

wstring map;

float playerRow{ 8.0f };
float playerCol{ 8.0f };
float playerAngle{ 0.0f };

float depth{ 16.0f };
float FOV{ 3.14159 / 4.0 };

int main()
{

	cout << "Creating Window...\n";

	Window* pWindow = new Window();

	bool running = true;

	map += L"################";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"################";

	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	int wWidth = pWindow->GetWindowWidth();
	int wHeight = pWindow->GetWindowHeight();
	HWND wHwnd = pWindow->GetWindowHandle();

	vector<uint32_t> backBuffer(wWidth * wHeight, RGB(0, 0, 0));

	fill(backBuffer.begin(), backBuffer.end(), RGB(0, 0, 0));

	while (running)
	{

		if (!pWindow->ProcessMessages())
		{
			cout << "Closing Window\n";
			running = false;
		}

		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();

		if (GetAsyncKeyState('A') & 0x8000)
			playerAngle -= 0.5f * fElapsedTime;

		if (GetAsyncKeyState('D') & 0x8000)
			playerAngle += 0.5f * fElapsedTime;

		if (GetAsyncKeyState('W') & 0x8000)
		{

			playerRow += sinf(playerAngle) * 5.0f * fElapsedTime;
			playerCol += cosf(playerAngle) * 5.0f * fElapsedTime;

		}

		if (GetAsyncKeyState('S') & 0x8000)
		{

			playerRow -= sinf(playerAngle) * 5.0f * fElapsedTime;
			playerCol -= cosf(playerAngle) * 5.0f * fElapsedTime;

		}

		for (int i = 0; i < wWidth; i++)
		{

			bool hitWall = false;

			float rayAngle = (playerAngle - FOV / 2.0f) + (float(i) / float(wWidth)) * FOV;

			float distanceToWall = 0.0f;

			float eyeRow = sinf(rayAngle);
			float eyeCol = cosf(rayAngle);

			while (!hitWall && distanceToWall < depth)
			{

				distanceToWall += 0.1f;

				int testRow = (int)(playerRow + eyeRow * distanceToWall);
				int testCol = (int)(playerCol + eyeCol * distanceToWall);

				if (testRow < 0 || testRow > mapWidth || testCol < 0 || testCol > mapHeight)
				{

					hitWall = true;
					distanceToWall = depth;

				}

				else 
				{
					if (map[testCol * mapWidth + testRow] == '#')
					{
						hitWall = true;
					}
				}

			}

			int ceilling = (float)(wHeight / 2.0f) - wHeight / ((float)distanceToWall);
			int floor = wHeight - ceilling;

			for (int y = 0; y < wHeight; y++)
			{

				if (y < ceilling)
				{
					backBuffer[y * wWidth + i] = RGB(0, 0, 0);
				}
				else if (y >= ceilling && y <= floor)
				{
					backBuffer[y * wWidth + i] = RGB(128, 128, 128);
				}
				else
				{
					backBuffer[y * wWidth + i] = RGB(0, 0, 0);
				}

			}
		
			HDC hdc = GetDC(wHwnd);
			BITMAPINFO bmi = { 0 };
			bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bmi.bmiHeader.biWidth = wWidth;
			bmi.bmiHeader.biHeight = -wHeight;
			bmi.bmiHeader.biPlanes = 1;
			bmi.bmiHeader.biBitCount = 32;
			bmi.bmiHeader.biCompression = BI_RGB;

			StretchDIBits(hdc, 0, 0, wWidth, wHeight, 0, 0, wWidth, wHeight, backBuffer.data(), &bmi, DIB_RGB_COLORS, SRCCOPY);

			ReleaseDC(wHwnd, hdc);

		}

	}

	delete pWindow;

	return 0;

}
