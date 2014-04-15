/**
*\file client_cli.cpp 
* Soubor obsahující implementaci metod třídy Client_cli<br/>
* Rozšiřuje metody třídy Klient pouze o některé funkce výpisu, původní funkcionalita je jinak zachována a neměněna
*\author Michal Veselý (xvesel63)
*/

#include "client_cli.h"

/**
*\fn void Client_cli::print_map() 
* Vypíše stav hrací plochy
*/
void Client_cli::print_map()
{
	for (int i=0; i < height; i++)
	{
		for (int j=0; j < width; j++)
		{
			std::cout<<map[i][j];
		}
		std::cout<<std::endl;
	}
}

/**
*\fn void Client_cli::print_games()
* Vypíše rozehrané hry, ke kterým se lze připojit
*/
void Client_cli::print_games()
{
	this->get_games();
	std::cout<<this->games<<std::endl<<std::endl;
}

/**
*\fn void Client_cli::print_maps()
* Vypíše mapy, které jsou k dispozici pro založení nové hry
*/
void Client_cli::print_maps()
{
	this->show_maps();
	std::cout<<this->maps<<std::endl<<std::endl;
}

Client_cli::Client_cli(){;}
Client_cli::~Client_cli(){;}
