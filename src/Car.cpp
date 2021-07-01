#include "Car.h"
#include "Renderer/Renderer.h"
#include "Camera.h"
#include "RenderCommand.h"
#include "Circuit/Segment.h"
#include "Platform/Platform.h"

void Car::moveCar(double deltaTime)
{
  bool grass = inGrass();
  double realMaxVelocity = grass ? _grassMaxVelocity : _maxVelocity;


	//Vibration
	if (grass)
		Platform::SetVibration(255);
	else
		Platform::SetVibration(0);

    // check if we surpass grass max velocity
    if (!grass || _velocity <= _grassMaxVelocity)
    {
        _firstTimeGrass = false;
        _realFriction = _friction;
    }
    else if(_velocity > _grassMaxVelocity)
    {
        _firstTimeGrass = true;
        _realFriction = _frictionUntilStabilize;
    }
    else
        _realFriction = _grassFriction;

    _velocity += (_realAceleration + _realFriction) * deltaTime;

    if (!_firstTimeGrass) 
        if (_velocity > realMaxVelocity)
            _velocity = realMaxVelocity;
    if (_velocity < 0.0)
        _velocity = 0.0;

    //Input movement
    _pos.setX(_pos.getX() + (_dir.getX() * _velocity * deltaTime));


    //Circuit movement
    double increZ = _dir.getY() * _velocity * deltaTime;

    _pos.setX(_pos.getX() + increZ * _ratioXZ);
    _pos.setY(_pos.getY() + increZ * _ratioYZ);
    _pos.setZ(_pos.getZ() + increZ);

    if (_pos.getX() < -_mapLimit)
        _pos.setX(-_mapLimit);
	else if (_pos.getX() > _mapLimit)
		_pos.setX(_mapLimit);
     
}
//Check if we are out of the road
bool Car::inGrass()
{
    return _pos.getX() > _currentRoadHalfWidth || _pos.getX() < -_currentRoadHalfWidth;
}

// Switches between normal car image and downhill car image
void Car::changeImage()
{
    if (_image == _imageDef)
    {
        _image = _imageHill;
        _frameW = 82;
        _frameH = 47;
    }
    else {
        _image = _imageDef;
        _frameW = 82;
        _frameH = 43;
    }
    _frameRow = _frameRow == 1 ? 0 : 1;
}

//Updates animation frames
void Car::updateAnimation(double deltaTime)
{
    if (_timerAnim >= _timeBetweenAnim) {
        _timerAnim = 0;
        _frameRow += _frameRow + _frameH;
        _bounceAnim = !_bounceAnim;

        if (_frameRow >= _maxFrameH) _frameRow = 0;
    }
    _timerAnim += deltaTime * (_velocity/500);
}

Car::Car(Image* image, Image* imageHill, Vector3 pos, int w, int h)
{
  _pos = pos;

  _width = w;
  _height = h;
  _aspectRatio = (double)_width / _height;

  _mapLimit = 10000;

  _dir = Vector2(0, 1);
  _velocity = 0;
  _maxVelocity = 8000;
  _grassMaxVelocity = 3000;
  _aceleration = 1500;
  _deceleration = -1500;
  _realAceleration = 0;
  _friction = -240; 
  _grassFriction = -300;
  _realFriction = _friction;
  _frictionUntilStabilize = -3000;

  _movingBackward = false;
  _movingForward = false;
  _movingLeft = false;
  _movingRight = false;

  _curveLeft = false;
  _curveRight = false;

  _firstTimeGrass = false;

  // Animations

  _imageDef = image;
  _imageHill = imageHill;
  changeImage();

  _frameRow = 0;
  _maxFrameH = 2 * _frameH;

  _bounceAnim = false;
  _bounce = 3;
  _currentAnim = Animation::IDLE;
  _timeBetweenAnim = 0.5;
  _timerAnim = 0;

  _ratioXZ = 0;
  _ratioYZ = 0;
}

// Update everything necessary for car behaviour
void Car::update(double deltaTime)
{
    updateAnimation(deltaTime);
    moveCar(deltaTime);
}

// Render the image in the coordinates given by the viewport
void Car::render(RenderCommand* comando)
{
  Vector2 viewPortUL = getUpperLeft();
  Vector2 viewPortLR = getDownRight();

  //Renderer::DrawImage(_image, viewPortUL.getX(), viewPortUL.getY(), viewPortLR.getX(), viewPortLR.getY());

  // Set position
  comando->drawSpriteInfo.image = _image;
  comando->drawSpriteInfo.x1 = viewPortUL.getX();
  comando->drawSpriteInfo.y1 = viewPortUL.getY();
  comando->drawSpriteInfo.x2 = viewPortLR.getX();
  comando->drawSpriteInfo.y2 = viewPortLR.getY();

  // Animation simulating car vibration
  if (_bounceAnim)
  {
      comando->drawSpriteInfo.y1 -= _bounce;
      comando->drawSpriteInfo.y2 -= _bounce;
  }

  // Select clip of image
  int col = _frameW * (int)_currentAnim;
  comando->drawSpriteInfo.srcX1 = col;
  comando->drawSpriteInfo.srcY1 = _frameRow;
  comando->drawSpriteInfo.srcX2 = col + _frameW;
  comando->drawSpriteInfo.srcY2 = _frameRow + _frameH;
}

void Car::handleInput(Event evento)
{
    //Check actions for every event
    // Forward movement
    if (evento.type == TypeEvent::MOVE_FORWARD && !_movingForward) {
        _realAceleration += _aceleration;
        _movingForward = true;
    }
    // Backwards movement
    else if (evento.type == TypeEvent::MOVE_BACKWARD && !_movingBackward) {
        _realAceleration += _deceleration;
        _movingBackward = true;
    }
    // Left movement
    else if (evento.type == TypeEvent::MOVE_LEFT && !_movingLeft) {
        _dir.setX(-0.4 + _dir.getX());
        _movingLeft = true;
        if (_movingRight)
            _dir.setX(-0.4 + _dir.getX());

        _currentAnim = Animation::LEFT;
        _movingRight = false;
    }
    // Right movement
    else if (evento.type == TypeEvent::MOVE_RIGHT && !_movingRight) {
        _dir.setX(0.4 + _dir.getX());
        _movingRight = true;

        if (_movingLeft)
            _dir.setX(0.4 + _dir.getX());

        _currentAnim = Animation::RIGHT;
        _movingLeft = false;
    }
    // Forward stop
    else if (evento.type == TypeEvent::STOP_FORWARD && _movingForward) {
        _realAceleration -= _aceleration;
        _movingForward = false;
    }
    // Backward stop
    else if (evento.type == TypeEvent::STOP_BACKWARD && _movingBackward) {
        _realAceleration -= _deceleration;
        _movingBackward = false;
    }
    // Left stop
    else if (evento.type == TypeEvent::STOP_LEFT && _movingLeft) {
        _dir.setX(0.4 + _dir.getX());
        _movingLeft = false;
        _currentAnim = Animation::IDLE;
    }
    // Right stop
    else if (evento.type == TypeEvent::STOP_RIGHT && _movingRight) {
        _dir.setX(-0.4 + _dir.getX());
        _movingRight = false;
        _currentAnim = Animation::IDLE;
    }
}

//Update values when we change to a new segment
void Car::setActualSegment(Segment* seg)
{
    _actualSegment = seg;

    _currentRoadHalfWidth = seg->getAsphaltDownRight().getX();

    _pos.setY(_actualSegment->getAsphaltDownLeft().getY());
    double xDiff = _actualSegment->getDiffX();
    double yDiff = _actualSegment->getAsphaltUpLeft().getY() - _actualSegment->getAsphaltDownLeft().getY();
    double zDiff = _actualSegment->getAsphaltUpLeft().getZ() - _actualSegment->getAsphaltDownLeft().getZ();

    _ratioYZ = yDiff / zDiff;
    _ratioXZ = -xDiff / zDiff;

    if (yDiff > 0 && _image == _imageDef)
        changeImage();
    else if(yDiff <= 0 && _image != _imageDef)
        changeImage();
}

// GETTERS AND SETTERS
void Car::setZPos(int z)
{
    _pos.setZ(z);
}

// Return a pointer to the image
Image* Car::getImage()
{
    return _image;
}

// Calculate the coordinates of the upper left
// corner of the image according to the viewport
Vector2 Car::getUpperLeft()
{
    Vector3 upperLeft = Vector3(_pos.getX() - (_width / 2), _pos.getY() + (_height / 2), _pos.getZ());
    return Camera::toViewport(upperLeft);;
}

// Calculate the coordinates of the lower right
// corner of the image according to the viewport
Vector2 Car::getDownRight()
{
    Vector3 lowerRight = Vector3(_pos.getX() + (_width / 2), _pos.getY() - (_height / 2), _pos.getZ());
    return Camera::toViewport(lowerRight);
}

Vector3 Car::getPosition()
{
    return _pos;
}
