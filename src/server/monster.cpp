#include "monster.h"

Monster::Monster(Game * game, float timeout)
{
	this->game = game;
	this->timeout = timeout*1000000;

	game->get_map()->set(1,0, Box::MONSTER + Box::RIGHT);
	pos.x = 1;
	pos.y = 0;
	pos.look = Box::RIGHT;

	thread = std::thread(&Monster::work, this);
}

Monster::~Monster()
{
	thread.join();
}

void Monster::work()
{
	std::string cmd = "step";
	Position next_pos;
	unsigned char obj;

	while(game->is_running())
	{
		game->map_mutex.lock();
		game->next(pos, &next_pos.x, &next_pos.y);
		next_pos.look = pos.look;

		try
		{
			while(game->is_running() && ((obj = game->get_map()->get(next_pos.x, next_pos.y)) == Box::EMPTY || obj == Box::KEY))
			{
				if(obj == Box::KEY)
				{
					game->get_map()->set_ghost(next_pos.x, next_pos.y, Box::KEY);
				}

				unsigned char ghost_obj = game->get_map()->get_ghost(pos.x, pos.y);
				game->get_map()->set(pos.x, pos.y, ghost_obj ? ghost_obj : Box::EMPTY);
				game->get_map()->set_ghost(pos.x, pos.y, 0);

				next_pos.look = pos.look;
				pos = next_pos;
				game->get_map()->set(pos.x, pos.y, Box::MONSTER + pos.look);
				game->send(*(game->get_map()->get_map()));

				game->map_mutex.unlock();
				usleep(timeout);
				game->map_mutex.lock();
				game->next(pos, &next_pos.x, &next_pos.y);
			}
		} catch(std::exception & e)
		{
			obj = Box::WALL;
		}

		switch((obj/10)*10)
		{
			case Box::RED:
			case Box::GREEN:
			case Box::WHITE:
			case Box::BLUE:
				game->kill((obj/10)*10);
				break;

			case Box::WALL:
				pos.look = rand() % 4 + 1;
				break;
		}

		game->map_mutex.unlock();
	}
}

//TODO inteligentnější pohyb
//TODO umístění
