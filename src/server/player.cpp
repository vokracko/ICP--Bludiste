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

void Player::work()
{
	init();


	// TODO while game->running ?
		// v cyklu přijímat zprávu
		// pokud přijmu tak zavolám objekt hry pokud jde o zprávu pro hru
		// a předám mu všechny informace co jsem přijal
		// aby je přeposlal
		// jinak zprávu obsloužím sám

	// TODO onquit
	// nějak dát vědět hře
	// Server::get_instance->add_orphan(this);
}

bool Player::init()
{
	std::string target;
	size_t pos;
	int game_id = 0;

	receive(&target, Connection::SYNC);
	std::cout << target << std::endl;
	if(target != "list" && target != "quit") return false; //neznámý příkaz

	do
	{
		send_games();
		//TODO posílat i mapy které může vytvořit

		do
		{
			receive(&target, Connection::SYNC); //tady je příkaz co zadal klient


			if(target == "list") break;
			else if(target == "quit") return false;

			game_id = std::stoi(target, &pos);
			if(pos == target.length() - 1)
			{
				// ve zprávě je jen jedno číslo == zakládá novou hru
				game_id = Server::get_instance()->new_game(target);
				if(game_id == 0)
				{
					send_invalid();
					send_games();
					continue;
				}
			}

			game = Server::get_instance()->assing(game_id, this);

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
	std::string message;// = Server::get_instance()->get_games_string();
	message.assign("0: hra1 mapa2\r\n1: hra2 mapa1\r\n");
	message.append("\r\nMapy:\r\n1) bludiště\r\n2) hra\r\n");
	send(&message, Connection::SYNC);
}

void Player::send(std::string * message, int mode)
{
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
}


