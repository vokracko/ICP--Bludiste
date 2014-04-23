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

		send_map(true);

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
				// start = std::chrono::system_clock::now();
				return true;
			}

		} while(target != "list");

	} while(target == "list"); //aktualizace her ze strany klienta
}

void Player::inc_step()
{
	step_count++;
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
	message.append(game->quit_info());
	send(&message, Connection::SYNC);
}

std::string Player::quit_info()
{
	std::string message;
	auto diff = std::chrono::system_clock::now() - start;
	int total = std::chrono::duration_cast<std::chrono::duration<int>>(diff).count();


	message = std::to_string(total) + " " + std::to_string(step_count);
	return message;
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
	std::cout << "Player: " << id << std::endl;
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


//TODO ctrlc kilnutí serveru a poslání zprávy klientovy ať jde do píči
