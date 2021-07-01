#pragma once

#include "Vector3.h"
#include "Vector2.h"
#include "Image/Image.h"
#include "Input/Event.h"

class RenderCommand;
class Segment;

class Car {
private:

	Vector3 _pos;
	int _width, _height;
	double _aspectRatio;

	// ---- Values to move the car
	Vector2 _dir; // (x, z)

	double _velocity;
	double _maxVelocity;
	double _grassMaxVelocity;

	double _aceleration;
	double _deceleration;
	double _realAceleration;

	double _friction;
	double _grassFriction;
	double _realFriction;
	double _frictionUntilStabilize;

	double _currentRoadHalfWidth;

	double _mapLimit;

	bool _movingForward;
	bool _movingBackward;
	bool _movingLeft;
	bool _movingRight;

	bool _curveLeft;
	bool _curveRight;

	bool _firstTimeGrass;

	Segment* _actualSegment;
	double _ratioYZ;
	double _ratioXZ;

	// move car using physics
	void moveCar(double deltaTime);
	bool inGrass();

	// ---- Values to handle animations
	Image* _image;
	Image* _imageDef;
	Image* _imageHill;

	enum class Animation {
		LEFT, IDLE, RIGHT
	};

	int _frameW, _frameH;
	int _frameRow, _maxFrameH;
	int _bounce;
	bool _bounceAnim;

	Animation _currentAnim;
	double _timeBetweenAnim;
	double _timerAnim;

	// change current image
	void changeImage();
	// update current animation
	void updateAnimation(double deltaTime);

public:
	Car(Image* image, Image* imageHill, Vector3 pos, int w, int h);

	// Update everything necessary for car behaviour
	void update(double deltaTime);

	// Render the image in the coordinates given by the viewport
	void render(RenderCommand* comando);

	void handleInput(Event evento);

	//---- GETTERS AND SETTERS

	void setActualSegment(Segment* seg);

	void setZPos(int z);

	// Return a pointer to the image
	Image* getImage();

	// Calculate the coordinates of the upper left
	// corner of the image according to the viewport
	Vector2 getUpperLeft();

	// Calculate the coordinates of the lower right
	// corner of the image according to the viewport
	Vector2 getDownRight();

	// Getters
	Vector3 getPosition();
};