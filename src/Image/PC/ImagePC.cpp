#ifdef PLATFORM_PC
#include "ImagePC.h"
#include "Platform/Platform.h"
#include "SDL_surface.h"
#include "SDL_render.h"

#include <stdio.h>
#include <iostream>

ImagePC::~ImagePC()
{
	SDL_DestroyTexture(text);
	delete buffer;
}

// Reads the image from the parameter file
void ImagePC::loadFile(const char* filepath, SDL_Renderer* renderer)
{
	buffer =(uint32_t*)Platform::Get_Buffer_From_File(filepath);

	// Read image proportions from buffer

	image_width = SDL_Swap32(*buffer);
	buffer++;
	image_height = SDL_Swap32(*buffer);
	buffer++;

	// Read the image itself from the file
	image = buffer;
	buffer -= 2;

	int i = 0;
	int size = image_width * image_height;
	while (i < size)
	{
		*(image + i) = SDL_Swap32(*(image + i));
		i++;
	}

	// Create an SDL_Surface from the image
	SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormatFrom(image, image_width, image_height,
		32, 4 * image_width, SDL_PIXELFORMAT_ABGR32);
	if (surf == NULL) {
		std::cout << "Surface error\n";
		return;
	}

	text = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
}

// ========== GETTERS ==========
SDL_Texture* ImagePC::getImage()
{
	return text;
}

uint32_t ImagePC::getWidth()
{
	return image_width;
}

uint32_t ImagePC::getHeight()
{
	return image_height;
}
uint32_t ImagePC::getPixelColor(int x, int y)
{
	int index = (x * image_width) + y;

	uint32_t color = *(image + index);
	return color;
}
#endif