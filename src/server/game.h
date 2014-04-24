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
// #include "monster.h" //TODO

class Game
{
	private:
		std::vector<Player*> players;
		Map * map;
		// Monster * monster; //TODO

		int id;
		float timeout;
		bool running;
		bool colors[4] = {false};

		std::mutex map_mutex;
		std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

	public:


	private:
		int rotate(Player * p, int way);
		int take(Player * p);
		int open(Player * p);
		int step(Player * p);

	public:
		Game(float timeout, int map_id);
		~Game();
		void send(std::string message, Player * p = nullptr, int res = 0, Player * skip = nullptr);
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
		void next(Position pos, int *x, int *y);
		std::string quit_info();
		void stop();
		float get_timeout();
};
