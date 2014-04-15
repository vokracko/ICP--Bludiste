#include "game.h"

Game::Game(float timeout, int map_id)
{
	map = new Map(map_id);
	id = Server::get_instance()->get_game_id();
	this->timeout = timeout;
	running = true;
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

void Game::cmd(Player * p, std::string * command)
{
	bool res;
	//TODO
	if(*command == "left")
	{
		res = turn_left(p);
	}
	else if(*command == "right")
	{
		res = turn_right(p);
	}
	else if(*command == "take")
	{
		res = take(p);
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

void Game::set(Player * p, Position pos)
{
	Position current_pos = p->get_position();

	map->set(current_pos.x, current_pos.y, Box::EMPTY);
	map->set(pos.x, pos.y, p->get_color() + pos.look);
	p->set_position(pos);
}

bool Game::take(Player * p)
{
	//TODO vyřešit překreslování klíče když na něm stojím
}

bool Game::open(Player * p)
{
	Position current_pos = p->get_position();
	Position key = map->get_key_position(); //TODO více klíčů
	int x = current_pos.x;
	int y = current_pos.y;

	if(!p->has_key()) return false; //nevlastní klíč, nemůže otevřít

	switch(current_pos.look)
	{
		case Box::UP: x++;break;
		case Box::DOWN: x--;break;
		case Box::LEFT: y--;break;
		case Box::RIGHT: y++;break;
	}

	if(map->get(x, y) == Box::KEY)
	{
		map->set(x,y, Box::EMPTY);
		p->take_key();
		return true;
	}

	return false;
}

bool Game::turn_left(Player * p)
{
	Position pos;
	Position current_pos = p->get_position();
	pos.x = current_pos.x;
	pos.y = current_pos.y;
	pos.look = (current_pos.look) == 4 ? 1 : current_pos.look + 1;

	set(p, pos);

	return true;
}

bool Game::turn_right(Player * p)
{
	Position pos;
	Position current_pos = p->get_position();
	pos.x = current_pos.x;
	pos.y = current_pos.y;
	pos.look = (current_pos.look) == 1 ? 4 : current_pos.look - 1;

	set(p, pos);

	return true;
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
				if(players.size() == 0) Server::get_instance()->delete_game(this);
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
	std::string message = std::to_string(id) + ": ";
	message.append(map->get_name() + ", ");
	//TODO trvání hry
	message.append("hráči: " + std::to_string(players.size()) + "/4");

	return message;
}

int Game::get_id()
{
	return id;
}
