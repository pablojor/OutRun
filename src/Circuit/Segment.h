#pragma once

#include "Vector3.h"
#include "Vector2.h"
#include "Image/Image.h"
class RenderCommand;

class Segment {
private:
	uint32_t _asphaltColor;
	uint32_t _shoulderColor;
	uint32_t _grassColor;

	int32_t _curveDist;
	double _downPointCurveInc;
	double _upPointCurveInc;

	//3D positions
	Vector3 _asphaltDownLeft;
	Vector3 _asphaltDownRight;	
	Vector3 _asphaltUpLeft;
	Vector3 _asphaltUpRight;

	Vector3 _shoulderDownLeftLeft;
	Vector3 _shoulderDownRightRight;
	Vector3 _shoulderUpLeftLeft;
	Vector3 _shoulderUpRightRight;

	Vector3 _grassDownLeft;
	Vector3 _grassDownRight;
	Vector3 _grassUpLeft;
	Vector3 _grassUpRight;

	//Positions adapted to viewport
	Vector2 _shoulderDownLeftLeft_ToViewport;
	Vector2 _shoulderDownRightRight_ToViewport;
	Vector2 _shoulderUpLeftLeft_ToViewport;
	Vector2 _shoulderUpRightRight_ToViewport;

	Vector2 _asphaltDownLeft_ToViewport;
	Vector2 _asphaltUpLeft_ToViewport;
	Vector2 _asphaltDownRight_ToViewport;
	Vector2 _asphaltUpRight_ToViewport;

	Vector2 _grassDownLeft_ToViewport;
	Vector2 _grassDownRight_ToViewport;
	Vector2 _grassUpLeft_ToViewport;
	Vector2 _grassUpRight_ToViewport;

public:
	Segment();
	Segment(uint32_t asphaltColor, uint32_t shoulderColor, uint32_t grassColor, int32_t curveDistAnt);

	// Sets this segment to a copy of given segment
	void copySegment(Segment* segToCopy);

	// Load data from every element of the segment into the render command
	void renderAsphalt(RenderCommand* comando, int32_t maxHeight);
	void renderShoulderLeft(RenderCommand* comando, int32_t maxHeight);
	void renderShoulderRight(RenderCommand* comando, int32_t maxHeight);
	void renderGrassLeft(RenderCommand* comando, int32_t maxHeight);
	void renderGrassRight(RenderCommand* comando, int32_t maxHeight);

	// Position setters for every element of the segment
	void setDownPos(int32_t asphaltTam, float heigth, int32_t zDist);
	void setDownPosWithVectors(Vector3 asphaltDownLeft, Vector3 asphaltDownRight, Vector3 shoulderDownLeftLeft, Vector3 shoulderDownRightRight, Vector3 grassDownLeft, Vector3 grassDownRight);
	void setUpPosWithVectors(Vector3 asphaltUpLeft, Vector3 asphaltUpRight, Vector3 shoulderUpLeftLeft, Vector3 shoulderUpRightRight, Vector3 grassUpLeft, Vector3 grassUpRight);
	
	// Calculate viewport positions and returns segment height
	int32_t prepareToRender(double& curveAmount, double& realCurveAmount, double amountToMovedInSegment);

	// Sets Z position of of upper vertices of each element of the segment
	void setZUp(int newZ);

	// Sets Z position of of lower vertices of each element of the segment
	void setZDown(int newZ);

	// Adds curve offset to each element of the segment
	void setCurveIn3D();

	// ========== GETTERS ==========
	int32_t getCurveDist();
	double getDiffX();

	Vector3 getAsphaltDownLeft();
	Vector3 getAsphaltDownRight();
	Vector3 getAsphaltUpLeft();
	Vector3 getAsphaltUpRight();

	Vector3 getShoulderDownLeftLeft();
	Vector3 getShoulderDownRightRight();
	Vector3 getShoulderUpLeftLeft();
	Vector3 getShoulderUpRightRight();

	Vector3 getGrassDownLeft();
	Vector3 getGrassDownRight();
	Vector3 getGrassUpLeft();
	Vector3 getGrassUpRight();
};