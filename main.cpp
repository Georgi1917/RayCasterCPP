#include <iostream>
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

	while (running)
	{
		if (!pWindow->ProcessMessages())
		{
			cout << "Closing Window\n";
			running = false;
		}

		int wWidth = pWindow->GetWindowWidth();
		int wHeight = pWindow->GetWindowHeight();
		HWND wHwnd = pWindow->GetWindowHandle();

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

			HDC hdc = GetDC(wHwnd);

			for (int y = 0; y < wHeight; y++)
			{

				if (y < ceilling)
				{
					SetPixel(hdc, i, y, RGB(0, 0, 0));
				}
				else if (y >= ceilling && y <= floor)
				{
					SetPixel(hdc, i, y, RGB(128, 128, 128));
				}
				else
				{
					SetPixel(hdc, i, y, RGB(0, 0, 0));
				}

			}
		
			ReleaseDC(wHwnd, hdc);

		}

		Sleep(16);

	}

	delete pWindow;

	return 0;

}
