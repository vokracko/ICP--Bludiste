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
void Connection::start()
{
	std::string str = "co je to za shit\r\n";
	boost::asio::async_write(
		socket,
		boost::asio::buffer(str),
		boost::bind(&Connection::handle_write, shared_from_this())
	);
}
