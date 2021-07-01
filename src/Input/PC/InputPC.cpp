#ifdef PLATFORM_PC

#include "InputPC.h"
#include "SDL.h"
#include "Platform/Platform.h"

#include <iostream>
#include <stdio.h>

std::vector<Event> InputPC::_events;
InputObserver* InputPC::_inputOberver;

void InputObserver::init()
{
    _deadZone = 3200;
    _controllerMinValue = 1500;
    _lastXAxis = 0;
}

//Called from platfrom and calls to procces input
void InputObserver::processEvent(SDL_Event ev)
{
    if (SDL_GameControllerOpen(0) != NULL) {
        processControllerEvent(ev);
    }

    processKeyboardEvent(ev);
}


//Process input from keyboard
void InputObserver::processKeyboardEvent(SDL_Event ev) {
    Event e;
    // Start movements on key down
    if (ev.type == SDL_KEYDOWN) {
        // FORWARD movement
        if (ev.key.keysym.sym == SDLK_w || ev.key.keysym.sym == SDLK_UP)
        {
            e.type = TypeEvent::MOVE_FORWARD;
            InputPC::Add_Events(e);
        }
        // LEFT movement
        else if (ev.key.keysym.sym == SDLK_a || ev.key.keysym.sym == SDLK_LEFT)
        {
            e.type = TypeEvent::MOVE_LEFT;
            InputPC::Add_Events(e);
        }
        // BACKWARD movement
        else if (ev.key.keysym.sym == SDLK_s || ev.key.keysym.sym == SDLK_DOWN)
        {
            e.type = TypeEvent::MOVE_BACKWARD;
            InputPC::Add_Events(e);
        }
        // RIGHT movement
        else if (ev.key.keysym.sym == SDLK_d || ev.key.keysym.sym == SDLK_RIGHT)
        {
            e.type = TypeEvent::MOVE_RIGHT;
            InputPC::Add_Events(e);
        }

    }
    // End movements on key up
    else if (ev.type == SDL_KEYUP) {
        // FORWARD movement
        if (ev.key.keysym.sym == SDLK_w || ev.key.keysym.sym == SDLK_UP)
        {
            e.type = TypeEvent::STOP_FORWARD;
            InputPC::Add_Events(e);
        }
        // LEFT movement
        else if (ev.key.keysym.sym == SDLK_a || ev.key.keysym.sym == SDLK_LEFT)
        {
            e.type = TypeEvent::STOP_LEFT;
            InputPC::Add_Events(e);
        }
        // BACKWARD movement
        else if (ev.key.keysym.sym == SDLK_s || ev.key.keysym.sym == SDLK_DOWN)
        {
            e.type = TypeEvent::STOP_BACKWARD;
            InputPC::Add_Events(e);
        }
        // RIGHT movement
        else if (ev.key.keysym.sym == SDLK_d || ev.key.keysym.sym == SDLK_RIGHT)
        {
            e.type = TypeEvent::STOP_RIGHT;
            InputPC::Add_Events(e);
        }
    }
}

// Process Input from controller
void InputObserver::processControllerEvent(SDL_Event ev) {
    Event e;

    // Horizontal movement with sticks
    if (ev.type == SDL_JOYAXISMOTION) {
        Sint16 xAxis = SDL_GameControllerGetAxis(SDL_GameControllerOpen(0), SDL_CONTROLLER_AXIS_LEFTX);

        if (abs(_lastXAxis - xAxis) > _controllerMinValue)
        {
            // LEFT movement
            if (xAxis < -_deadZone) {
                e.type = TypeEvent::MOVE_LEFT;
                InputPC::Add_Events(e);
            }
            // RIGHT movement
            else if (xAxis > _deadZone) {
                e.type = TypeEvent::MOVE_RIGHT;
                InputPC::Add_Events(e);
            }
            // No movement while within dead zone
            else {
                e.type = TypeEvent::STOP_LEFT;
                InputPC::Add_Events(e);
                e.type = TypeEvent::STOP_RIGHT;
                InputPC::Add_Events(e);
            }
        }
        _lastXAxis = xAxis;

        // Start movements on key down
    }
    else if (ev.type == SDL_JOYBUTTONDOWN) {
        // FORWARD movement
        if (SDL_GameControllerGetButton(SDL_GameControllerOpen(0), SDL_CONTROLLER_BUTTON_A)) {
            e.type = TypeEvent::MOVE_FORWARD;
            InputPC::Add_Events(e);
        }
        // BACKWARD movement
        if (SDL_GameControllerGetButton(SDL_GameControllerOpen(0), SDL_CONTROLLER_BUTTON_B)) {
            e.type = TypeEvent::MOVE_BACKWARD;
            InputPC::Add_Events(e);
        }

        // Stop movements on key up
    }
    else if (ev.type == SDL_JOYBUTTONUP) {
        // FORWARD movement
        if (!SDL_GameControllerGetButton(SDL_GameControllerOpen(0), SDL_CONTROLLER_BUTTON_A)) {
            e.type = TypeEvent::STOP_FORWARD;
            InputPC::Add_Events(e);
        }

        // BACKWARD movement
        if (!SDL_GameControllerGetButton(SDL_GameControllerOpen(0), SDL_CONTROLLER_BUTTON_B)) {
            e.type = TypeEvent::STOP_BACKWARD;
            InputPC::Add_Events(e);
        }
    }
}

// Initialize input
void InputPC::Init()
{
	_inputOberver = new InputObserver();
    _inputOberver->init();
	PlatformPC::RegisterObserver(_inputOberver);
}

// Release all resources used by input
void InputPC::Release()
{
    delete _inputOberver;
}

// Add an event to events list
void InputPC::Add_Events(Event e)
{
    _events.push_back(e);
}

// Return events list
std::vector<Event> InputPC::Get_Events()
{
    std::vector<Event> events;
    events = _events;
    _events.clear();
    return events;
}

#endif