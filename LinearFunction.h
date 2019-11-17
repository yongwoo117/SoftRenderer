#pragma once

struct Point
{
	double x, y;
	Point() { x = y = 0; }
	Point(double X, double Y) :x(X), y(Y) {}
	double getLength(const Point& point);
	static double getLength(const Point& point1, const Point& point2);
};

class LinearFunction
{
private:
	double m_slope, m_intercept;
	bool m_isVertical;
public:
	LinearFunction(const Point& point1, const Point& point2);
	double operator()(double x) const;
	double operator()(int x) const;
	Point getCrossPoint(const LinearFunction& Func) const;
	double getLength(const Point& point) const;
	bool isHigher(const Point& point) const;
	bool isHigher(double x, double y) const;
};