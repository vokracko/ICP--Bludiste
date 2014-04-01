#include "connection.h"

Connection::Connection(boost::asio::io_service & ios): socket(ios)
{
}

void Connection::handle_write()
{
}

// boost::asio::ip::tcp::socket Connection::get_socket()
// {
// 	return socket;
// TODO předělat ať nemusí být public
// }

/**
 * Zahájení spojení
 * \fn void Connection::start()
 */
void Connection::write(std::string message)
{
	boost::asio::async_write(
		socket,
		boost::asio::buffer(message),
		boost::bind(&Connection::handle_write, this)
	);
}
