#include "game.h"

/**
 * Pošle zprávu o změně stavu hry vše klientům kromě toho, který tuto zprávu vytvořil
 * \fn void Game::send(Client * exclude, std::string message)
 * \param exclude odkaz na klienta, který zprávu vytvořil
 * \param message obsah zprávy
 */
void Game::send(Client * exclude, std::string message)
{
	for(auto c: clients)
	{
		if(c == exclude) continue;

		c->send(message);
	}
}


/**
 * Připojí klienta do hry
 * \fn bool Game::add_client(Client * c)
 * \param c odkaz na klienta
 * \return výsledek operace
 */
bool Game::add_client(Client * c)
{
	if(this->clients.size() < 4)
	{
		this->clients->push_back(c);
		return true;
	}

	return false;
}
