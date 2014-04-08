#pragma once

#include <boost/asio/ip/address_v4.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <vector>
#include <chrono>
#include "server.h"
#include "connection.h"

class Player
{
	private:
		int id;
		Connection * conn = nullptr;
		std::thread thread;
	public:

	private:

	public:
		Player(Connection * conn);
		~Player();
		bool connect();
		void work();
		void send(std::string message);
		void receive();
		void send_games();
};

