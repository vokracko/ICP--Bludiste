/**
 * Server se stará o obsluhu nově příchozích požadavků na hry a připojování klientů
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
		Connection * last_connection;
		boost::asio::ip::tcp::acceptor acceptor;
		std::vector<Player *> orphans;

	private:
		Server(boost::asio::io_service & ios);
		void accept_player(Connection * conn, const boost::system::error_code& e);


	public:
		static Server * get_instance();
		static void create(boost::asio::io_service * ios);
		static void kill(int sig);

		~Server();
		void stop();
		void listen();

		int get_game_id();
		int new_game(std::string & game_settings);
		Game * assign(int game_id, Player * player);
		void delete_game(Game * g);
		std::string get_games_string();

		int get_player_id();
		void add_orphan(Player * p);
		void remove_orphan(Player * p);

};
