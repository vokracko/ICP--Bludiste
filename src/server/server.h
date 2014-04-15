/**
 * Server se stará o obsluhu nově příchozích požadavků na hry
 * \file server.h
 * \author Lukáš Vokráčko (xvokra00)
*/

class Server;

#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <vector>
#include "connection.h"
#include "game.h"
#include "player.h"

class Server
{
	public:
		static boost::asio::io_service * ios;
		static const int PORT = 1234;

		std::vector<Game *> games;
	private:
		boost::asio::ip::tcp::acceptor acceptor;
		std::vector<Player *> orphans;
		Connection * last_connection;

	public:
		~Server();
		static Server * get_instance();
		static void create(boost::asio::io_service * ios);
		static void kill(int sig);


		int get_player_id();
		int get_game_id();
		void listen();

		std::string get_games_string();
		void stop();
		Game * assign(int game_id, Player * player);
		int new_game(std::string & game_settings);
		void add_orphan(Player * p);
		void delete_game(Game * g);

	private:
		Server(boost::asio::io_service & ios);
		void accept_player(Connection * conn, const boost::system::error_code& e);
		void remove_orphan(Player * p);
};
