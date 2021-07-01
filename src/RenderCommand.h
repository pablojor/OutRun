#pragma once

#include "Image/Image.h"

enum class RenderCommandType
{
	CLEAR, PRESENT, DRAWIMAGE, DRAWLINE, DRAWTRAPECE, DRAWSPRITE
};

struct ClearInfo
{
	uint32_t color;
};

struct DrawImageInfo
{
	Image* image;
	int x1, x2, y1, y2;
};

struct DrawSpriteInfo
{
	Image* image;
	int x1, x2, y1, y2;
	int srcX1, srcX2, srcY1, srcY2;
};

struct DrawLineInfo
{
	uint32_t color;
	int y, x1, x2;
};

struct DrawTrapeceInfo
{
	uint32_t color;
	int x1, y1, w1, x2, y2, w2, maxHeight;
};

struct RenderCommand
{
	RenderCommandType type;

	union
	{
		ClearInfo clearInfo;
		DrawImageInfo drawImageInfo;
		DrawLineInfo drawLineInfo;
		DrawTrapeceInfo drawTrapeceInfo;
		DrawSpriteInfo drawSpriteInfo;
	};
};