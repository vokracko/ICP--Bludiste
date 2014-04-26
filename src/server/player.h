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
		Connection * conn = nullptr;
		std::thread thread;
		std::string read_message;
		Game * game = nullptr;
		Position position;
		std::chrono::time_point<std::chrono::system_clock> start;


	private:
		void send_games();
		void send_map_list();
		void send_map(bool firt_time = false);
		void send_invalid();

	public:
		Player(Connection * conn);
		~Player();

		bool init();
		void work();
		int get_id();

		void send(std::string * message, int mode = Connection::ASYNC);
		void receive(std::string * target, int mode = Connection::ASYNC);

		int get_color();
		void set_color(int color);
		void set_position(Position pos);
		Position get_position();
		void inc_step();
		std::string end_info();

		bool has_key();
		void take_key();

		void send_quit();

};

