#pragma once
#ifdef PLATFORM_PC

#include <vector>
#include "Input/Event.h"
#include "Platform/Platform.h"
#include "SDL_gamecontroller.h"

class InputObserver : public EventObserver
{
private:
	int _deadZone, _controllerMinValue, _lastXAxis;

public:
	void init();

	// Called from platfrom and calls to procces input
	virtual void processEvent(SDL_Event ev);

	// Process Input from PS4 controller
	void processControllerEvent(SDL_Event ev);

	// Process Input keyboard
	void processKeyboardEvent(SDL_Event ev);
};

class InputPC 
{
private:
	static InputObserver* _inputOberver;
	static std::vector<Event> _events;

public:
	// Initialize input
	static void Init();

	// Release all resources used by input
	static void Release();

	// Add an event to events list
	static void Add_Events(Event e);

	// Return events list
	static std::vector<Event> Get_Events();
};
#endif