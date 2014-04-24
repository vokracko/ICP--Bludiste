#include "game.h"

Game::Game(float timeout, int map_id)
{
	map = new Map(map_id);
	id = Server::get_instance()->get_game_id();
	this->timeout = timeout;
	running = true;
	// monster = new Monster(this, timeout); //TODO
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
	// delete monster; //TODO
}

bool Game::is_running()
{
	return running;
}

void Game::stop()
{
	running = false;

	for(std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
	{
		(*it)->send_quit();
	}

}

bool Game::cmd(Player * p, std::string * command)
{
	map_mutex.lock();

	bool res = false;

	if(*command == "left")
	{
		res = rotate(p, Box::LEFT);
	}
	else if(*command == "right")
	{
		res = rotate(p, Box::RIGHT);
	}
	else if(*command == "take")
	{
		res = take(p);
	}
	else if(*command == "open")
	{
		res = open(p);
	}
	else if(*command == "step")
	{
		res = step(p);
		p->inc_step();
	}
	else if(*command == "stop")
	{
		res = true;
	}

	send(*(map->get_map()), p, res); // odešle všem hráčům aktuální stav

	map_mutex.unlock();

	return res;
}

std::string Game::quit_info()
{
	std::string info[5] = {"0", "0 0", "0 0", "0 0", "0 0"};


	auto diff = std::chrono::system_clock::now() - start;
	int total = std::chrono::duration_cast<std::chrono::duration<int>>(diff).count();

	info[0] = std::to_string(total) + "\r\n";

	for(std::vector<Player *>::iterator it = players.begin(); it != players.end(); ++it)
	{
		int xxx = (*it)->get_id();
		std::string yyyy = (*it)->quit_info();
		// info[(*it)->get_id()-4] = (*it)->quit_info();
	}

	std::string res;

	for(int i = 0; i < 5; ++i)
	{
		res.append(info[i] + "\r\n");
	}

	return res;
}

void Game::set(Player * p, Position pos)
{
	Position current_pos = p->get_position();
	unsigned char ghost_obj = map->get_ghost(current_pos.x, current_pos.y);

	map->set(current_pos.x, current_pos.y, ghost_obj ? ghost_obj : Box::EMPTY);
	// map->set(current_pos.x, current_pos.y, Box::EMPTY);
	map->set(pos.x, pos.y, p->get_color() + pos.look);

	map->set_ghost(current_pos.x, current_pos.y, 0);
	p->set_position(pos);
}

void Game::next(Position pos, int * x, int * y)
{
	*x = pos.x;
	*y = pos.y;

	switch(pos.look)
	{
		case Box::UP: (*y)--;break;
		case Box::DOWN: (*y)++;break;
		case Box::LEFT: (*x)--;break;
		case Box::RIGHT: (*x)++;break;
	}
}

bool Game::step(Player * p)
{
	Position current_pos = p->get_position();
	Position pos;
	int next_obj;
	int ghost_obj;
	bool res = false;

	pos.look = current_pos.look;
	next(current_pos, &pos.x, &pos.y);

	next_obj = map->get(pos.x, pos.y);

	if(next_obj == Box::EMPTY)
	{
		res = true;
	}
	else if(next_obj == Box::KEY && p->has_key())
	{
		map->set_ghost(pos.x, pos.y, Box::KEY);
		std::cout<<"Vkládám ghosta na key: " << pos.x << "," << pos.y<<std::endl;
		res = true;
	}
	else if(next_obj == Box::GATE + Box::OPEN)
	{
		map->set_ghost(pos.x, pos.y, Box::GATE + Box::OPEN);
		res = true;
	}

	if(res)
	{
		if(next_obj == Box::GATE + Box::OPEN)
		{
			//TODO výhra
			//TODO kontrola hranic mapy
		}
		else
		{
			map->set(pos.x, pos.y, p->get_color() + current_pos.look);
			set(p, pos);
		}

		return true;
	}

	return false;

}

bool Game::take(Player * p)
{
	Position current_pos = p->get_position();
	int x, y;

	if(p->has_key()) return false; //nemůže vzít více klíčů

	next(current_pos, &x, &y);

	if(map->get(x, y) == Box::KEY)
	{
		map->set(x,y, Box::EMPTY);
		p->take_key();
		return true;
	}

	return false;
}

bool Game::open(Player * p)
{
	Position current_pos = p->get_position();
	int x, y;

	if(!p->has_key()) return false; //nevlastní klíč, nemůže otevřít

	next(current_pos, &x, &y);

	if(map->get(x, y) == Box::GATE + Box::CLOSED)
	{
		map->set(x,y, Box::GATE + Box::OPEN);
		return true;
	}

	return false;
}

bool Game::rotate(Player * p, int way)
{
	Position pos;
	Position current_pos = p->get_position();
	pos.x = current_pos.x;
	pos.y = current_pos.y;

	if(way == Box::LEFT) pos.look = (current_pos.look) == 4 ? 1 : current_pos.look + 1;
	else pos.look = (current_pos.look) == 1 ? 4 : current_pos.look - 1;

	set(p, pos);

	return true;
}

/**
 * Pošle zprávu o změně stavu hry vše klientům kromě toho, který tuto zprávu vytvořil
 * \fn void Game::send(Player * exclude, std::string message)
 * \param exclude odkaz na hráče, který zprávu vytvořil
 * \param message obsah zprávy
 */
void Game::send(std::string message, Player * p, int res, Player * skip)
{
	char c = res ? MOVE_PASS : MOVE_FAIL;;
	std::string info = message + c + "\r\n";
	std::string no_info = message + "\r\n";

	for(std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
	{
		if(*it == skip)
		{
			continue;
		}

		if(p == *it)
		{
			(*it)->send(&info);
		}
		else
		{
			(*it)->send(&no_info);
		}
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
		set_color(p);

		map->emplace_player(p);

		char c = p->get_color() + Box::CONNECTED;
		std::string info = *(map->get_map());
		info += c;
		send(info);

		players.push_back(p);

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
				map->unemplace_player(p);
				break;
			}

		}

		if(players.size())
		{
			std::string info = *(map->get_map()) + (char) (p->get_color()+Box::DISCONNECTED);
			send(info);
		}
		else
		{
			Server::get_instance()->delete_game(this);
		}
	}
}

void Game::remove_color(Player * p)
{
	colors[p->get_color()/10-40] = false;
}

void Game::set_color(Player * p)
{
	for(int i = 0; i < 4; ++i)
	{
		if(colors[i] == false)
		{
			p->set_color(i*10+40);
			colors[i] = true;
			break;
		}
	}
}

std::string Game::to_string()
{
	auto diff = std::chrono::system_clock::now() - start;
	int total = std::chrono::duration_cast<std::chrono::duration<int>>(diff).count();
	int hours = total/(60*60);
	int mins = total/60;
	int secs = total%60;

	std::string message = std::to_string(id) + ": ";
	message.append(map->get_name() + ", ");
	message.append("hráči: " + std::to_string(players.size()) + "/4");
	message.append(", trvání: " + std::to_string(hours) + "h" + std::to_string(mins) + "m" + std::to_string(secs) + "s");

	return message;
}

int Game::get_id()
{
	return id;
}
