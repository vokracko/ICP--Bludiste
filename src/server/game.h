/**
 * Třída vlastní hry
 * \file game.h
 * \author Lukáš Vokráčko (xvokra00)
 */

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "player.h"
// #include "map.h" //TODO

class Player;
class Game
{
	private:
		std::vector<Player*> * players;
		int id;
		int map;
		float timeout;
		// Map * map; //TODO

	public:


	private:

	public:
		Game(float timeout, int map);
		~Game();
		void send(Player * exclude, std::string message);
		bool add_player(Player * p);
		int get_id();
		std::string to_string();

};
