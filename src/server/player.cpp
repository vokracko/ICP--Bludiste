/**
 * \file player.cpp
 * \author Lukáš Vokráčko (xvokra00)
*/

#include "player.h"

/**
 * \fn Player::Player(Connection * conn)
 * \brief Vytvoření vlákna pro hráče
 * \param[in] conn Spojení patřící k tomuto hráři
 */
Player::Player(Connection * conn)
{
	this->conn = conn;
	id = Server::get_instance()->get_player_id();
	thread = std::thread(&Player::work, this);
	thread.detach();
}

/**
 * \fn Player::~Player()
 * \brief Ukončení vlákna a spojení
 */
Player::~Player()
{
	delete conn;
}

/*
 * \fn bool Player::has_key()
 * \return own_key
 */
bool Player::has_key()
{
	return own_key;
}

/*
 * \fn void Player::take_key()
 * \brief Nastaví vlastnictví klíče
 */
void Player::take_key()
{
	own_key = true;
}

/*
 * \fn void Player::work()
 * \brief Veškeré akce hráče
 */
void Player::work()
{
	std::string message;
	bool res;

	try
	{
		if(!init()) return;

		send_map(true);

		while(game->is_running() && ok)
		{
			receive(&message, Connection::SYNC);
			if(!ok || message == "quit") break;

			if(message == "go")
			{
				message = "step";

				go = true;
				std::thread(&Player::go_timer, this).detach();
			}

			game->cmd(this, &message);  // upraví políčka hry
		}
	}
	catch(std::exception & e)
	{

	}

	if(game != nullptr)
	{
		game->remove_player(this);
	}

	Server::get_instance()->remove_orphan(this);
	delete this;


}

/**
 * \fn void Player::go_timer()
 * \brief Časuje kroky při příkazu go
 */
void Player::go_timer()
{
	std::string step = "step";

	while(go)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((int) (game->get_timeout() * 1000)));
		if(go == false) break;

		game->cmd(this, &step);
	}
}

//TODO předělat na asynchroní, volat destruktory

/**
 * \fn int Player::get_id()
 * \return id
 */
int Player::get_id()
{
	return id;
}

/**
 * \fn Position Player::get_position()
 * \return position
 */
Position Player::get_position()
{
	return position;
}

/**
 * \fn bool Player::init()
 * \brief Komunikace s klientemnež se připojí do hry
 * \return výsledek připojení
 */
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
					continue;
				}
			}

			game = Server::get_instance()->assign(game_id, this);

			if(!game)
			{
				// není místo ve hře/neexistující hra
				send_invalid();
				continue;
			}
			else
			{
				start = std::chrono::system_clock::now();
				return true;
			}

		} while(target != "list");

	} while(target == "list"); //aktualizace her ze strany klienta
}

/**
 * \fn void Player::inc_step()
 * \brief Inkrementuje počet kroků pro statistiky na konci hry
 */
void Player::inc_step()
{
	step_count++;
}

/**
 * \fn void Player::send_invalid()
 * \brief Odešle zprávu o neplatném příkazu
 */
void Player::send_invalid()
{
	std::string message = "invalid\r\n";
	send(&message, Connection::SYNC);
}

/**
 * \fn void Player::send_games()
 * \brief Odešle zprávu o probíhajících hrách
 */
void Player::send_games()
{
	std::string message = Server::get_instance()->get_games_string();
	send(&message, Connection::SYNC);
}

/**
 * \fn void Player::send_map_list()
 * \brief Odešle zprávu o dostupných mapách
 */
void Player::send_map_list()
{
	std::string message = Map::list();
	send(&message, Connection::SYNC);
}

/**
 * \fn void Player::end_info()
 * \brief Vytvoří string s informacemi o tomto hráči
 * \@see Game::end_info
 * \return řetězec s informacemi
 */
std::string Player::end_info()
{
	std::string message;
	auto diff = std::chrono::system_clock::now() - start;
	int total = std::chrono::duration_cast<std::chrono::duration<int>>(diff).count();


	message = std::to_string(total) + " " + std::to_string(step_count);
	return message;
}

/**
 * \fn void Player::send_map(bool first_time)
 * \brief Zašle hráči mapu
 * \param[in] first_time S tímto parametrem zašle kromě mapy i rozměry, barvu a umístění hráče
 */
void Player::send_map(bool first_time)
{
	std::string message;

	if(first_time)
	{
		message.assign(std::to_string(game->get_map()->get_width()) + " ");
		message.append(std::to_string(game->get_map()->get_height()) + " ");
		message.append(std::to_string(color/10) + " ");
		message.append(std::to_string(position.x) + " ");
		message.append(std::to_string(position.y) + " ");
		message.append(std::to_string(game->get_timeout()) + "\r\n");
	}

	message.append(*(game->get_map()->get_map()));

	send(&message, Connection::SYNC);
}

/**
 * \fn int Player::get_color()
 * \return color
 */
int Player::get_color()
{
	return color;
}

/**
 * \fn int Player::set_position(Position pos)
 * \brief Nastavý pozici hráče
 * \param[in] pos nová pozice
 */
void Player::set_position(Position pos)
{
	position = pos;
}

/**
 * \fn void Player::set_color(int color)
 * \brief Nastaví hráči barvu
 * \param[in] color barva
 */
void Player::set_color(int color)
{
	this->color = color;
}

/**
 * \fn void Player::send(std::string * message, int mode)
 * \brief Odešle hráči zprávu
 * \param[in] message zpráva
 * \param[in] mode synchronní/asynchronní
 */
void Player::send(std::string * message, int mode)
{
	try
	{
		if(mode == Connection::ASYNC)
		{
			conn->send(message);
		}
		else if(mode == Connection::SYNC)
		{
			conn->sync_send(message);
		}
	} catch(std::exception & e)
	{
		ok = false;
		game->remove_player(this);
	}
}

/**
 * \fn void Player::receive(std::string * target, int mode)
 * \brief Přijme zprávu od hráče
 * \param[out] target ukazatel na místo, kam se má zpráva uložit
 * \param[in] mode synchronní/asynchronní
 */
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
