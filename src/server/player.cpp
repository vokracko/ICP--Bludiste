#include "player.h"

Player::Player(Connection * conn)
{
	this->conn = conn;
}

Player::~Player()
{
	// delete conn;
}

void Player::work()
{
	send_games();
	// připojit se ke hře
	// vytvořit novou hru ..

	//g = get_game(gid)
	//if(g.add_Player(this->id)) ? OK : full

	// v cyklu přijímat zprávu
	// pokud přijmu tak zavolám objekt hry pokud jde o zprávu pro hru
	// a předám mu všechny informace co jsem přijal
	// aby je přeposlal
	// jinak zprávu obsloužím sám
}

void Player::send_games()
{
	std::string message = Server::get_instance()->get_games_string();
	send(message);
}

void Player::send(std::string message)
{
	conn->write(message);
	//pošli zprávu klientovy
}
