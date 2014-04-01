#include "server.h"

boost::asio::io_service * Server::ios = nullptr;

/**
 * Čeká na příchozí spojení o klientů
 * \fn void Server::listen()
 */
void Server::listen()
{
	Connection * conn(Connection::create(acceptor.get_io_service()));

	acceptor.async_accept(
		conn->socket,
		boost::bind(&Server::accept_player, this, conn, boost::asio::placeholders::error)
	);
}

/**
 * Ověřuje příchozí spojení
 * \fn void Server::accept_player(Connection::pointer conn, const boost::system::error_code& e)
 * \param conn příchozí spojení
 * \param e chybový kód spojení
 */
void Server::accept_player(Connection * conn, const boost::system::error_code& e)
{
	if(!e)
	{
		std::cout << "Přijaté spojení" << std::endl;
		Player * player = new Player(conn);
		std::thread player_thread(&Player::work, *player);
		player_thread.join(); //TODO ukládat thready
		listen();
	}
	else
	{
		std::cout << "Chyba při spojení" << std::endl;
	}
}

std::string Server::get_games_string()
{
	std::vector<Game *> * games = Server::get_instance()->get_games();
	std::string message;

	for(std::vector<Game*>::iterator it = games->begin(); it != games->end(); ++it)
	{
		message.append((*it)->to_string() + "\r\n");
	}
	return message;
}

std::vector<Game *> * Server::get_games()
{
	return games;
}

boost::shared_ptr<Server> Server::get_instance()
{

	static boost::shared_ptr<Server> instance(new Server(*(Server::ios)));
	return instance;
}

void Server::create(boost::asio::io_service * ios)
{
	Server::ios = ios;
}

Server::Server(boost::asio::io_service & ios): acceptor(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT))
{
	games = new std::vector<Game*>;
}

Server::~Server()
{
	delete games;
}
