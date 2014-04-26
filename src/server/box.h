/**
 * \file box.h
 * \brief Výčet hodnot pro identifikaci zpráv a objektů ve hře
 * \author Lukáš Vokráčko (xvokra00)
*/
enum Box
{
	RED = 40,
	GREEN = 50,
	BLUE = 60,
	WHITE = 70,

	MONSTER = 80,
	KEY = 90,
	GATE = 100,
	WALL = 110,
	EMPTY = 120,

	UP = 1,
	LEFT = 2,
	DOWN = 3,
	RIGHT = 4,
	OPEN = 5,
	CLOSED = 6,

	DISCONNECTED = 9,
	CONNECTED = 8,
	KILLED = 7,

	MOVE_PASS = 35,
	MOVE_FAIL = 36,
	YOU_WIN = 37
};

