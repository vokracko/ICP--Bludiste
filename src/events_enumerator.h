#pragma once

#define MAX_EVENTS 10

enum game_events
{
	RED_KILLED = 47,
	GREEN_KILLED = 57,
	BLUE_KILLED = 67,
	WHITE_KILLED=77,

	RED_CONNECTED = 48,
	GREEN_CONNECTED = 58,
	BLUE_CONNECTED = 68,
	WHITE_CONNECTED = 78,

	RED_DISCONNECTED = 49,
	GREEN_DISCONNECTED = 59,
	BLUE_DISCONNECTED = 69,
	WHITE_DISCONNECTED = 79,

	MOVE_PASS = 35,
	MOVE_FAIL = 36,

	RED_KEY = 130,
	GREEN_KEY = 140,
	BLUE_KEY = 150,
	WHITE_KEY = 160,

	RED_OPEN = 45,
	GREEN_OPEN = 55,
	BLUE_OPEN = 65,
	WHITE_OPEN = 75,

	RED_WIN = 40,
	GREEN_WIN = 50,
	BLUE_WIN = 60,
	WHITE_WIN = 70,
};
