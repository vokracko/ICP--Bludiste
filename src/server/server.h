/**
 * Server se stará o obsluhu nově příchozích požadavků na hry
 * \file server.h
 * \author Lukáš Vokráčko (xvokra00)
*/

#ifndef _H_SERVER
#define _H_SERVER

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "connection.h"

class Server
{
	boost::asio::ip::tcp::acceptor acceptor;

	public:
		Server(boost::asio::io_service & ios): acceptor(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234)) {};
		void listen();
		void accept_client(Connection::pointer conn, const boost::system::error_code& e);
};

#endif
