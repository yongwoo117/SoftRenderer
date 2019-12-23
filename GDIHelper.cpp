
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"

// ����
ULONG g_CurrentColor;
BYTE *g_pBits;

HDC	hScreenDC, hMemoryDC;
HBITMAP hDefaultBitmap, hDIBitmap;

// �Լ�

void BufferSwap()
{
	BitBlt(hScreenDC, 0, 0, g_nClientWidth, g_nClientHeight, hMemoryDC, 0, 0, SRCCOPY);
}

void SetColor(BYTE r, BYTE g, BYTE b)
{
	g_CurrentColor = RGB(b, g, r);
}

void Clear()
{
	ULONG* dest = (ULONG*)g_pBits;
	DWORD bytecount = g_nClientWidth * g_nClientHeight * sizeof(ULONG);
	ULONG value = g_CurrentColor;
	bytecount /= 4;
	while (bytecount--)
	{
		*dest++ = value;
	}
	return;
}

void InitGDI(HWND hWnd)
{
	hScreenDC = GetDC(hWnd);
	hMemoryDC = CreateCompatibleDC(hScreenDC);

	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(BITMAPINFO));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = g_nClientWidth;
	bmi.bmiHeader.biHeight = -g_nClientHeight;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;

	hDIBitmap = CreateDIBSection(hMemoryDC, &bmi, DIB_RGB_COLORS, (void**)&g_pBits, NULL, 0);
	hDefaultBitmap = (HBITMAP)SelectObject(hMemoryDC, hDIBitmap);

	g_bIsActive = TRUE;
}

void ReleaseGDI(HWND hWnd)
{
	g_bIsActive = FALSE;

	DeleteObject(hDefaultBitmap);
	DeleteObject(hDIBitmap);
	ReleaseDC(hWnd, hScreenDC);
	ReleaseDC(hWnd, hMemoryDC);
}


