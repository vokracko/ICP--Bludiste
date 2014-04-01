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
		Connection*conn;

	public:

	private:

	public:
		Player(Connection * conn);
		~Player();
		void work();
		void send(std::string message);
		void send_games();
};

