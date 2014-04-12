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
#include "map.h"

class Game
{
	private:
		std::vector<Player*> players;
		Map * map;

		int id;
		int map_id;
		float timeout;
		bool running;
		bool colors[4] = {false};

		std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

	public:


	private:
		void turn_right(int player_id);
		void turn_left(int player_id);

	public:
		Game(float timeout, int map_id);
		~Game();
		void send(std::string message);
		bool add_player(Player * p);
		int get_id();
		std::string to_string();
		bool is_running();
		void remove_player(Player * p);
		void set(int player_id, std::string * command);
		void remove_color(Player * p);
		void set_color(Player * p);
		Map * get_map();
		void stop();
};
