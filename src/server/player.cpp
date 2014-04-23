#include "player.h"

Player::Player(Connection * conn)
{
	this->conn = conn;
	thread = std::thread(&Player::work, this);
	id = Server::get_instance()->get_player_id();
}

Player::~Player()
{
	delete conn;
	thread.join();
}

bool Player::has_key()
{
	return own_key;
}

void Player::take_key()
{
	own_key = true;
}

void Player::work()
{
	std::string message;
	bool res;

	try
	{
		if(!init()) return;

		// position.x = 0;
		// position.y = 0;
		// position.look = Box::DOWN;

		send_map(true);

		// game->get_map()->set(0, 0, Box::RED + Box::DOWN);
		// send_map();

		while(game->is_running() && message != "quit")
		{
			receive(&message, Connection::SYNC);
			res = game->cmd(this, &message);  // upraví políčka hry
			// message = res ? "OK" : "KO";
			// send(&message, Connection::SYNC);
		}
	}
	catch(std::exception & e)
	{
		//TODO posílat ukončení hry
	}

	if(game != nullptr) game->remove_player(this);
}

int Player::get_id()
{
	return id;
}

Position Player::get_position()
{
	return position;
}

bool Player::init()
{
	std::string target;
	size_t pos;
	int game_id = 0;

	receive(&target, Connection::SYNC); // přijme maps/quit
	if(target == "quit") return false;
	send_map_list();

	receive(&target, Connection::SYNC);
	if(target != "list" || target == "quit") return false; //neznámý příkaz

	do
	{
		send_games();

		do
		{
			receive(&target, Connection::SYNC); //tady je příkaz co zadal klient


			if(target == "list") break;
			else if(target == "quit") return false;

			game_id = std::stoi(target, &pos);
			if(pos != target.length())
			{
				// ve zprávě dvě čísla == zakládá novou hru
				game_id = Server::get_instance()->new_game(target);
				if(game_id == 0)
				{
					send_invalid();
					send_games();
					continue;
				}
			}

			game = Server::get_instance()->assign(game_id, this);

			if(!game)
			{
				// není místo ve hře/neexistující hra
				send_invalid();
				send_games();
				continue;
			}
			else
			{
				send_play();
				return true;
			}

		} while(target != "list");

	} while(target == "list"); //aktualizace her ze strany klienta
}

void Player::send_play()
{
	std::string message = "play\r\n";
}

void Player::send_invalid()
{
	std::string message = "invalid\r\n";
	send(&message, Connection::SYNC);
}

void Player::send_games()
{
	std::string message = Server::get_instance()->get_games_string();
	send(&message, Connection::SYNC);
}

void Player::send_map_list()
{
	std::string message = Map::list();
	send(&message, Connection::SYNC);
}

void Player::send_quit()
{
	std::string message = "quit\r\n";
	send(&message, Connection::SYNC);
}

void Player::send_map(bool first_time)
{
	std::string message;

	if(first_time)
	{
		message.assign(std::to_string(game->get_map()->get_width()) + " ");
		message.append(std::to_string(game->get_map()->get_height()) + " ");
		message.append(std::to_string(color/10) + " ");
		message.append(std::to_string(position.x) + " ");
		message.append(std::to_string(position.y) + "\r\n");
	}

	//TODO možná provádět kopii, možná synchronizaci s mutexem
	message.append(*(game->get_map()->get_map()));

	send(&message, Connection::SYNC);
}

int Player::get_color()
{
	return color;
}

void Player::set_position(Position pos)
{
	position = pos;
}

void Player::set_color(int color)
{
	this->color = color;
}

void Player::send(std::string * message, int mode)
{
	std::cout << *message << std::endl;

	if(mode == Connection::ASYNC)
	{
		conn->send(message);
	}
	else if(mode == Connection::SYNC)
	{
		conn->sync_send(message);
	}
}

void Player::receive(std::string * target, int mode)
{
	if(mode == Connection::ASYNC)
	{
		conn->receive(target);
	}
	else if(mode == Connection::SYNC)
	{
		conn->sync_receive(target);
	}

	std::cout << "Receive: " << *target << std::endl;
}


