#include "game.h"

Game::Game(float timeout, int map_id)
{
	id = Server::get_instance()->get_game_id();
	this->timeout = timeout;
	running = true;
	map = new Map(map_id);
	// this->map = Server::get_instance()->get_map(map);
}

Game::~Game()
{
	for(std::vector<Player *>::iterator it = players.begin(); it != players.end(); ++it)
	{
		Server::get_instance()->add_orphan(*it);
		(*it)->work();
		players.erase(it);
	}

	delete map;
}

bool Game::is_running()
{
	return running;
}

void Game::stop()
{
	//std::chrono::duration<int> elapsed_seconds = std::chrono::system_clock::now() - start;
	//TODO poslat čas hry a další bullshity
	//TODO elapsed_seconds.count()

	running = false;

	for(std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
	{
		(*it)->send_quit();
	}

}

void Game::set(int player_id, std::string * command)
{

	//TODO
	if(*command == "left")
	{
		turn_left(player_id);
	}
	else if(*command == "right")
	{
		turn_right(player_id);
	}
	else if(*command == "take")
	{

	}
	else if(*command == "open")
	{

	}
	else if(*command == "go")
	{

	}
	else if(*command == "stop")
	{

	}
}

void Game::turn_left(int player_id)
{
	// TODO
	// map->
}

void Game::turn_right(int player_id)
{
	// TODO
}

/**
 * Pošle zprávu o změně stavu hry vše klientům kromě toho, který tuto zprávu vytvořil
 * \fn void Game::send(Player * exclude, std::string message)
 * \param exclude odkaz na hráče, který zprávu vytvořil
 * \param message obsah zprávy
 */
void Game::send(std::string message)
{
	for(std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
	{
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
	if(players.size() < 4)
	{
		players.push_back(p);
		set_color(p);
		map->emplace_player(p);
		return true;
	}

	return false;
}

Map * Game::get_map()
{
	return map;
}

void Game::remove_player(Player * p)
{
	if(running)
	{
		for(std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
		{
			if(*it == p)
			{
				players.erase(it);
				remove_color(p);
				//TODO unemplace player
				break;
			}
		}
	}
}

void Game::remove_color(Player * p)
{
	int color = p->get_color();
	colors[color] = false;
}

void Game::set_color(Player * p)
{
	for(int i = 0; i < 4; ++i)
	{
		if(colors[i] == false)
		{
			p->set_color(i);
			colors[i] = true;
			break;
		}
	}
}

std::string Game::to_string()
{
	std::string message = get_id() + ": ";
	//TODO trvání hry
	// message.append(players.size() + " ");
	message.append(players.size() + "/4");

	return message;
}

int Game::get_id()
{
	return id;
}
