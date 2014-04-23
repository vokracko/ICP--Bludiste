/**
 * Třída vlastní hry
 * \file game.h
 * \author Lukáš Vokráčko (xvokra00)
 */

class Game;

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include "player.h"
#include "position.h"
#include "map.h"
#include "box.h"

class Game
{
	private:
		std::vector<Player*> players;
		Map * map;

		int id;
		float timeout;
		bool running;
		bool colors[4] = {false};

		std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

	public:


	private:
		bool rotate(Player * p, int way);
		bool take(Player * p);
		bool open(Player * p);

		void next(Position pos, int *x, int *y);

	public:
		Game(float timeout, int map_id);
		~Game();
		void send(std::string message, Player * p = nullptr, int res = 0);
		bool add_player(Player * p);
		int get_id();
		std::string to_string();
		bool is_running();
		void remove_player(Player * p);
		bool cmd(Player * p, std::string * command);
		void set(Player * p, Position pos);
		void remove_color(Player * p);
		void set_color(Player * p);
		Map * get_map();
		void stop();
};
