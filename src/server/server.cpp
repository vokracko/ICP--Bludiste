#include "server.h"

/**
 * Čeká na příchozí spojení o klientů
 * \fn void Server::listen()
 */
void Server::listen()
{
	Connection::pointer conn(Connection::create(acceptor.get_io_service()));

	acceptor.async_accept(
		conn->socket,
		boost::bind(
			&Server::accept_client, this, conn,
			boost::asio::placeholders::error
		)
	);
}

/**
 * Ověřuje příchozí spojení
 * \fn void Server::accept_client(Connection::pointer conn, const boost::system::error_code& e)
 * \param conn příchozí spojení
 * \param e chybový kód spojení
 */
void Server::accept_client(Connection::pointer conn, const boost::system::error_code& e)
{
	if(!e)
	{
		std::cout << "Přijaté spojení" << std::endl;
		conn->start();
		listen();
	}
	else
	{
		std::cout << "Chyba při spojení" << std::endl;
	}
	// Client c;
	// c.work();

}
