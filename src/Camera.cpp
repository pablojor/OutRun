#include "Camera.h"

#include <math.h>
#include <iostream>

Vector3 Camera::position;
int Camera::width;
int Camera::height;
double Camera::ratio;
double Camera::angle;
double Camera::d;
double Camera::pi;
double Camera::velocity;

// Initialize camera parameters
void Camera::Init(Vector3 pos, int w, int h, double a, double vel)
{
	position = pos;
	width = w;
	height = h;
	ratio = (double)width / (double)height;
	angle = a;
	pi = 3.14159265359;
	velocity = vel;
	
	d = 1.0 / tan((angle / 2.0) * (pi / 180.0));
}

// Transforms spatial 3D position coordinates to 2D render coordinates
Vector2 Camera::toViewport(Vector3 pos)
{
	Vector2 posReal;

	if (position.getZ() >= pos.getZ())
		return Vector2(-1, -1);

	double z = ((pos.getZ() - position.getZ()) / d);

	double y = (pos.getY() - position.getY()) / z;
	double yPixel = height - ((y + 1) * (height / 2));

	double x = (pos.getX() - position.getX()) / z;
	double xPixel = (x + ratio) * height / 2;

	posReal = Vector2(xPixel, yPixel);
	
	return posReal;
}

// Moves the camera along the Z axis and returns it
// to its origin once a threshold has been reached
void Camera::moveCamera(double deltaTime)
{
	position.setZ(position.getZ() + velocity * deltaTime);
}

// GETTERS AND SETTERS
Vector3 Camera::getPosition()
{
	return position;
}

void Camera::setPosition(Vector3 newPos)
{
	position = newPos;
}
