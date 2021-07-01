#include "Segment.h"
#include "Camera.h"
#include "RenderCommand.h"
#include <stdlib.h>
#include <iostream>

Segment::Segment() {}

Segment::Segment(uint32_t asphaltColor, uint32_t shoulderColor, uint32_t grassColor, int32_t curveDistAnt) : _asphaltColor(asphaltColor), _shoulderColor(shoulderColor), _grassColor(grassColor), _curveDist(curveDistAnt)
{
	_upPointCurveInc = 0;
	_downPointCurveInc = 0;
}

// Sets this segment to a copy of given segment
void Segment::copySegment(Segment* segToCopy)
{
	this->_asphaltDownLeft = segToCopy->_asphaltDownLeft;
	this->_asphaltDownRight = segToCopy->_asphaltDownRight;
	this->_asphaltUpLeft = segToCopy->_asphaltUpLeft;
	this->_asphaltUpRight = segToCopy->_asphaltUpRight;
	this->_asphaltColor = segToCopy->_asphaltColor;

	this->_curveDist = segToCopy->_curveDist;

	this->_grassColor = segToCopy->_grassColor;
	this->_grassDownLeft = segToCopy->_grassDownLeft;
	this->_grassDownRight = segToCopy->_grassDownRight;
	this->_grassUpLeft = segToCopy->_grassUpLeft;
	this->_grassUpRight = segToCopy->_grassUpRight;

	this->_shoulderColor = segToCopy->_shoulderColor;
	this->_shoulderDownLeftLeft = segToCopy->_shoulderDownLeftLeft;
	this->_shoulderDownRightRight = segToCopy->_shoulderDownRightRight;
	this->_shoulderUpLeftLeft = segToCopy->_shoulderUpLeftLeft;
	this->_shoulderUpRightRight = segToCopy->_shoulderUpRightRight;
}

void Segment::renderAsphalt(RenderCommand* comando, int32_t maxHeight)
{
	comando->drawTrapeceInfo.color = _asphaltColor;
	comando->drawTrapeceInfo.maxHeight = maxHeight;

	comando->drawTrapeceInfo.x1 = (int32_t)_asphaltUpLeft_ToViewport.getX();
	comando->drawTrapeceInfo.y1 = (int32_t)_asphaltUpLeft_ToViewport.getY();
	comando->drawTrapeceInfo.w1 = abs((int32_t)_asphaltUpLeft_ToViewport.getX() - (int32_t)_asphaltUpRight_ToViewport.getX());

	comando->drawTrapeceInfo.x2 = (int32_t)_asphaltDownLeft_ToViewport.getX();
	comando->drawTrapeceInfo.y2 = (int32_t)_asphaltDownLeft_ToViewport.getY();
	comando->drawTrapeceInfo.w2 = abs((int32_t)_asphaltDownLeft_ToViewport.getX() - (int32_t)_asphaltDownRight_ToViewport.getX());
}

void Segment::renderShoulderLeft(RenderCommand* comando, int32_t maxHeight)
{
	comando->drawTrapeceInfo.color = _shoulderColor;
	comando->drawTrapeceInfo.maxHeight = maxHeight;

	comando->drawTrapeceInfo.x1 = (int32_t)_shoulderUpLeftLeft_ToViewport.getX();
	comando->drawTrapeceInfo.y1 = (int32_t)_shoulderUpLeftLeft_ToViewport.getY();
	comando->drawTrapeceInfo.w1 = abs((int32_t)_asphaltUpLeft_ToViewport.getX() - (int32_t)_shoulderUpLeftLeft_ToViewport.getX());

	comando->drawTrapeceInfo.x2 = (int32_t)_shoulderDownLeftLeft_ToViewport.getX();
	comando->drawTrapeceInfo.y2 = (int32_t)_shoulderDownLeftLeft_ToViewport.getY();
	comando->drawTrapeceInfo.w2 = abs((int32_t)_asphaltDownLeft_ToViewport.getX() - (int32_t)_shoulderDownLeftLeft_ToViewport.getX());
}

void Segment::renderShoulderRight(RenderCommand* comando, int32_t maxHeight)
{
	comando->drawTrapeceInfo.color = _shoulderColor;
	comando->drawTrapeceInfo.maxHeight = maxHeight;

	comando->drawTrapeceInfo.x1 = (int32_t)_asphaltUpRight_ToViewport.getX();
	comando->drawTrapeceInfo.y1 = (int32_t)_asphaltUpRight_ToViewport.getY();
	comando->drawTrapeceInfo.w1 = abs((int32_t)_asphaltUpRight_ToViewport.getX() - (int32_t)_shoulderUpRightRight_ToViewport.getX());

	comando->drawTrapeceInfo.x2 = (int32_t)_asphaltDownRight_ToViewport.getX();
	comando->drawTrapeceInfo.y2 = (int32_t)_asphaltDownRight_ToViewport.getY();
	comando->drawTrapeceInfo.w2 = abs((int32_t)_asphaltDownRight_ToViewport.getX() - (int32_t)_shoulderDownRightRight_ToViewport.getX());
}

void Segment::renderGrassLeft(RenderCommand* comando, int32_t maxHeight)
{
	comando->drawTrapeceInfo.color = _grassColor;
	comando->drawTrapeceInfo.maxHeight = maxHeight;

	comando->drawTrapeceInfo.x1 = (int32_t)_grassUpLeft_ToViewport.getX();
	comando->drawTrapeceInfo.y1 = (int32_t)_grassUpLeft_ToViewport.getY();
	comando->drawTrapeceInfo.w1 = abs((int32_t)_grassUpLeft_ToViewport.getX() - (int32_t)_shoulderUpLeftLeft_ToViewport.getX());

	comando->drawTrapeceInfo.x2 = (int32_t)_grassDownLeft_ToViewport.getX();
	comando->drawTrapeceInfo.y2 = (int32_t)_grassDownLeft_ToViewport.getY();
	comando->drawTrapeceInfo.w2 = abs((int32_t)_grassDownLeft_ToViewport.getX() - (int32_t)_shoulderDownLeftLeft_ToViewport.getX());
}

void Segment::renderGrassRight(RenderCommand* comando, int32_t maxHeight)
{
	comando->drawTrapeceInfo.color = _grassColor;
	comando->drawTrapeceInfo.maxHeight = maxHeight;

	comando->drawTrapeceInfo.x1 = (int32_t)_shoulderUpRightRight_ToViewport.getX();
	comando->drawTrapeceInfo.y1 = (int32_t)_shoulderUpRightRight_ToViewport.getY();
	comando->drawTrapeceInfo.w1 = abs((int32_t)_shoulderUpRightRight_ToViewport.getX() - (int32_t)_grassUpRight_ToViewport.getX());

	comando->drawTrapeceInfo.x2 = (int32_t)_shoulderDownRightRight_ToViewport.getX();
	comando->drawTrapeceInfo.y2 = (int32_t)_shoulderDownRightRight_ToViewport.getY();
	comando->drawTrapeceInfo.w2 = abs((int32_t)_shoulderDownRightRight_ToViewport.getX() - (int32_t)_grassDownRight_ToViewport.getX());
}

void Segment::setDownPos(int32_t asphaltTam, float heigth, int32_t zDist)
{
	int32_t half = asphaltTam / 2;
	_asphaltDownRight.changeVector((int32_t)(half), heigth, (int32_t)zDist);
	_asphaltDownLeft.changeVector((int32_t)(-half), heigth, (int32_t)zDist);

	_shoulderDownLeftLeft.changeVector((int32_t)(-half - (asphaltTam/6)), heigth, (int32_t)zDist);
	_shoulderDownRightRight.changeVector((int32_t)(half + (asphaltTam / 6)), heigth, (int32_t)zDist);

	_grassDownLeft.changeVector((int32_t)-1000000 , heigth, (int32_t)zDist);
	_grassDownRight.changeVector((int32_t)1000000, heigth, (int32_t)zDist);
}

void Segment::setDownPosWithVectors(Vector3 alphasDowntLeft, Vector3 asphaltDownRight, Vector3 shoulderDownLeftLeft, Vector3 shoulderDownRightRight, Vector3 grassDownLeft, Vector3 grassDownRight)
{
	_asphaltDownLeft = alphasDowntLeft;
	_asphaltDownRight = asphaltDownRight;

	_shoulderDownLeftLeft = shoulderDownLeftLeft;
	_shoulderDownRightRight = shoulderDownRightRight;

	_grassDownLeft = grassDownLeft;
	_grassDownRight = grassDownRight;
}

void Segment::setUpPosWithVectors(Vector3 asphaltUpLeft, Vector3 asphaltUpRight, Vector3 shoulderUpLeftLeft, Vector3 shoulderUpRightRight, Vector3 grassUpLeft, Vector3 grassUpRight)
{
	_asphaltUpLeft = asphaltUpLeft;
	_asphaltUpRight = asphaltUpRight;

	_shoulderUpLeftLeft = shoulderUpLeftLeft;
	_shoulderUpRightRight = shoulderUpRightRight;

	_grassUpLeft = grassUpLeft;
	_grassUpRight = grassUpRight;
}

//Calculate viewport positions and returns segment height
int32_t Segment::prepareToRender(double& curveAmount, double& realCurveAmount, double amountMovedInSegment)
{	
	_downPointCurveInc = realCurveAmount;
	_upPointCurveInc = realCurveAmount + (((double)_curveDist * amountMovedInSegment) + curveAmount);

	// Shoulder down left
	Vector3 shoulderDownLeftLeftCurve = _shoulderDownLeftLeft;
	shoulderDownLeftLeftCurve.setX(shoulderDownLeftLeftCurve.getX() + _downPointCurveInc);
	_shoulderDownLeftLeft_ToViewport = Camera::toViewport(shoulderDownLeftLeftCurve);

	// Shoulder down right
	Vector3 shoulderDownRightRightCurve = _shoulderDownRightRight;
	shoulderDownRightRightCurve.setX(shoulderDownRightRightCurve.getX() + _downPointCurveInc);
	_shoulderDownRightRight_ToViewport = Camera::toViewport(shoulderDownRightRightCurve);

	// Shoulder up left
	Vector3 shoulderUpLeftLeftCurve = _shoulderUpLeftLeft;
	shoulderUpLeftLeftCurve.setX(shoulderUpLeftLeftCurve.getX() + _upPointCurveInc);
	_shoulderUpLeftLeft_ToViewport = Camera::toViewport(shoulderUpLeftLeftCurve);

	// Shoulder up right
	Vector3 shoulderUpRightRightCurve = _shoulderUpRightRight;
	shoulderUpRightRightCurve.setX(shoulderUpRightRightCurve.getX() + _upPointCurveInc);
	_shoulderUpRightRight_ToViewport = Camera::toViewport(shoulderUpRightRightCurve);


	// Asphalt down left
	Vector3 asphaltDownLeftCurve = _asphaltDownLeft;
	asphaltDownLeftCurve.setX(asphaltDownLeftCurve.getX() + _downPointCurveInc);
	_asphaltDownLeft_ToViewport = Camera::toViewport(asphaltDownLeftCurve);

	// Asphalt down right
	Vector3 asphaltDownRightCurve = _asphaltDownRight;
	asphaltDownRightCurve.setX(asphaltDownRightCurve.getX() + _downPointCurveInc);
	_asphaltDownRight_ToViewport = Camera::toViewport(asphaltDownRightCurve);

	// Asphalt up left
	Vector3 asphaltUpLeftCurve = _asphaltUpLeft;
	asphaltUpLeftCurve.setX(asphaltUpLeftCurve.getX() + _upPointCurveInc);
	_asphaltUpLeft_ToViewport = Camera::toViewport(asphaltUpLeftCurve);

	// Asphalt up right
	Vector3 asphaltUpRightCurve = _asphaltUpRight;
	asphaltUpRightCurve.setX(asphaltUpRightCurve.getX() + _upPointCurveInc);
	_asphaltUpRight_ToViewport = Camera::toViewport(asphaltUpRightCurve);


	// Grass down left
	Vector3 grassDownLeftCurve = _grassDownLeft;
	grassDownLeftCurve.setX(grassDownLeftCurve.getX() + _downPointCurveInc);
	_grassDownLeft_ToViewport = Camera::toViewport(grassDownLeftCurve);

	// Grass down right
	Vector3 grassDownRightCurve = _grassDownRight;
	grassDownRightCurve.setX(grassDownRightCurve.getX() + _downPointCurveInc);
	_grassDownRight_ToViewport = Camera::toViewport(grassDownRightCurve);

	// Grass up left
	Vector3 grassUpLeftCurve = _grassUpLeft;
	grassUpLeftCurve.setX(grassUpLeftCurve.getX() + _upPointCurveInc);
	_grassUpLeft_ToViewport = Camera::toViewport(grassUpLeftCurve);

	// Grass up right
	Vector3 grassUpRightCurve = _grassUpRight;
	grassUpRightCurve.setX(grassUpRightCurve.getX() + _upPointCurveInc);
	_grassUpRight_ToViewport = Camera::toViewport(grassUpRightCurve);

	curveAmount += (double)_curveDist * amountMovedInSegment;
	realCurveAmount = _upPointCurveInc;

	return _asphaltUpRight_ToViewport.getY();
}

// Sets Z position of of upper vertices of each element of the segment
void Segment::setZUp(int newZ)
{
	_asphaltUpLeft.setZ(newZ);
	_asphaltUpRight.setZ(newZ);
	_shoulderUpLeftLeft.setZ(newZ);
	_shoulderUpRightRight.setZ(newZ);

	_grassUpLeft.setZ(newZ);
	_grassUpRight.setZ(newZ);
}

// Sets Z position of of lower vertices of each element of the segment
void Segment::setZDown(int newZ)
{
	_asphaltDownLeft.setZ(newZ);
	_asphaltDownRight.setZ(newZ);
	_shoulderDownLeftLeft.setZ(newZ);
	_shoulderDownRightRight.setZ(newZ);

	_grassDownLeft.setZ(newZ);
	_grassDownRight.setZ(newZ);
}

// Adds curve offset to each element of the segment
void Segment::setCurveIn3D()
{
	_asphaltUpLeft.setX(_asphaltUpLeft.getX() + _curveDist);
	_asphaltUpRight.setX(_asphaltUpRight.getX() + _curveDist);

	_shoulderUpLeftLeft.setX(_shoulderUpLeftLeft.getX() + _curveDist);
	_shoulderUpRightRight.setX(_shoulderUpRightRight.getX() + _curveDist);

	_grassUpLeft.setX(_grassUpLeft.getX() + _curveDist);
	_grassUpRight.setX(_grassUpRight.getX() + _curveDist);

	_asphaltDownLeft.setX(_asphaltDownLeft.getX() + _curveDist);
	_asphaltDownRight.setX(_asphaltDownRight.getX() + _curveDist);

	_shoulderDownLeftLeft.setX(_shoulderDownLeftLeft.getX() + _curveDist);
	_shoulderDownRightRight.setX(_shoulderDownRightRight.getX() + _curveDist);

	_grassDownLeft.setX(_grassDownLeft.getX() + _curveDist);
	_grassDownRight.setX(_grassDownRight.getX() + _curveDist);
}

// Getters
int32_t Segment::getCurveDist()
{
	return _curveDist;
}

double Segment::getDiffX()
{
	return _upPointCurveInc - _downPointCurveInc;
}

Vector3 Segment::getAsphaltDownLeft()
{
	return _asphaltDownLeft;
}

Vector3 Segment::getAsphaltDownRight()
{
	return _asphaltDownRight;
}

Vector3 Segment::getAsphaltUpLeft()
{
	return _asphaltUpLeft;
}

Vector3 Segment::getAsphaltUpRight()
{
	return _asphaltUpRight;
}

Vector3 Segment::getShoulderDownLeftLeft()
{
	return _shoulderDownLeftLeft;
}

Vector3 Segment::getShoulderDownRightRight()
{
	return _shoulderDownRightRight;
}

Vector3 Segment::getShoulderUpLeftLeft()
{
	return _shoulderUpLeftLeft;
}

Vector3 Segment::getShoulderUpRightRight()
{
	return _shoulderUpRightRight;
}

Vector3 Segment::getGrassDownLeft()
{
	return _grassDownLeft;
}

Vector3 Segment::getGrassDownRight()
{
	return _grassDownRight;
}

Vector3 Segment::getGrassUpLeft()
{
	return _grassUpLeft;
}
Vector3 Segment::getGrassUpRight()
{
	return _grassUpRight;
}
