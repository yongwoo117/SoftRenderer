
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"
#include "Func.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);

int CoordinateTransformX(int X)
{
	return X - g_nClientWidth / 2;
}
int CoordinateTransformY(int Y)
{
	return -Y + g_nClientHeight / 2;
}

//Goals에 동적할당하여 넘기십시오. 함수 내부에서 Goals를 delete[]합니다.
void DrawShape(Point Goals[], int length, COLORREF rgb)
{
	//도형 파악
	Func* Funcs = new Func[length];
	for (int i = 0; i < length - 1; i++)
	{
		Funcs[i] = Func(Goals[i], Goals[i + 1]); // 각 변의 직선의 방정식 구하기
	}
	Funcs[length - 1] = Func(Goals[length - 1], Goals[0]);
	//무게 중심 구하기
	//무게중심은 항상 도형 내부에 있으므로 무게중심과 각 직선의 방정식과의 관계를 구한다
	Point Middle(0, 0);
	for (int i = 0; i < length; i++)
	{
		Middle.SetX(Middle.GetX() + Goals[i].GetX());
		Middle.SetY(Middle.GetY() + Goals[i].GetY());
	}
	Middle.SetX(Middle.GetX() / length);
	Middle.SetY(Middle.GetY() / length);
	//무게중심과 각 직선의 방정식과의 관계를 저장할 배열
	bool* Password = new bool[length];
	//도형을 둘러싸는 가장 작은 직사각형 생성
	int MaxX = 0;
	int MaxY = 0;
	int MinX = Goals[0].GetX();
	int MinY = Goals[0].GetY();
	for (int i = 0; i < length; i++)
	{
		if (MaxX < Goals[i].GetX())
			MaxX = Goals[i].GetX();
		else if (MinX > Goals[i].GetX())
			MinX = Goals[i].GetX();

		if (MaxY < Goals[i].GetY())
			MaxY = Goals[i].GetY();
		else if (MinY > Goals[i].GetY())
			MinY = Goals[i].GetY();

		Password[i] = Funcs[i].isHigher(Middle); // 무게중심과 각 변의 직선의 방정식과의 관계 구하기
	}

	//채색
	SetColor(rgb);
	for (int X = MinX; X < MaxX; X++)
	{
		for (int Y = MinY; Y < MaxY; Y++)
		{
			for (int i = 0; i < length; i++)
			{
				// 해당픽셀이 무게중심처럼 각 직선의 방정식 내부에 있는지 검사
				if (Password[i] == Funcs[i].isHigher(Point(X, Y)))
				{
					if (i == length - 1)
						PutPixel(CoordinateTransformX(X), CoordinateTransformY(Y));
				}
				else
				{
					break;
				}
			}
		}
	}
	delete[] Goals;
	delete[] Funcs;
	delete[] Password;
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


void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	// Draw
	SetColor(255, 0, 0);
	PutPixel(0, 0);
	DrawShape(new Point[3]{ Point(15,106), Point(23,120), Point(1,119) }, 3, RGB(41, 41, 41));
	DrawShape(new Point[5]{ Point(16,56),Point(28,63),Point(28,83), Point(23,120),Point(15,106) }, 5, RGB(94, 93, 91));
	DrawShape(new Point[3]{ Point(28,42),Point(28,63),Point(16,56) }, 3, RGB(151, 152, 154));
	DrawShape(new Point[6]{ Point(28,42),Point(53,33),Point(80,42),Point(111,92),Point(48,213),Point(28,83) }, 6, RGB(41, 42, 44));
	DrawShape(new Point[3]{ Point(59,192),Point(90,213),Point(48,213) }, 3, RGB(94, 93, 91));
	DrawShape(new Point[3]{ Point(80,42),Point(147,24),Point(111,92) }, 3, RGB(155, 156, 158));
	DrawShape(new Point[4]{ Point(147,24),Point(174,136),Point(127,149),Point(100,114) }, 4, RGB(94, 93, 91));
	DrawShape(new Point[3]{ Point(100,114),Point(127,149),Point(86,141) }, 3, RGB(155, 156, 158));
	DrawShape(new Point[5]{ Point(147,24),Point(216,1),Point(246,24),Point(210,213),Point(186,188) }, 5, RGB(41, 42, 44));
	DrawShape(new Point[3]{ Point(214,190),Point(249,213),Point(210,213) }, 3, RGB(94, 92, 93));
	DrawShape(new Point[3]{ Point(246,24),Point(283,68),Point(225,136) }, 3, RGB(94, 90, 87));
	DrawShape(new Point[3]{ Point(243,115),Point(283,68),Point(243,159) }, 3, RGB(40, 40, 40));
	DrawShape(new Point[3]{ Point(283,68),Point(294,108),Point(243,159) }, 3, RGB(94, 93, 91));
	DrawShape(new Point[3]{ Point(283,68),Point(304,60),Point(294,108) }, 3, RGB(46, 47, 49));
	DrawShape(new Point[3]{ Point(300,82),Point(316,75),Point(294,108) }, 3, RGB(157, 158, 160));
	DrawShape(new Point[5]{ Point(294,108),Point(327,126),Point(328,176),Point(297,193),Point(243,159) }, 5, RGB(94, 93, 91));
	DrawShape(new Point[3]{ Point(327,126),Point(353,120),Point(327,140) }, 3, RGB(41, 42, 44));
	DrawShape(new Point[3]{ Point(328,145),Point(395,117),Point(328,176) }, 3, RGB(41, 42, 44));

	// Buffer Swap 
	BufferSwap();
}
