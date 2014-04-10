#include "game.h"

Game::Game(float timeout, int map)
{
	id = Server::get_instance()->get_game_id();
	this->timeout = timeout;
	// this->map = Server::get_instance()->get_map(map);
}

Game::~Game()
{
	std::cout << "game~players"<<std::endl;
	players->clear();
}

/**
 * Pošle zprávu o změně stavu hry vše klientům kromě toho, který tuto zprávu vytvořil
 * \fn void Game::send(Player * exclude, std::string message)
 * \param exclude odkaz na hráče, který zprávu vytvořil
 * \param message obsah zprávy
 */
void Game::send(Player * exclude, std::string message)
{
	for(std::vector<Player*>::iterator it = players->begin(); it != players->end(); ++it)
	{
		if((*it) == exclude) continue;

		(*it)->send(&message);
	}
}


/**
 * Připojí hráče do hry
 * \fn bool Game::add_Player(Player * c)
 * \param c odkaz na hráče
 * \return výsledek operace
 */
bool Game::add_player(Player * p)
{
	if(players->size() < 4)
	{
		players->push_back(p);
		//TODO posílat mapu
		return true;
	}

	return false;
}

std::string Game::to_string()
{
	std::string message;

	message.append(players->size() + " ");
	return message;
	//TODO informace o mapě
}

//TODO mazat klienty

int Game::get_id()
{
	return id;
}
