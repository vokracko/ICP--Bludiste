#include "monster.h"

Monster::Monster(Game * game, float timeout)
{
	this->game = game;
	this->timeout = timeout*1000000;
}

void Monster::work()
{
	std::string cmd = "step";
	Position next_pos;

	while(game->is_running())
	{
		game->next(pos, &next_pos.x, &next_pos.y);
		next_pos.look = pos.look;

		while(game->map->get(next_pos.x, next_pos.y) == Box::EMPTY)
		{
			next_pos.look = pos.look;
			pos = next_pos;
			game->map->set(pos.x, pos.y, pos.look);
			game->next(pos, &next_pos.x, &next_pos.y);
		}

		game->get_map(pos.x, pos.y)
		game->cmd(this, &cmd);
		usleep(timeout);
	}
}

void Monster::inc_step()
{

}


