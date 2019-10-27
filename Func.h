#pragma once
#include "Point.h"

class Func
{
private:
	double A;
	double B;
	Point Limit1;
	Point Limit2;

public:
	Func(Point, Point);
	Func() {}
	bool isHigher(Point);
};
