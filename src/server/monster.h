/**
 * \brief Třída hlídače bludiště
 * \file monster.h
 * \author Lukáš Vokráčko (xvokra00)
 */

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

	private:
		int rotate(int look, int way);
		void new_way(Position * current);
		bool isPlayer(unsigned char obj);
};
