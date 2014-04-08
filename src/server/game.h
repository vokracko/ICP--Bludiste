/**
 * Třída vlastní hry
 * \file game.h
 * \author Lukáš Vokráčko (xvokra00)
 */

#pragma once

#include <string>
#include <vector>
#include "player.h"

class Player;
class Game
{
	private:
		//TODO map
		//TODO map->heigh, width
		std::vector<Player*> * players;

	public:


	private:

	public:
		~Game();
		void send(Player * exclude, std::string message);
		bool add_player(Player * p);
		std::string to_string();

};
