#pragma once

struct Point
{
	double x, y;
};

class LinearFunction
{
private:
	double m_slope, m_intercept;
public:
	LinearFunction(double slope, double intercept) :m_slope(slope), m_intercept(intercept) {}
	LinearFunction(const Point& point1, const Point& point2);
	double operator()(double x);
	double operator()(int x);
	static double GetLength(const Point& point1, const Point& point2);
};