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
	for (int i=0; i < width; i++)
	{
		for (int j=0; j < height; j++)
		{
			std::cout<<map[i][j];
		}
		std::cout<<std::endl;
	}
}
Client_cli::Client_cli(){;}
Client_cli::~Client_cli(){;}
