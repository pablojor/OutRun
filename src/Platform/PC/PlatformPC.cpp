#ifdef PLATFORM_PC

#include "PlatformPC.h"
#include "SDL.h"

#include <iostream>
#include <stdio.h>

std::vector<EventObserver*> PlatformPC::_observers;

// Initialize SDL checking for errors
void PlatformPC::Init()
{
    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER) != 0) {
        std::cout << "error" << "\n";
    }
}

// Close SDL
void PlatformPC::Release()
{
    SDL_Quit();
}

// Process SDL events
bool PlatformPC::Tick()
{
	bool exit = true;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT || event.type == SDL_MOUSEBUTTONDOWN)
			exit = false;
		else
		{
			for (int i = 0; i < _observers.size(); i++)
				_observers[i]->processEvent(event);
		}
			
    }

    return exit;
}

// Does nothing, just fills parent template
void PlatformPC::SetVibration(uint8_t vib)
{
	return;
}

// Transforms uint32_t to uint8_t array and returns it as reference
void PlatformPC::Uint32_to_Uint8(uint32_t color, uint8_t * result)
{
	result[0] = (color >> 24 & 0x000000ff);
	result[1] = (color >> 16 & 0x000000ff);
	result[2] = (color >> 8 & 0x000000ff);
	result[3] = (color & 0x000000ff);
}

// Return system time
double PlatformPC::Get_Time()
{
    return SDL_GetTicks() / 1.0e3;
}

//Puts the entire file in a buffer
void* PlatformPC::Get_Buffer_From_File(const char * filepath)
{
	FILE * pFile;
	pFile = fopen(filepath, "rb");

	if (pFile == NULL) {
		fputs("File error", stderr);
		return nullptr;
	}

	fseek(pFile, 0, SEEK_END);
	long fsize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	void* buffer = malloc(fsize);
	fread(buffer, 1, fsize, pFile);
	fclose(pFile);

	return buffer;
}

// Adds a new observer to the list
void PlatformPC::RegisterObserver(EventObserver* obsever)
{
	_observers.push_back(obsever);
}

// Transforms an uint32_t from Big Endian to Little Endian
uint32_t PlatformPC::Big_to_Little(uint32_t big)
{
	return SDL_Swap32(big);
}

#endif