
#include "stdafx.h"
#include "Func.h"

Func::Func(Point P1, Point P2)
{
	A = ((P2.GetY() - (double)P1.GetY()) / ((double)P2.GetX() - P1.GetX()));
	B = P1.GetY() - A * P1.GetX();
	Limit1 = P1;
	Limit2 = P2;
}

bool Func::isHigher(Point input)
{
	if (input.GetY() > A * input.GetX() + B)
		return true;
	else
		return false;
}
