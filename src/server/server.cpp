#include "server.h"

boost::asio::io_service * Server::ios;

/**
 * Čeká na příchozí spojení o klientů
 * \fn void Server::listen()
 */
void Server::listen()
{
	Connection * conn = new Connection(acceptor.get_io_service());
	last_connection = conn;

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
		orphans.push_back(player);

		listen();
	}
	else
	{
		std::cout << "Chyba při spojení" << std::endl;
	}

	//TODO nějak uchovávat hráče
}

std::string Server::get_games_string()
{
	std::vector<Game *> games = Server::get_instance()->games;
	std::string message;

	for(std::vector<Game*>::iterator it = games.begin(); it != games.end(); ++it)
	{
		message.append((*it)->to_string() + "\r\n");
	}
	return message;
}

Server * Server::get_instance()
{

	static Server instance(*(Server::ios));
	return &instance;
}

void Server::create(boost::asio::io_service * ios)
{
	Server::ios = ios;

	std::cout << sizeof(Server) << std::endl;
	std::cout << sizeof(Player) << std::endl;
	std::cout << sizeof(Game) << std::endl;
	std::cout << sizeof(Connection) << std::endl;
	std::cout << sizeof(boost::asio::io_service) << std::endl;
	std::cout << sizeof(games) << std::endl;
	std::cout << sizeof(orphans) << std::endl;
}

void Server::kill(int sig)
{
	Server::get_instance()->stop();
}

void Server::stop()
{
	std::cout << sizeof(Server) << std::endl;
	std::cout << sizeof(Player) << std::endl;
	std::cout << sizeof(Game) << std::endl;
	std::cout << sizeof(Connection) << std::endl;
	std::cout << sizeof(boost::asio::io_service) << std::endl;
	std::cout << sizeof(games) << std::endl;
	std::cout << sizeof(orphans) << std::endl;

	std::cout << orphans.size() << std::endl;

	Server::ios->stop();
	acceptor.close();

	for(std::vector<Player *>::iterator it = orphans.begin(); it != orphans.end(); ++it)
	{
		delete *it;
	}

	for(std::vector<Game *>::iterator it = games.begin(); it != games.end(); ++it)
	{
		delete *it;
	}

	orphans.clear();
	games.clear();

	std::cout << orphans.size() << std::endl;

	delete last_connection;
}


Server::Server(boost::asio::io_service & ios): acceptor(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT))
{

}

Server::~Server()
{

}
