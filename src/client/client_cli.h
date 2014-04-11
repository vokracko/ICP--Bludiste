#pragma once
/**
*\file client_cli.h 
* Soubor obsahující implementaci hlavičky třídy Client_cli<br/>
*Potomek Třídy Client, jenž reimplementuje některé funkce tak, aby pracovali pouze s konzolí
*\author Michal Veselý (xvesel63)
*/

#include "client.h"

class Client_cli : public Client
{
	public:
	void print_map();
	void print_games();
	Client_cli();
	~Client_cli();
};