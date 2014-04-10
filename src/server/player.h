#pragma once

#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <vector>
#include <chrono>
#include "server.h"
#include "game.h"
#include "connection.h"

class Game;
class Player
{
	private:
		int id;
		Connection * conn = nullptr;
		std::thread thread;
		std::string read_message;
		Game * game;

	public:

	private:

	public:
		Player(Connection * conn);
		~Player();
		bool init();
		void work();
		void send(std::string * message, int mode = Connection::ASYNC);
		void receive(std::string * target, int mode = Connection::ASYNC);
		void send_games();
		void send_invalid();
		void send_play();
};

