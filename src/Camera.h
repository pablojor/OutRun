#pragma once
#include "Vector3.h"
#include "Vector2.h"

class Camera {
private:
	static Vector3 position;
	static int width, height;
	static double ratio;
	static double angle;
	static double d;
	static double pi;
	static double velocity;

public:
	// Initialize camera parameters
	static void Init(Vector3 pos, int w, int h, double angle, double velocity);

	// Transforms spatial 3D position coordinates to 2D render coordinates
	static Vector2 toViewport(Vector3 pos);

	// Moves the camera along the Z axis and returns it
	// to its origin once a threshold has been reached
	static void moveCamera(double deltaTime);

	// Getters
	static Vector3 getPosition();

	// Setters
	static void setPosition(Vector3 newPos);
};