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
		Connection(boost::asio::io_service & ios);
		void handle_write();

	public:

		void write(std::string message);
		// boost::asio::ip::tcp::socket get_socket(); TODO

		static Connection * create(boost::asio::io_service & ios)
		{
			Connection * pointer =new Connection(ios);
			return pointer;
		}
};


#endif
