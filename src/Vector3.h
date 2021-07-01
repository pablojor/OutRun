#pragma once

class Vector3 {
private:
	double _x;
	double _y;
	double _z;

public:
	Vector3();
	Vector3(double x, double y, double z);

	void changeVector(double x, double y, double z);

	void setX(double x);
	void setY(double y);
	void setZ(double z);

	double getX();
	double getY();
	double getZ();
};