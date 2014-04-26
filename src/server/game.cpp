/**
 * \file game.cpp
 * \author Lukáš Vokráčko (xvokra00)
*/

#include "game.h"

/**
 * \fn Game::Game(float timeout, int map_id)
 * \brief Vytvoří mapu, hlídače, získá unikátní identifikátor a nastaví parametry hry
 * \param[in] timeout zpoždění při příkazu go
 * \param[in] map_id identifikátory mapy
*/
Game::Game(float timeout, int map_id)
{
	id = Server::get_instance()->get_game_id();
	this->timeout = timeout;
	running = true;
	map = new Map(map_id);
	monster = new Monster(this, timeout);
}

/**
 * \fn Game::~Game()
 * \brief Smaže mapa a hlídače
*/
Game::~Game()
{
	delete map;
	delete monster;
}

/**
 * \fn bool Game::is_running()
 * \brief Vrátí stav hry
 * \return running stav hry
*/
bool Game::is_running()
{
	return running;
}

/**
 * \fn void Game::stop(bool quit)
 * \brief Zastaví hru, pošle poslední zprávu hráčů a poté je smaže
 * \param[in] quit při true pošle zprávu o násilném ukončení hry, jinak pošle statistiky o hře
*/
void Game::stop(bool quit)
{
	running = false;

	if(quit)
	{
		std::string msg = "quit\r\n";
		send(msg);
	}
	else
	{
		end_info();
	}

}

/**
 * \fn void Game::cmd(Player * p, std::string * command)
 * \brief Zpracuje tah hráče a informuje jeho a všechny ostatní hráče o výsledku tohoto tahu
 * \param[in] p ukazatel na hráče, který provádí tah
 * \param[in] command ukazatel na string obsahující identifikátor tahu
*/
void Game::cmd(Player * p, std::string * command)
{
	map_mutex.lock();

	int res = MOVE_FAIL;
	int state = 0;
	p->go = false;

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
		state = p->get_color() + Box::KEY;
	}
	else if(*command == "open")
	{
		res = open(p);
		state = p->get_color() + Box::OPEN;
	}
	else if(*command == "step")
	{
		res = step(p);
		p->inc_step();

		if(res == Box::YOU_WIN)
		{
			state = p->get_color();
		}
	}
	else if(*command == "stop")
	{
		res = MOVE_PASS;
	}

	send(*(map->get_map()), p, res, res == MOVE_FAIL ? 0 : state); // odešle všem hráčům aktuální stav

	if(res == Box::YOU_WIN)
	{
		stop();
	}

	map_mutex.unlock();
}

/**
 * \fn void Game::end_info()
 * \brief Zašle statistiky hry všem hráčům při ukončení hry vítězstvím
*/
void Game::end_info()
{
	auto diff = std::chrono::system_clock::now() - start;
	int total = std::chrono::duration_cast<std::chrono::duration<int>>(diff).count();
	std::string info[5] = {"", "0 0", "0 0", "0 0", "0 0"};

	info[0] = "end" + std::to_string(total);

	for(std::vector<Player *>::iterator it = players.begin(); it != players.end(); ++it)
	{
		info[(*it)->get_color()/10-3] = (*it)->end_info();
	}

	std::string res;

	for(int i = 0; i < 5; ++i)
	{
		if(i == 4)
		{
			res.append(info[i] + "\r\n");
		}
		else
		{

		res.append(info[i] + "\n");
		}
	}

	for(std::vector<Player *>::iterator it = players.begin(); it!= players.end(); ++it)
	{
		(*it)->send(&res);
	}
}

/**
 * \fn void Game::set(Player * p, Position pos)
 * \brief Přemístí hráče z jeho aktuální pozice na pozici novou
 * \param[in] p ukazatel na hráče, jehož pozice se má změnit
 * \param[in] pos nová pozice
*/
void Game::set(Player * p, Position pos)
{
	Position current_pos = p->get_position();
	unsigned char ghost_obj = map->get_ghost(current_pos.x, current_pos.y);

	map->set(current_pos.x, current_pos.y, ghost_obj ? ghost_obj : Box::EMPTY);
	map->set(pos.x, pos.y, p->get_color() + pos.look);

	map->set_ghost(current_pos.x, current_pos.y, 0);
	p->set_position(pos);
}

/**
 * \fn void Game::kill(int color)
 * \brief Zabije hráče, zašle o tom všem zprávu a odstraní ho
 * \param[in] color barva zabitého hráče
*/
void Game::kill(int color)
{
	for(std::vector<Player *>::iterator it = players.begin(); it != players.end(); ++it)
	{
		if((*it)->get_color() == color)
		{
			(*it)->go = false;
			remove_player(*it);
			send(*(map->get_map()), nullptr, 0, (*it)->get_color() + Box::KILLED);
			break;
		}
	}
}

/**
 * \fn void Game::next(Position * pos, int * x, int * y)
 * \brief Na základě pozice a natočení hráče určí souřadnice následující pozice
 * \param[in] pos aktuální pozice hráče
 * \param[out] x ukazatel na novou souřadnici X
 * \param[out] y ukazatel na novou souřadnici Y
*/
void Game::next(Position * pos, int * x, int * y)
{
	*x = pos->x;
	*y = pos->y;

	switch(pos->look)
	{
		case Box::UP: (*y)--;break;
		case Box::DOWN: (*y)++;break;
		case Box::LEFT: (*x)--;break;
		case Box::RIGHT: (*x)++;break;
	}
}

/**
 * \fn int Game::step(Player * p)
 * \brief Pohne hráče o jedno políčko dopředu
 * \param[in] p ukazatel na hráče, jehož pohyb se má vykonat
 * \return res informace o výsledku tahu
 * \see Game::next()
*/
int Game::step(Player * p)
{
	Position current_pos = p->get_position();
	Position pos;
	int next_obj;
	int ghost_obj;
	int res = MOVE_FAIL;
	p->go = true;
	pos.look = current_pos.look;
	next(&current_pos, &pos.x, &pos.y);

	try
	{
		next_obj = map->get(pos.x, pos.y);
	}
	catch(std::exception & e)
	{
		p->go = false;
		return MOVE_FAIL;
	}

	if(next_obj == Box::EMPTY)
	{
		res = MOVE_PASS;
	}
	else if(next_obj == Box::KEY && p->has_key())
	{
		map->set_ghost(pos.x, pos.y, Box::KEY);
		res = MOVE_PASS;
	}
	else if(next_obj == (Box::GATE + Box::OPEN))
	{
		return Box::YOU_WIN;
	}
	else if(next_obj >= 40 && next_obj <= 90 && p->get_color() == Box::MONSTER)
	{
		res = next_obj - next_obj%10 + Box::KILLED;
	}

	if(res != MOVE_FAIL)
	{
		map->set(pos.x, pos.y, p->get_color() + current_pos.look);
		set(p, pos);
	}
	else
	{
		p->go = false;
	}

	return res;

}

/**
 * \fn int Game::take(Player * p)
 * \brief Sebere klíč pokud jště žádný nemá
 * \param[in] p ukazatel na hráče provádějícího tah
 * \return - výsledek tahu
*/
int Game::take(Player * p)
{
	Position current_pos = p->get_position();
	int x, y;

	if(p->has_key()) return MOVE_FAIL; //nemůže vzít více klíčů

	next(&current_pos, &x, &y);

	if(map->get(x, y) == Box::KEY)
	{
		map->set(x,y, Box::EMPTY);
		p->take_key();
		return MOVE_PASS;
	}

	return MOVE_FAIL;
}

/**
 * \fn int Game::open(Player * p)
 * \brief Otevře bránu pokud hráč vlastní klíč
 * \param[in] p ukazatel na hráče provádějícího tah
 * \return - výsledek tahu
*/
int Game::open(Player * p)
{
	Position current_pos = p->get_position();
	int x, y;

	if(!p->has_key()) return MOVE_FAIL; //nevlastní klíč, nemůže otevřít

	next(&current_pos, &x, &y);

	if(map->get(x, y) == Box::GATE + Box::CLOSED)
	{
		map->set(x,y, Box::GATE + Box::OPEN);
		return MOVE_PASS;
	}

	return MOVE_FAIL;
}

/**
 * \fn int Game::rotate(Player * p, int way)
 * \brief Otočí hráče o 90 stupňů
 * \param[in] p ukazatel na hráče provádějícího tah
 * \param[in] way směr otáčení
 * \return true otočení se vždy povede
*/
int Game::rotate(Player * p, int way)
{
	Position pos;
	Position current_pos = p->get_position();
	pos.x = current_pos.x;
	pos.y = current_pos.y;

	if(way == Box::LEFT) pos.look = (current_pos.look) == 4 ? 1 : current_pos.look + 1;
	else pos.look = (current_pos.look) == 1 ? 4 : current_pos.look - 1;

	set(p, pos);

	return MOVE_PASS;
}

/**
 * \fn void Game::send(std::string message, Player * p, int move_res, int state_code)
 * \brief Pošle zprávu všem hráčům
 * \param[in] message obsah zprávy
 * \param[in] p odkaz na hráče, jehož tah zprávu vygeneroval
 * \param[in] move_res doplňující informace pro hráče jež zprávu vygeneroval
 * \param[in] state_code doplňující informace pro ostatní hráče
 */
void Game::send(std::string message, Player * p, int move_res, int state_code)
{
	std::string res_info = message + (char) move_res + "\r\n";
	std::string state_info = state_code ? message + (char) state_code + "\r\n" : message + "\r\n";

	for(std::vector<Player*>::iterator it = players.begin(); it != players.end(); ++it)
	{
		if(p == *it)
		{
			(*it)->send(&res_info);
		}
		else
		{
			(*it)->send(&state_info);
		}
	}
}

/**
 * \fn float Game::get_timeout()
 * \brief Vrátí hodnotu časové prodlevy
 * \return timeout
 */
float Game::get_timeout()
{
	return timeout;
}

/**
 * \fn bool Game::add_player(Player * p)
 * \brief Připojí hráče do hry
 * \param p ukazatel na připojovaného hráče
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

/**
 * \fn Map * Game::get_map()
 * \brief Vrátí ukazatel na mapu
 * \return map ukazatel na mapu
*/
Map * Game::get_map()
{
	return map;
}

/**
 * \fn void Game::remove_player(Player * p)
 * \brief Odebere hráče ze hry a informuje o tom ostatní hráče
 * \param[in] p ukazatel na odebíraného hráče
*/
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
				Server::get_instance()->add_orphan(p);
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
			running = false;
		}
	}
}

/**
 * \fn void Game::remove_color(Player * p)
 * \brief Uvolní barvu použitou hráčem p
 * \param[in] p ukazatel na hráče vlastnící barvu
*/
void Game::remove_color(Player * p)
{
	colors[p->get_color()/10-4] = false;
}

/**
 * \fn void Game::set_color(Player * p)
 * \brief Přiřadí hráči volnou barvu
 * \param[in] p ukazatel na hráče
*/
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

/**
 * \fn std::string Game::to_string()
 * \brief Zabalí informace o hře do řetězce
 * \return message informace o hře
*/
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

/**
 * \fn int Game::get_id()
 * \return id identifikátor hry
*/
int Game::get_id()
{
	return id;
}
