#include "stdafx.h"
#include "LinearFunction.h"
#include <cmath>
#include <limits>
#include <stdexcept>
using namespace std;

double Point::getLength(const Point& point)
{
	return sqrt(pow(x - point.x, 2) + pow(y - point.y, 2));
}

double Point::getLength(const Point& point1, const Point& point2)
{
	return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

LinearFunction::LinearFunction(const Point& point1, const Point& point2)
{
	if (point1.x - point2.x == 0) // x=n 그래프인 경우
	{
		m_slope = DBL_MAX;
		m_intercept = point1.x;
		m_isVertical = true;
	}
	else
	{
		m_slope = (point2.y - point1.y) / (point2.x - point1.x);
		m_intercept = point1.y - m_slope * point1.x;
		m_isVertical = false;
	}
}

double LinearFunction::operator()(double x) const
{
	if (m_isVertical)
		throw invalid_argument("x=n 식에서 y를 구하려 했습니다.");
	return m_slope * x + m_intercept;
}

double LinearFunction::operator()(int x) const
{
	if (m_isVertical)
		throw invalid_argument("x=n 식에서 y를 구하려 했습니다.");
	return m_slope * x + m_intercept;
}

Point LinearFunction::getCrossPoint(const LinearFunction & Func) const
{
	if (m_isVertical)
		return Point(m_intercept, Func(m_intercept));
	else if (Func.m_isVertical)
		return Point(Func.m_intercept, (*this)(Func.m_intercept));
	double x = (Func.m_intercept - m_intercept) / (m_slope - Func.m_slope);
	return Point(x, (*this)(x));
}

double LinearFunction::getLength(const Point& point) const
{
	if (m_isVertical)
		return abs(m_intercept - point.x);
	
	LinearFunction temp;
	temp.m_slope = -1 / m_slope;
	temp.m_intercept = point.y - temp.m_slope * point.x;
	return Point::getLength(getCrossPoint(temp), point);
}

bool LinearFunction::isHigher(const Point & point) const
{
	if (m_isVertical)
		return point.x > m_intercept;
	return ((*this)(point.x) > point.y);
}

bool LinearFunction::isHigher(double x, double y) const
{
	if (m_isVertical)
		return x > m_intercept;
	return ((*this)(x) > y);
}
