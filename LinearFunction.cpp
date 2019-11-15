#include "stdafx.h"
#include "LinearFunction.h"
#include <cmath>
#include <limits>
using namespace std;

LinearFunction::LinearFunction(const Point& point1, const Point& point2)
{
	if (point1.x - point2.x == 0)
	{
		m_slope = DBL_MAX;
		m_intercept = point1.x;
	}
	else
	{
		m_slope = (point2.y - point1.y) / (point2.x - point1.x);
		m_intercept = point1.y - m_slope * point1.x;
	}
}

double LinearFunction::operator()(double x) const
{
	if (m_slope == DBL_MAX)
		return (x > m_slope) ? DBL_MAX : -DBL_MAX;
	return m_slope * x + m_intercept;
}

double LinearFunction::operator()(int x) const
{
	if (m_slope == DBL_MAX)
		return (x > m_slope) ? DBL_MAX : -DBL_MAX;
	return m_slope * x + m_intercept;
}

double LinearFunction::GetLength(const Point& point1, const Point& point2)
{
	return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

Point LinearFunction::getCrossPoint(const LinearFunction & Func)
{
	if (m_slope == DBL_MAX)
		return Point(m_intercept, Func(m_intercept));
	else if (Func.m_slope == DBL_MAX)
		return Point(Func.m_intercept, (*this)(Func.m_intercept));
	double x = (Func.m_intercept - m_intercept) / (m_slope - Func.m_slope);
	return Point(x, (*this)(x));
}

bool LinearFunction::isHigher(const Point & point)
{
	return ((*this)(point.x) > point.y);
}

bool LinearFunction::isHigher(double x, double y)
{
	return ((*this)(x) > y);
}
