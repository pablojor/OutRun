#pragma once

class Vector2 {
private:
	double _x;
	double _y;

public:
	Vector2();
	Vector2(double x, double y);

	void changeVector(double x, double y);

	void setX(double x);
	void setY(double y);

	double getX();
	double getY();
};