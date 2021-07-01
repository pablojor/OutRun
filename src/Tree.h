#pragma once

#include "Vector3.h"
#include "Vector2.h"
#include "Image/Image.h"

class Tree {
private:
	Vector3 _pos;
	int _width, _height;
	Image* _image;
	double _aspectRatio;

public:
	Tree();
	Tree(Image* image, Vector3 pos, int w, int h);

	// Render the image in the coordinates given by the viewport
	void render();

	// Return a pointer to the image
	Image* getImage();

	// Calculate the coordinates of the upper left
	// corner of the image according to the viewport
	Vector2 getUpperLeft();

	// Calculate the coordinates of the lower right
	// corner of the image according to the viewport
	Vector2 getDownRight();
};