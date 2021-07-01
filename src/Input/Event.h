#pragma once

enum class TypeEvent {
	MOVE_RIGHT, MOVE_LEFT, MOVE_FORWARD, MOVE_BACKWARD, 
	STOP_RIGHT, STOP_LEFT, STOP_FORWARD, STOP_BACKWARD, 
	STOP, EXIT
};

struct Event {
	TypeEvent type;
};