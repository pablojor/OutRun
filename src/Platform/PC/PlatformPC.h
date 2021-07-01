#pragma once
#ifdef PLATFORM_PC

#include <stdint.h>
#include <vector>
#include "SDL_events.h"

class EventObserver
{
public:
	virtual void processEvent(SDL_Event ev) = 0;
};

class PlatformPC
{
private:
	static std::vector<EventObserver*> _observers;

public:
	// Initialize SDL checking for errors
	static void Init();

	// Close SDL
	static void Release();

	// Process SDL events
	static bool Tick();

	// Does nothing, just fills parent template
	static void SetVibration(uint8_t vib);

	// Transforms uint32_t to uint8_t array and returns it as reference
	static void Uint32_to_Uint8(uint32_t color, uint8_t* result);

	// Return system time
	static double Get_Time();

	// Get buffer from file
	static void* Get_Buffer_From_File(const char* filepath);

	// Adds a new observer to the list
	static void RegisterObserver(EventObserver* obsever);

	// Transforms an uint32_t from Big Endian to Little Endian
	static uint32_t Big_to_Little(uint32_t big);

	
};
#endif