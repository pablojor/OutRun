#ifdef PLATFORM_PC
#include "RendererPC.h"
#include "Platform/Platform.h"
#include "SDL.h"
#include <iostream>

SDL_Window* RendererPC::_window = nullptr;
SDL_Renderer* RendererPC::_renderer = nullptr;
int RendererPC::win_width = 0;
int RendererPC::win_height = 0;

// Create SDL Window and Renderer
void RendererPC::Init(bool tryWindowed, int resX, int resY)
{
    if (!tryWindowed)
    {
        SDL_DisplayMode monitor;
        SDL_GetCurrentDisplayMode(0, &monitor);
        win_width = monitor.w;
        win_height = monitor.h;

        _window = SDL_CreateWindow("Out Run", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    else
    {
        win_width = resX;
        win_height = resY;

        _window = SDL_CreateWindow("Out Run", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN);
    }

    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

// Destroy SDL Window and Renderer
void RendererPC::Release()
{
    if (_renderer != nullptr)
        SDL_DestroyRenderer(_renderer);
    if (_window != nullptr)
        SDL_DestroyWindow(_window);
}

void RendererPC::Present()
{
    SDL_RenderPresent(_renderer);
}

void RendererPC::Clear(uint32_t color)
{
	SetColor(color);
    SDL_RenderClear(_renderer);
}

// Sets drawing color for future renders
void RendererPC::SetColor(uint32_t color)
{
	uint8_t colorResult[4];
	Platform::Uint32_to_Uint8(color, colorResult);
	SDL_SetRenderDrawColor(_renderer, colorResult[0], colorResult[1], colorResult[2], colorResult[3]);
}


// Draws horizontal line in given position and color
void RendererPC::DrawHLine(int y, int x1, int x2, uint32_t color)
{
	SetColor(color);
    SDL_RenderDrawLine(_renderer, x1, y, x2, y);
}

// Draws single pixel in given position and color
void RendererPC::PutPixel(int x, int y, uint32_t color)
{
	SetColor(color);
    SDL_RenderDrawPoint(_renderer, x, y);
}

//Draws trapece with cliping
void RendererPC::DrawTrapece(int x1, int y1, int w1, int x2, int y2, int w2, uint32_t c, int maxHeight)
{
	if (y1 > y2)
		return;
	if ((x2 + w2 < 0 && x1 + w1 < 0) || (x1 > win_width&& x2 > win_width) || y2 < 0 || y1 > maxHeight)
		return;


	double diffY = abs((float)(y2 - y1));
	double diffX = abs((float)(x2 - x1));
	double diffW = abs((float)(w2 - w1));
	double incre = diffX / diffY;
	double increW = diffW / diffY;
	double suma = 0;
	double sumaW = 0;

	int add = 1;
	int move = -1;

	if (w1 > w2)
		add *= -1;
	if (x2 > x1)
		move *= -1;

	if (y1 < 0)
		y1 = 0;
	if (y2 > maxHeight)
		y2 = maxHeight;

	bool canClipRight = false;
	if (x2 > win_width)
		canClipRight = true;
	bool canClipLeft = false;
	if (x2 + w2 < 0)
		canClipLeft = true;

	int clipX, clipX2;

	while (y1 != y2)
	{
		suma += incre;
		sumaW += increW;

		x1 += move * floor(suma);
		suma -= floor(suma);

		w1 += add * floor(sumaW);
		sumaW -= floor(sumaW);

		if (canClipRight && x1 > win_width)
		{
			break;
		}
		if (canClipLeft && x1 + w1 < 0)
		{
			break;
		}

		if (x1 < 0)
			clipX = 0;
		else
			clipX = x1;

		if (x1 + w1 > win_width)
			clipX2 = win_width;
		else
			clipX2 = x1 + w1;


		if (clipX2 >= 0 && clipX <= win_width)
			DrawHLine(y1, clipX, clipX2, c);

		y1++;
	}
}

// Draws image in given viewport-adapted coordinates
void RendererPC::DrawImage(Image* image, int x1, int y1, int x2, int y2)
{
	int w = abs(x2 - x1);
	int h = abs(y2 - y1);

	if (x2 < 0 || x1 >= win_width || y2 < 0 || y1 >= win_height)
		return;

	SDL_Rect texr; texr.x = x1; texr.y = y1; texr.w = w; texr.h = h;


	SDL_RenderCopy(_renderer, image->getImage(), NULL, &texr);
}

// Draws a portion (sprite) of an image in given viewport-adapted coordinates
void RendererPC::DrawSprite(Image* image, int x1, int y1, int x2, int y2, int srcX1, int srcY1, int srcX2, int srcY2)
{
    int w = abs(x2 - x1);
    int h = abs(y2 - y1);

    if (x2 < 0 || x1 >= win_width || y2 < 0 || y1 >= win_height)
        return;

    SDL_Rect texr; texr.x = x1; texr.y = y1; texr.w = w; texr.h = h;

	SDL_Rect texSrc; texSrc.x = srcX1; texSrc.y = srcY1; texSrc.w = abs(srcX2 - srcX1); texSrc.h = abs(srcY2 - srcY1);

    SDL_RenderCopy(_renderer, image->getImage(), &texSrc, &texr);
}

Image* RendererPC::CreateImage(const char* path)
{
  Image* image = new Image();
  image->loadFile(path, _renderer);
  return image;
}

// ========== GETTERS ==========
int RendererPC::GetWidth()
{
	return win_width;
}

int RendererPC::GetHeight()
{
	return win_height;
}

SDL_Renderer* RendererPC::getRenderer()
{
    return _renderer;
}
#endif