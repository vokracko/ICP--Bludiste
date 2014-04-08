/**
 * Třída spojení
 * \file connetion.h
 * \author Lukáš Vokráčko (xvokra00)
 */

#ifndef _H_CONNECTION
#define _H_CONNECTION

#include <boost/bind.hpp>
#include <boost/asio.hpp>

class Connection
{
	private:

	public:
		boost::asio::ip::tcp::socket socket;

	private:
		void handle_read(std::string * message);

	public:
		Connection(boost::asio::io_service & ios);
		~Connection();
		void write(std::string message);
		void read(std::string * target);
};


#endif
