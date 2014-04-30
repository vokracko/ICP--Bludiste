/**
 * \brief Třída hráče, stará se o zasílání zpráv a uchovává informace o jeho pozici, barvě a klíči
 * \file player.h
 * \author Lukáš Vokráčko (xvokra00)
 */

class Player;

#pragma once

#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <vector>
#include <chrono>
#include "server.h"
#include "game.h"
#include "connection.h"
#include "position.h"

class Player
{
	private:
		int id;
		int color;
		int step_count = 0;
		bool own_key = false;
		bool ok = true;

		Connection * conn = nullptr;
		std::thread thread;
		std::thread go_thread;
		std::string read_message;
		Game * game = nullptr;
		Position position;
		std::chrono::time_point<std::chrono::system_clock> start;

	public:
		bool go = false;

	private:
		void send_games();
		void send_map_list();
		void send_map(bool firt_time = false);
		void send_invalid();
		void go_timer();

	public:
		Player(Connection * conn);
		~Player();

		bool init();
		void work();
		int get_id();

		void send(std::string * message, int mode = Connection::SYNC);
		void receive(std::string * target, int mode = Connection::SYNC);

		int get_color();
		void set_color(int color);
		void set_position(Position pos);
		Position get_position();
		void inc_step();
		std::string end_info();

		bool has_key();
		void take_key();

		void send_quit();

		void go_start();
		void go_stop();
};

