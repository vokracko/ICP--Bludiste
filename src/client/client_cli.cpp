/**
*\file client_cli.cpp 
* Soubor obsahující implementaci metod třídy Client_cli<br/>
* Reimplementuje některé funkce pro účel komunikace s konzolí
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

void Client_cli::print_games()
{
	this->get_games();
	std::cout<<this->games<<std::endl<<std::endl;
}

void Client_cli::print_maps()
{
	this->show_maps();
	std::cout<<this->maps<<std::endl<<std::endl;
}

Client_cli::Client_cli(){;}
Client_cli::~Client_cli(){;}
