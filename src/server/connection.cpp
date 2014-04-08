#include "connection.h"

Connection::Connection(boost::asio::io_service & ios): socket(ios)
{

}

Connection::~Connection()
{
	std::cout << "killing conn" << std::endl;
	socket.close();
}

void Connection::handle_read(std::string * message)
{
	*message = "x";
	//odblokovat semafor


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
	//TODO předělat na frontu
	// boost::asio::async_write(socket, boost::asio::buffer(message));
}

void Connection::read(std::string * target)
{
	//TODO aktivovat semafor;
	// boost::asio::asio_read_some();
}
