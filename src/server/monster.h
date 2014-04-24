
class Monster;

#pragma once

#include <unistd.h>
#include "position.h"
#include "game.h"

class Monster
{
	long timeout;
	Game * game;
	Position pos;

	public:
		Monster(Game * game, float timeout);
		void inc_step();
		void work();
};
