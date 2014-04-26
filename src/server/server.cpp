/**
 * \file server.cpp
 * \author Lukáš Vokráčko (xvokra00)
 */

#include "server.h"

boost::asio::io_service * Server::ios;

/**
 * \fn void Server::listen()
 * \brief Čeká na příchozí spojení od klientů
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
 * \fn void Server::accept_player(Connection::pointer conn, const boost::system::error_code& e)
 * \brief Ověřuje příchozí spojení
 * \param[in] conn příchozí spojení
 * \param[in] e chybový kód spojení
 */
void Server::accept_player(Connection * conn, const boost::system::error_code& e)
{
	if(!e)
	{
		Player * player = new Player(conn);
		add_orphan(player);

		listen();
	}
	else
	{
		Server::kill(0);
	}
}

/**
 * \fn std::string Server::get_games_string()
 * \brief Uloží informace o probíhajících hrách do jednoho řetězce
 * \return message
 */
std::string Server::get_games_string()
{
	std::vector<Game *> games = Server::get_instance()->games;
	std::string message;

	if(games.size())
	{
		for(std::vector<Game*>::iterator it = games.begin(); it != games.end(); ++it)
		{
			if(!(*it)->is_running()) continue;
			message.append((*it)->to_string() + "\r\n");
		}
	}
	else
	{
		message = "0\r\n";
	}
	return message;
}

/**
 * \fn Game * Server::assign(int game_id, Player * player)
 * \brief Připojí hráče ke hře
 * \param[in] game_id identifikátor hry
 * \param[in] player ukazatel na připojováního hráče
 * \return ukazatel na hru, kam se připojil
 */
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

/**
 * \fn int Server::new_game(std::string & game_settings)
 * \brief Vytvoří novou hru
 * \param[in] game_setting nastavení hry
 * \return identifikátor hry
 */
int Server::new_game(std::string & game_settings)
{
	size_t pos;
	int map_id;
	float timeout;

	for(std::vector<Game *>::iterator it = games.begin(); it != games.end(); ++it)
	{
		if(!(*it)->is_running())
		{
			delete_game(*it);
		}
	}

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

/**
 * \fn void Server::delete_game(Game * g)
 * \brief Smaže hru
 * \param[in] g ukazatel na hru, jež se má smazat
 */
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

/**
 * \fn void Server::remove_orphan(Player * p)
 * \brief Odstraní hráče, jež není připojen k žádné hře
 * \param[in] p ukazatel na hráče, jež se má odstranit
 */
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

/**
 * \fn void Server::add_orphan(Player * p)
 * \brief Uchová hráče bez připojení ke hře
 * \param[in] p ukazatel na hráče
 */
void Server::add_orphan(Player * p)
{
	orphans.push_back(p);
}

/**
 * \fn Server * Server::get_instance()
 * \brief Vytvoří/vrátí instanci serveru
 * \return instance
 */
Server * Server::get_instance()
{

	static Server instance(*(Server::ios));
	return &instance;
}

/**
 * \fn void Server::create(boost::asio::io_service * ios)
 * \brief Inicializuje io_service a seznam map
 * \param[in] ios io_service
 * \see Map::init()
 */
void Server::create(boost::asio::io_service * ios)
{
	Server::ios = ios;
	Map::init();
}

/**
 * \fn void Server::kill(int sig)
 * \brief Odchytává ctrl+c, zastaví io_service
 * \param[in] sig číslo signálu
 */
void Server::kill(int sig)
{
	std::cout << "server::kill" << std::endl;
	std::vector<Game *> games = Server::get_instance()->games;
	std::cout << "stop games" << std::endl;
	for(std::vector<Game *>::iterator it = games.begin(); it != games.end(); ++it)
	{
		if((*it)->is_running()) (*it)->stop(true);
	}

	Server::get_instance()->stop();
}

/**
 * \fn void Server::stop()
 * \brief Zastaví server, smaže všechny hry a hráče bez her
 */
void Server::stop()
{
	std::cout << "server::stop" << std::endl;
	Server::ios->stop();
	acceptor.close();

	std::cout << "delte games" << std::endl;
	for(std::vector<Game *>::iterator it = games.begin(); it != games.end(); ++it)
	{
		delete *it;
	}

	games.clear();

	std::cout << "delte orphans" << std::endl;
	for(std::vector<Player *>::iterator it = orphans.begin(); it != orphans.end(); ++it)
	{
		std::cout << " N ";
		delete *it;
	}

	orphans.clear();

	std::cout << "delet last conn" << std::endl;
	delete last_connection;
}

/**
 * \fn int Server::get_player_id()
 * \brief Generátor identifikátorů hráčů
 * \return identifikátor hráče
 */
int Server::get_player_id()
{
	static int id = 0;
	return ++id;
}

/**
 * \fn int Server::get_player_id()
 * \brief Generátor identifikátorů her
 * \return identifikátor hry
 */
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
