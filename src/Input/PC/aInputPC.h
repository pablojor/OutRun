#pragma once
#ifdef PLATFORM_PC

#include <vector>
#include "Input/Event.h";

class InputPC
{
public:
	// Process SDL events
	static std::vector<Event> Procces_Events();
};
#endif