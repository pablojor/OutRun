#pragma once
#ifdef PLATFORM_PC

#include "Image/Image.h"
#include <stdint.h>


class SDL_Window;
class SDL_Renderer;

class RendererPC
{
private:
	static SDL_Window* _window;
	static SDL_Renderer* _renderer;

	static int win_width;
	static int win_height;

public:
	// Create SDL Window and Renderer
	static void Init(bool tryWindowed, int resX, int resY);

	// Destroy SDL Window and Renderer
	static void Release();

	static void Present();
	static void Clear(uint32_t color);

	// Sets drawing color for future renders
	static void SetColor(uint32_t color);

	// Draws horizontal line in given position and color
	static void DrawHLine(int y, int x1, int x2, uint32_t color);

	// Draws single pixel in given position and color
	static void PutPixel(int x, int y, uint32_t color);

	//Draws a trapece
	static void DrawTrapece(int x1, int y1, int w1, int x2, int y2, int w2, uint32_t c, int maxHeight);

	// Draws image in given viewport-adapted coordinates
	static void DrawImage(Image* image, int x1, int y1, int x2, int y2);

	// Draws a portion (sprite) of an image in given viewport-adapted coordinates
	static void DrawSprite(Image* image, int x1, int y1, int x2, int y2, int srcX1, int srcY1, int srcX2, int srcY2);

	// Creates an image from the file given
	static Image* CreateImage(const char* path);

	// ========== GETTERS ==========
	static int GetWidth();
	static int GetHeight();
	static SDL_Renderer* getRenderer();
};
#endif