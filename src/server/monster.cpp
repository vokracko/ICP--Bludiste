/**
 * \file monster.cpp
 * \author Lukáš Vokráčko (xvokra00)
*/

#include "monster.h"

/**
 * \fn Monster::Monster(Game * game, float timeout)
 * \brief Vytvoření monstra, jeho umístění v bludišti a spuštění vlastního vlákna
 * \param[in] game ukazatel na hru
 * \param[in] timeout časová prodleva mezi kroky
 */
Monster::Monster(Game * game, float timeout)
{
	this->game = game;
	this->timeout = timeout*1000000;

	do
	{
		pos.x = rand() % game->get_map()->get_width();
		pos.y = rand() % game->get_map()->get_height();
	} while(game->get_map()->get(pos.x, pos.y) != Box::EMPTY);

	pos.look = rand() % 4 + 1;
	game->get_map()->set(pos.x ,pos.y, Box::MONSTER + pos.look);

	// thread = std::thread(&Monster::work, this);
}

/**
 * \fn Monster::~Monster()
 * \brief Ukončení vlákna
 */
Monster::~Monster()
{
	// thread.join();
}

/**
 * \fn void Monster::work()
 * \brief Pohyb a akce hlídače v bludišti
 */
void Monster::work()
{
	std::string cmd = "step";
	Position next_pos;
	unsigned char obj;

	while(game->is_running())
	{
		//zjištění nového směru
		game->map_mutex.lock();
		new_way(&pos);
		game->next(&pos, &next_pos.x, &next_pos.y);
		next_pos.look = pos.look;
		obj = game->get_map()->get(next_pos.x, next_pos.y);

		// řešení ghost objektů
		if(obj == Box::KEY) game->get_map()->set_ghost(next_pos.x, next_pos.y, Box::KEY);
		else if(isPlayer(obj)) game->kill((obj/10)*10);
		unsigned char ghost_obj = game->get_map()->get_ghost(pos.x, pos.y);
		game->get_map()->set(pos.x, pos.y, ghost_obj ? ghost_obj : Box::EMPTY);
		game->get_map()->set_ghost(pos.x, pos.y, 0);

		//změna pozice
		game->get_map()->set(next_pos.x, next_pos.y, Box::MONSTER + pos.look);
		game->send(*(game->get_map()->get_map()));
		game->map_mutex.unlock();
		usleep(timeout);
		pos = next_pos;
	}

}

/**
 * \fn bool Monster::isPlayer(unsigned char obj)
 * \brief Zjistí, zda je objekt hráčem
 * \param[in] obj objekt
 * \return výsledek
 */
bool Monster::isPlayer(unsigned char obj)
{
	return obj >= Box::RED && obj <= Box::WHITE + Box::RIGHT;
}

/**
 * \fn int Monster::rotate(int look, int way)
 * \brief Otočení hlídače ve směru way
 * \param[in] look aktuální natočení hlídače
 * \way[in] way směr otáčení
 * \return nové natočení
 */
int Monster::rotate(int look, int way)
{
	if(way == Box::LEFT) return look == 4 ? 1 : look + 1;
	else return look == 1 ? 4 : look - 1;
}

/**
 * \fn void Monster::new_way(Position * current)
 * \brief Nastavý nové natočení hlídače
 * \param[in,out] current Aktuální pozice v mapě
 */
void Monster::new_way(Position * current)
{
	static Position next;
	static unsigned char obj;
	unsigned char looks[5] = {0,};
	int count = 0;
	int back = rotate(current->look, Box::LEFT);
	back = rotate(back, Box::LEFT);
	int only_one = back;

	for(int i = 1; i < 5; ++i)
	{
		game->next(current, &next.x, &next.y);

		try
		{
			obj = game->get_map()->get(next.x, next.y);
		} catch(std::exception & e)
		{
			current->look = rotate(current->look, Box::LEFT);
			continue;
		}

		obj = game->get_map()->get(next.x, next.y);

		if(obj == Box::EMPTY || obj == Box::KEY || isPlayer(obj))
		{
			count++;
			if(current->look != back) only_one = current->look;
			looks[current->look] = current->look;
		}

		current->look = rotate(current->look, Box::LEFT);
	}

	if(count < 3)
	{
		current->look = only_one;
	}
	else
	{
		while((current->look = looks[rand()%4+1]) == 0 || current->look == back);
	}
}
