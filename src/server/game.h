/**
 * Třída vlastní hry
 * \file game.h
 * \author Lukáš Vokráčko (xvokra00)
 */

#ifndef _H_GAME
#define _H_GAME

#include <string>
#include "client.h"

class Game
{
	std::queue<Client *> clients;

	void send(Client * exclude);
	bool add_client(Client * c);
};

#endif
