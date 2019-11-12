
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
	Point MiddlePoint((P1.x + P2.x + P3.x) / 3, (P1.y, P2.y, P3.y) / 3);
	const bool Password[] = { Lines[0].isHigher(MiddlePoint),Lines[1].isHigher(MiddlePoint),Lines[2].isHigher(MiddlePoint) };

	min_size.x = round(min(P1.x, P2.x));
	min_size.x = round(min(min_size.x, P3.x));
	max_size.x = round(max(P1.x, P2.x));
	max_size.x = round(max(min_size.x, P3.x));

	min_size.y = round(min(P1.y, P2.y));
	min_size.y = round(min(min_size.y, P3.y));
	max_size.y = round(max(P1.y, P2.y));
	max_size.y = round(max(min_size.y, P3.y));

	int pixel_x;
	int pixel_y;
	int index;
	for (pixel_x = min_size.x; pixel_x <= max_size.x; pixel_x++)
	{
		for (pixel_y = min_size.y; pixel_y <= max_size.y; pixel_y++)
		{
			for (index = 0; index < 3; index++)
			{
				if (Password[index] != Lines[index].isHigher(pixel_x, pixel_y))
					break;
			}
			if (index == 3)
			{
				Point currentPoint(pixel_x, pixel_y);
				LinearFunction *RGBvalueCheck[3] = { 
					&LinearFunction(P1,currentPoint),
					&LinearFunction(P2,currentPoint),
					&LinearFunction(P3,currentPoint) };
				Point CrossPoint[3] = { 
					RGBvalueCheck[0]->getCrossPoint(Lines[1]),
					RGBvalueCheck[1]->getCrossPoint(Lines[2]),
					RGBvalueCheck[2]->getCrossPoint(Lines[0]) };
				SetColor(RGB(
					255 * (1-(LinearFunction::GetLength(P3, currentPoint) / LinearFunction::GetLength(P3, CrossPoint[2]))),
					255 * (1-(LinearFunction::GetLength(P2, currentPoint) / LinearFunction::GetLength(P2, CrossPoint[1]))),
					255 * (1-(LinearFunction::GetLength(P1, currentPoint) / LinearFunction::GetLength(P1, CrossPoint[0])))));
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
	DrawTriangle(Point(300,0),Point(100,400),Point(600,470));

	// Buffer Swap 
	BufferSwap();
}
