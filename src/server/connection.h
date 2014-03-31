/**
 * Třída spojení
 * \file connetion.h
 * \author Lukáš Vokráčko (xvokra00)
 */

#ifndef _H_CONNECTION
#define _H_CONNECTION

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

class Connection: public boost::enable_shared_from_this<Connection>
{
	private:

	public:
		boost::asio::ip::tcp::socket socket;
		typedef boost::shared_ptr<Connection> pointer;

	private:
		Connection(boost::asio::io_service & ios);
		void handle_write();

	public:

		void start();
		// boost::asio::ip::tcp::socket get_socket();

		static pointer create(boost::asio::io_service & ios)
		{
			return pointer(new Connection(ios));
		}
};


#endif
