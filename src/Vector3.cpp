#include "Vector3.h"

Vector3::Vector3()
{
}

Vector3::Vector3(double x, double y, double z) : _x(x), _y(y), _z(z) {}

void Vector3::changeVector(double x, double y, double z)
{
	_x = x;
	_y = y;
	_z = z;
}

void Vector3::setX(double x)
{
	_x = x;
}

void Vector3::setY(double y)
{
	_y = y;
}

void Vector3::setZ(double z)
{
	_z = z;
}

double Vector3::getX()
{
	return _x;
}

double Vector3::getY()
{
	return _y;
}

double Vector3::getZ()
{
	return _z;
}
