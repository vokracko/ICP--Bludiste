#include "server.h"

boost::asio::io_service * Server::ios;

/**
 * Čeká na příchozí spojení o klientů
 * \fn void Server::listen()
 */
void Server::listen()
{
	Connection * conn = new Connection(acceptor.get_io_service());
	// boost::asio::ip::tcp::socket socket = conn->get_socket();
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
		Player * player = new Player(conn);
		orphans.push_back(player);

		listen();
	}
	else
	{
		std::cout << "Chyba při spojení" << std::endl;
	}
}

std::string Server::get_games_string()
{
	std::vector<Game *> games = Server::get_instance()->games;
	std::string message;

	if(games.size())
	{
		for(std::vector<Game*>::iterator it = games.begin(); it != games.end(); ++it)
		{
			message.append((*it)->to_string() + "\r\n");
		}
	}
	else
	{
		message = "0\r\n";
	}
	return message;
}

Game * Server::assign(int game_id, Player * player)
{
	Game * game_pointer = nullptr;

	for(std::vector<Game *>::iterator it = games.begin(); it != games.end(); ++it)
	{
		if((*it)->get_id() == game_id)
		{
			game_pointer = *it;
			break;
		}
	}

	if(game_pointer == nullptr) return false;

	if(game_pointer->add_player(player))
	{
		remove_orphan(player);
		return game_pointer;
	}

	return nullptr;
}

int Server::new_game(std::string & game_settings)
{
	size_t pos;
	int map_id;
	float timeout;

	try
	{
		timeout = std::stof(game_settings, &pos);
		game_settings = game_settings.substr(pos+1);
		map_id = std::stoi(game_settings);
	}
	catch(std::exception & e) // nevalidní data
	{
		return 0;
	}

	if(!Map::exists(map_id)) return 0;


	games.push_back(new Game(timeout, map_id));

	return games.back()->get_id();
}

void Server::delete_game(Game * g)
{
	for(std::vector<Game *>::iterator it = games.begin(); it != games.end(); ++it)
	{
		if(*it == g)
		{
			it = games.erase(it);
			delete g;
			break;
		}
	}
}

void Server::remove_orphan(Player * p)
{
	for(std::vector<Player *>::iterator it = orphans.begin(); it != orphans.end(); ++it)
	{
		if(*it == p)
		{
			orphans.erase(it);
			break;
		}
	}
}

void Server::add_orphan(Player * p)
{
	orphans.push_back(p);
}

Server * Server::get_instance()
{

	static Server instance(*(Server::ios));
	return &instance;
}

void Server::create(boost::asio::io_service * ios)
{
	Server::ios = ios;
	Map::init();
}

void Server::kill(int sig)
{
	std::vector<Game *> games = Server::get_instance()->games;
	for(std::vector<Game *>::iterator it = games.begin(); it != games.end(); ++it)
	{
		(*it)->stop();
	}


	Server::get_instance()->stop();
}

void Server::stop()
{
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

	delete last_connection;
}

int Server::get_player_id()
{
	static int id = 0;
	return ++id;
}

int Server::get_game_id()
{
	static int id = 0;
	return ++id;
}

Server::Server(boost::asio::io_service & ios): acceptor(ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), PORT))
{

}

Server::~Server()
{

}
