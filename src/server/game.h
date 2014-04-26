/**
 * \brief Třída celé hry, zpracovává veškeré akce hráčů a generuje zprávy pro ostatní
 * \file game.h
 * \author Lukáš Vokráčko (xvokra00)
 */

class Game;

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <chrono>
#include <future>
#include "player.h"
#include "position.h"
#include "map.h"
#include "../box.h"
#include "monster.h"

class Game
{
	private:
		int id;
		float timeout;
		bool running;
		bool colors[4] = {false};

		std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
		std::vector<Player*> players;
		Map * map;
		Monster * monster;

	public:
		std::mutex map_mutex;

	private:
		int rotate(Player * p, int way);
		int take(Player * p);
		int open(Player * p);
		int step(Player * p);

	public:
		Game(float timeout, int map_id);
		~Game();

		void kill(int color);
		void stop(bool quit = false);

		void cmd(Player * p, std::string * command);
		void set(Player * p, Position pos);
		void next(Position * pos, int *x, int *y);
		void send(std::string message, Player * p = nullptr, int move_res = 0, int state_code = 0);
		void remove_player(Player * p);
		void remove_color(Player * p);
		void set_color(Player * p);
		void end_info();

		float get_timeout();
		int get_id();

		Map * get_map();
		std::string to_string();

		bool add_player(Player * p);
		bool is_running();
};
