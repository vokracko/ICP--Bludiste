/**
 * Server se stará o obsluhu nově příchozích požadavků na hry
 * \file server.h
 * \author Lukáš Vokráčko (xvokra00)
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <vector>
#include "connection.h"
#include "game.h"
#include "player.h"

//TODO uchovávat hráče

class Game;
class Server
{
	public:
		static boost::asio::io_service * ios;
		static const int PORT = 1234;

	private:
		boost::asio::ip::tcp::acceptor acceptor;
		std::vector<Game *> games;
		std::vector<Player *> orphans;
		Connection * last_connection;

	public:
		~Server();
		static Server * get_instance();
		static void create(boost::asio::io_service * ios);
		static void kill(int sig);

		void listen();

		std::string get_games_string();
		void stop();

	private:
		void accept_player(Connection * conn, const boost::system::error_code& e);
		Server(boost::asio::io_service & ios);
};
