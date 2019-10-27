#pragma once
class Point
{
private:
	int X;
	int Y;
public:
	Point(int x, int y) :X(x), Y(y) {}
	Point() {}

	int GetX() { return X; }
	int GetY() { return Y; }
	void SetX(int x) { X = x; }
	void SetY(int y) { Y = y; }
};

