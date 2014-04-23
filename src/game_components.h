#pragma once

enum game_components
{
	RED_UP=41,
	RED_DOWN=43,
	RED_LEFT=42,
	RED_RIGHT=44,

	BLUE_UP=61,
	BLUE_DOWN=63,
	BLUE_LEFT=62,
	BLUE_RIGHT=64,

	WHITE_UP=71,
	WHITE_DOWN=73,
	WHITE_LEFT=72,
	WHITE_RIGHT=74,

	GREEN_UP=51,
	GREEN_DOWN=53,
	GREEN_LEFT=52,
	GREEN_RIGHT=54,

	MONSTER_UP=81,
	MONSTER_DOWN=83,
	MONSTER_LEFT=82,
	MONSTER_RIGHT=84,

	KEY=90,
	WALL=110,
	EMPTY=120,
	GATE_OPEN=105,
	GATE_CLOSE=106,
};

enum player_color
{
	RED=4,
	WHITE=7,
	GREEN=5,
	BLUE=6,
};