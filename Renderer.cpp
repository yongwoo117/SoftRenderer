
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"
#include "LinearFunction.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);

inline int CoordinateTransformX(int X)
{
	return X - g_nClientWidth / 2;
}
inline int CoordinateTransformY(int Y)
{
	return -Y + g_nClientHeight / 2;
}

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(int x, int y)
{
	if (!IsInRange(x, y)) return;

	ULONG* dest = (ULONG*)g_pBits;
	DWORD offset = g_nClientWidth * g_nClientHeight / 2 + g_nClientWidth / 2 + x + g_nClientWidth * -y;
	*(dest + offset) = g_CurrentColor;
}

void DrawTriangle(const Point& P1, const Point &P2, const Point &P3)
{
	Point min_size, max_size;
	LinearFunction Lines[] = { LinearFunction(P1,P2),LinearFunction(P2,P3),LinearFunction(P3,P1) };
	double Distances[] = { Point::getLength(P1,P2),Point::getLength(P2,P3),Point::getLength(P3,P1) };
	double Area = (Lines[0].getLength(P3) * Distances[0] / 2);
	Point MiddlePoint((P1.x + P2.x + P3.x) / 3, (P1.y + P2.y + P3.y) / 3);
	const bool Password[] = { Lines[0].isHigher(MiddlePoint),Lines[1].isHigher(MiddlePoint),Lines[2].isHigher(MiddlePoint) };

	min_size.x = min(P1.x, P2.x);
	min_size.x = min(min_size.x, P3.x);
	max_size.x = max(P1.x, P2.x);
	max_size.x = max(min_size.x, P3.x);

	min_size.y = min(P1.y, P2.y);
	min_size.y = min(min_size.y, P3.y);
	max_size.y = max(P1.y, P2.y);
	max_size.y = max(min_size.y, P3.y);

	int pixel_x;
	int pixel_y;
	int index;
	for (pixel_x = (int)round(min_size.x); pixel_x <= max_size.x; pixel_x++)
	{
		for (pixel_y = (int)round(min_size.y); pixel_y <= max_size.y; pixel_y++)
		{
			for (index = 0; index < 3; index++)
			{
				if (Password[index] != Lines[index].isHigher(pixel_x, pixel_y))
					break;
			}
			if (index == 3)
			{
				if (pixel_x == 320 && pixel_y == 200)
				{
					index = 3;
				}
				Point currentPoint(pixel_x, pixel_y);
				SetColor(RGB(
					255 * (Lines[2].getLength(currentPoint) * Distances[0] / 2) / Area,
					255 * (Lines[1].getLength(currentPoint) * Distances[1] / 2) / Area,
					255 * (Lines[0].getLength(currentPoint) * Distances[0] / 2) / Area));
				PutPixel(CoordinateTransformX(pixel_x), CoordinateTransformY(pixel_y));
			}
		}
	}
}

void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(0, 0, 0);
	Clear();

	// Draw
	DrawTriangle(
		Point(000,380),
		Point(420,000),
		Point(640,480)
	);

	// Buffer Swap 
	BufferSwap();
}
