#include "Circuit.h"
#include "Segment.h"
#include "Platform/Platform.h"
#include "Vector3.h"
#include "Renderer/Renderer.h"
#include "RenderThread.h"
#include "RenderCommand.h"
#include "Camera.h"
#include "Car.h"
#include <iostream>

Circuit::~Circuit()
{
	for (int i = 0; i < _numSegments; i++)
		delete _segments[i];
	delete _buffer;
}

void Circuit::init(Car* c)
{
	_iniSeg = 0, _iniCarSeg = 0;

	// Calculate segment where Car starts
	while (c->getPosition().getZ() > _segments[_iniCarSeg]->getAsphaltUpRight().getZ())
		_iniCarSeg++;
	c->setActualSegment(_segments[_iniCarSeg]);
}

// Reads file and creates all segments
void Circuit::loadFile(const char* filepath)
{
	_buffer = Platform::Get_Buffer_From_File(filepath);
	_numSegments = *((uint32_t*)_buffer);

	createSegment(_buffer, 0);

	int sum = 7;
	for (int i = 1; i < _numSegments; i++)
	{
		createSegment(_buffer, sum);
		_segments[i-1]->setUpPosWithVectors(_segments[i]->getAsphaltDownLeft(), _segments[i]->getAsphaltDownRight(), _segments[i]->getShoulderDownLeftLeft(), _segments[i]->getShoulderDownRightRight(), _segments[i]->getGrassDownLeft(), _segments[i]->getGrassDownRight());
		sum += 7;
	}

	_segments[_numSegments - 1]->setUpPosWithVectors(_segments[0]->getAsphaltDownLeft(), _segments[0]->getAsphaltDownRight(), _segments[0]->getShoulderDownLeftLeft(), _segments[0]->getShoulderDownRightRight(), _segments[0]->getGrassDownLeft(), _segments[0]->getGrassDownRight());

	_segments[_numSegments - 1]->setZUp(_segments[_numSegments - 1]->getAsphaltDownRight().getZ() + _segments[_numSegments - 2]->getAsphaltUpRight().getZ() - _segments[_numSegments - 2]->getAsphaltDownRight().getZ());

	// Add 300 more segments at the end
	int lastZ = 0;
	for (int i = 0; i < 300; i++)
	{
		Segment* segment = new Segment();
		segment->copySegment(_segments[i]);
		int zTam = _segments[i]->getAsphaltUpRight().getZ() - _segments[i]->getAsphaltDownRight().getZ();

		segment->setZDown(lastZ + _segments[_numSegments - 1]->getAsphaltUpRight().getZ());
		lastZ += zTam;
		segment->setZUp(lastZ + _segments[_numSegments - 1]->getAsphaltUpRight().getZ());

		_segments.push_back(segment);
	}
	_numSegments += 300;
}

// Add values to the segment
void Circuit::createSegment(void* buffer, int sum) {
	int32_t zDist = *((int32_t*)(buffer)+1 + sum);
	int32_t curveDist = *((int32_t*)(buffer)+2 + sum);
	int32_t asphaltTam = *((int32_t*)(buffer)+3 + sum);
	float heigth = *((float*)(buffer)+4 + sum);
	uint32_t asphaltColor = Platform::Big_to_Little(*((uint32_t*)(buffer)+5 + sum));
	uint32_t roadSideColor = Platform::Big_to_Little(*((uint32_t*)(buffer)+6 + sum));
	uint32_t grassColor = Platform::Big_to_Little(*((uint32_t*)(buffer)+7 + sum));

	Segment* segment = new Segment(asphaltColor, roadSideColor, grassColor, curveDist);

	segment->setDownPos(asphaltTam, heigth, zDist);

	_segments.push_back(segment);
}

// Renders 300 segments checking if segment to render is not off limits in height
void Circuit::render(RenderThread* thread, RenderCommand* comando)
{
	int32_t maxHeight = Renderer::GetHeight();
	double realCurveAmount = 0.0, curveAmount = 0.0;

	double amountMovedInSegment = (_segments[_iniSeg]->getAsphaltUpRight().getZ() - Camera::getPosition().getZ())
						/ (_segments[_iniSeg]->getAsphaltUpRight().getZ() - _segments[_iniSeg]->getAsphaltDownRight().getZ());

	if (amountMovedInSegment > 1)
		amountMovedInSegment = 1;
	else if(amountMovedInSegment < 0)
		amountMovedInSegment = 0;

	int32_t aux = _segments[_iniSeg]->prepareToRender(curveAmount, realCurveAmount, amountMovedInSegment);

	_segments[_iniSeg]->renderAsphalt(comando, maxHeight);
	thread->enqueueCommand(*comando);

	_segments[_iniSeg]->renderShoulderLeft(comando, maxHeight);
	thread->enqueueCommand(*comando);

	_segments[_iniSeg]->renderShoulderRight(comando, maxHeight);
	thread->enqueueCommand(*comando);

	_segments[_iniSeg]->renderGrassLeft(comando, maxHeight);
	thread->enqueueCommand(*comando);

	_segments[_iniSeg]->renderGrassRight(comando, maxHeight);
	thread->enqueueCommand(*comando);

	if (aux < maxHeight && aux > 0)
		maxHeight = aux;

	// Enqueue Renderer::DrawTrapece() command
	for (int i = _iniSeg + 1; i < _iniSeg + 300; i++)
	{
		aux = _segments[i]->prepareToRender(curveAmount, realCurveAmount, 1);

		_segments[i]->renderAsphalt(comando, maxHeight);
		thread->enqueueCommand(*comando);

		_segments[i]->renderShoulderLeft(comando, maxHeight);
		thread->enqueueCommand(*comando);

		_segments[i]->renderShoulderRight(comando, maxHeight);
		thread->enqueueCommand(*comando);

		_segments[i]->renderGrassLeft(comando, maxHeight);
		thread->enqueueCommand(*comando);

		_segments[i]->renderGrassRight(comando, maxHeight);
		thread->enqueueCommand(*comando);

		if (aux < maxHeight && aux > 0)
			maxHeight = aux;

	}
}

void Circuit::update(Car* c, int zOffset)
{
	// Check segment to render
	if (Camera::getPosition().getZ() > _segments[_iniSeg]->getAsphaltUpRight().getZ())
	{
		_iniSeg++;
		if (_iniSeg >= _numSegments - 300)
		{
			_iniSeg = 0;
			_iniCarSeg = 0;

			c->setZPos(_segments[_iniSeg]->getAsphaltDownLeft().getZ() - zOffset);
			while (-zOffset > _segments[_iniCarSeg]->getAsphaltUpRight().getZ())
				_iniCarSeg++;
		}

	}

	// Check segment in car
	if (c->getPosition().getZ() > _segments[_iniCarSeg]->getAsphaltUpRight().getZ())
	{
		_iniCarSeg++;
		c->setActualSegment(_segments[_iniCarSeg]);
	}
}

uint32_t Circuit::getNumSegments()
{
	return _numSegments;
}

std::vector<Segment*>& Circuit::getSegments()
{
	return _segments;
}
