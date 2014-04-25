
class Monster;

#pragma once

#include <unistd.h>
#include <thread>
#include "position.h"
#include "game.h"
#include "player.h"

class Monster
{
	long timeout;
	Game * game;
	Position pos;
	std::thread thread;

	public:
		Monster(Game * game, float timeout);
		~Monster();
		void work();
};
