#include "player.h"

Player::Player(Connection * conn)
{
	this->conn = conn;
	thread = std::thread(&Player::work, this);
}

Player::~Player()
{
	//TODO erase thread from server
	std::cout << "player~" << std::endl;
	delete conn;
	thread.join();
}

void Player::work()
{
	// delete this;
	//if(!connect()) return; //todo a zavři za sebou dveře
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

bool Player::connect()
{
	send_games();
	//TODO semafory z connection

	return false;

}

void Player::send_games()
{
	std::string message = Server::get_instance()->get_games_string();
	send(message);
}

void Player::send(std::string message)
{
	message = "wtfp";
	conn->write(message);
	//pošli zprávu klientovy
}

void Player::receive()
{

	// conn->read();
	//TODO;
	// std::string message;

}
