#include "Vector2.h"

Vector2::Vector2() { }

Vector2::Vector2(double x, double y) : _x(x), _y(y) {}

void Vector2::changeVector(double x, double y)
{
	_x = x;
	_y = y;
}

void Vector2::setX(double x)
{
	_x = x;
}

void Vector2::setY(double y)
{
	_y = y;
}

double Vector2::getX()
{
	return _x;
}

double Vector2::getY()
{
	return _y;
}
