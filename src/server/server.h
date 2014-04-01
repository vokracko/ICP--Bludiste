/**
 * Server se stará o obsluhu nově příchozích požadavků na hry
 * \file server.h
 * \author Lukáš Vokráčko (xvokra00)
*/

#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <thread>
#include <vector>
#include "connection.h"
#include "game.h"
#include "player.h"

//TODO uchovávat hráče

class Game;
class Server: public boost::enable_shared_from_this<Server>
{
	public:
		static boost::asio::io_service * ios;
		static const int PORT = 1234;

	private:
		boost::asio::ip::tcp::acceptor acceptor;
		std::vector<Game *> * games;

	public:
		static void create(boost::asio::io_service * ios);
		static boost::shared_ptr<Server> get_instance();

		void listen();

		std::string get_games_string();
		std::vector<Game *> * get_games();

		~Server();

	private:
		void accept_player(Connection * conn, const boost::system::error_code& e);
		Server(boost::asio::io_service & ios);
};
