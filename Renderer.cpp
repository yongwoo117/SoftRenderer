
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

//P1은 왼쪽 위의 점이고, P2는 오른쪽 아래의 점이어야 합니다.
void DrawUV(const Point& P1, const Point& P2)
{
	for (int Y = P1.y; Y < P2.y; Y++)
	{
		for (int X = P1.x; X < P2.x; X++)
		{
			SetColor(
				255 * (1 - (X - P2.x) / (P1.x - P2.x)),
				255 * (Y - P2.y) / (P1.y - P2.y),
				0
			);
			PutPixel(CoordinateTransformX(X), CoordinateTransformY(Y));
		}
	}
}

void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(0, 0, 0);
	Clear();

	// Draw
	DrawUV(Point(0, 0), Point(480, 480));

	// Buffer Swap 
	BufferSwap();
}
