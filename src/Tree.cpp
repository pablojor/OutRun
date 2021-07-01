#include "Tree.h"
#include "Renderer/Renderer.h"
#include "Camera.h"

Tree::Tree() { }

Tree::Tree(Image* image, Vector3 pos, int w, int h)
{
  _pos = pos;
  _width = w;
  _height = h;
  _image = image;
  _aspectRatio = (double)_width / _height;
}

// Render the image in the coordinates given by the viewport
void Tree::render()
{
  Vector2 viewPortUL = getUpperLeft();
  Vector2 viewPortLR = getDownRight();

  Renderer::DrawImage(_image, viewPortUL.getX(), viewPortUL.getY(), viewPortLR.getX(), viewPortLR.getY(),);
}

// Return a pointer to the image
Image* Tree::getImage()
{
    return _image;
}

// Calculate the coordinates of the upper left
// corner of the image according to the viewport
Vector2 Tree::getUpperLeft()
{
    Vector3 upperLeft = Vector3(_pos.getX() - (_width / 2), _pos.getY() + (_height / 2), _pos.getZ());
    return Camera::toViewport(upperLeft);;
}

// Calculate the coordinates of the lower right
// corner of the image according to the viewport
Vector2 Tree::getDownRight()
{
    Vector3 lowerRight = Vector3(_pos.getX() + (_width / 2), _pos.getY() - (_height / 2), _pos.getZ());
    return Camera::toViewport(lowerRight);
}
