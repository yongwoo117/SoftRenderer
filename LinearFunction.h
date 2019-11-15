#pragma once

struct Point
{
	double x, y;
	Point() { x = y = 0; }
	Point(double X, double Y) :x(X), y(Y) {}
};

class LinearFunction
{
private:
	double m_slope, m_intercept;
public:
	LinearFunction(double slope, double intercept) :m_slope(slope), m_intercept(intercept) {}
	LinearFunction(const Point& point1, const Point& point2);
	double operator()(double x) const;
	double operator()(int x) const;
	static double GetLength(const Point& point1, const Point& point2);
	Point getCrossPoint(const LinearFunction& Func);
	bool isHigher(const Point& point);
	bool isHigher(double x, double y);
};