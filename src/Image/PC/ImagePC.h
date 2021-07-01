#pragma once
#ifdef PLATFORM_PC

#include <stdint.h>
class SDL_Surface;
class SDL_Texture;
class SDL_Renderer;

class ImagePC
{
private:
	SDL_Texture* text;
	uint32_t* buffer;
	uint32_t* image;
	uint32_t image_width;
	uint32_t image_height;

public:
	~ImagePC();

	// Reads the image from the parameter file
	void loadFile(const char* filepath, SDL_Renderer* renderer);

	// ========== GETTERS ==========
	SDL_Texture* getImage();
	uint32_t getWidth();
	uint32_t getHeight();
	// Return de color of the pixel in row 'x' and column 'y'
	uint32_t getPixelColor(int x, int y);
};
#endif