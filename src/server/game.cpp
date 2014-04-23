#include "game.h"

Game::Game(float timeout, int map_id)
{
	map = new Map(map_id);
	id = Server::get_instance()->get_game_id();
	this->timeout = timeout;
	running = true;
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

bool Game::cmd(Player * p, std::string * command)
{
	bool res = false;
	//TODO asi použít mutex aby si to neměnily navzájem
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
	else if(*command == "go")
	{

	}
	else if(*command == "stop")
	{

	}

	send(*(map->get_map()), p, res); // odešle všem hráčům aktuální stav

	return res;
}

void Game::set(Player * p, Position pos)
{
	Position current_pos = p->get_position();

	map->set(current_pos.x, current_pos.y, Box::EMPTY);
	map->set(pos.x, pos.y, p->get_color() + pos.look);
	p->set_position(pos);
}

void Game::next(Position pos, int * x, int * y)
{
	*x = pos.x;
	*y = pos.y;

	switch(pos.look)
	{
		case Box::UP: (*x)++;break;
		case Box::DOWN: (*x)--;break;
		case Box::LEFT: (*y)--;break;
		case Box::RIGHT: (*y)++;break;
	}
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
		p->take_key();
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

	if(way = Box::LEFT) pos.look = (current_pos.look) == 4 ? 1 : current_pos.look + 1;
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
void Game::send(std::string message, Player * p, int res)
{
	for(std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
	{
		if(p == *it)
		{
			char c = res ? MOVE_PASS : MOVE_FAIL;
			std::string info = (*map->get_map()) + c;
			(*it)->send(&info);
		}
		else
		{
			(*it)->send(&message);
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

		char c = p->get_color() + Box::CONNECTED;
		std::string info = std::to_string(c);
		send(*(map->get_map()) + info);

		players.push_back(p);
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
				map->unemplace_player(p);
				break;
			}

		}

		if(players.size())
		{
			std::string info = std::to_string(p->get_color()+Box::DISCONNECTED);
			send(*(map->get_map()) + info);
		}
		else
		{
			Server::get_instance()->delete_game(this);
		}
	}
}

void Game::remove_color(Player * p)
{
	int color = p->get_color();
	colors[color/10-40] = false;
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
