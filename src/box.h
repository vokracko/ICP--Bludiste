#ifndef _H_BOX
#define _H_BOX

#include <string>

enum class Box
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

	TOP = 1,
	LEFT = 2,
	BOTTOM = 3,
	RIGHT = 4,
	NONE = 0
	OPEN = 5,
	CLOSE = 6
};

#endif
