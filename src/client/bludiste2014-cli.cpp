/**
*\file bludiste2014_cli.cpp
*Obsahuje funkci main, demonstruje klienta pro konzolovou verzi bludiště
*\author Michal Veselý (xvesel63)
*/

#include "client_cli.h"
#include <QCoreApplication>
#include <iostream>
#include "../errors.h"
#include <stdio.h>
#include <locale.h>

int main (int argc, char * argv[])
{
	QCoreApplication a(argc, argv);
	setlocale(LC_NUMERIC,"C");
	Client_cli client;

	std::string host,game_type = "";
	int repeat=0;
	try
	{
		// ziskani serveru na pripojeni
		std::cout<<"Na jaky server se chcete pripojit? "<<std::endl;
		// host="localhost";
		std::cin>>host;
		std::cout<<std::endl;
		client.connect_socket(const_cast<char *>(host.c_str()));

		// vypis her
		std::cout<<"Jsou vam k dispozici tyto mapy:" <<std::endl<<std::endl;
		client.print_maps();

		std::cout<<"Jsou vam k dispozici tyto hry:"<<std::endl<<std::endl;
		client.print_games();


		// vyber mezi join a create
		std::cout<<"Přejete se připojit k některé z těchto her, nebo si založit vlastní?"<<std::endl;

		int map_number=100,join,game_number,ec;
		float timeout=0;

		// vybere mezi join a create game
		do
		{
			join=0;
			std::cout<<"Pro vytvoření hry ......... 1"<<std::endl;
			std::cout<<"Pro připojení se ke hře ... 2"<<std::endl;
			std::cin >> game_type;
			join = std::stoi(game_type);
			break;
		} while (join!=1 && join!=2);

		// zalozeni nove hry
		if (join==1)
		{
			do // dokud neni zadan spravny timeout
			{
				std::cout<<"Zadejte timeout hry (v intervalu <0.5 ; 5>)"<<std::endl;
				//game_type="";
				//std::cin>>game_type;
				ec=scanf("%f",&timeout);
			} while (timeout < 0.5 || timeout > 5);

			do // dokud neni zadan spravne index mapy
			{
				std::cout<<"Zadejte cislo mapy (musí být validní)"<<std::endl;
				//game_type="";
				//std::cin >> game_type;
				ec=scanf("%d",&map_number);
			} while (map_number < 1);
			client.create_game(timeout,map_number);
		}
		else
		{
			do // dokud neni zadano spravne cislo hry
			{
				repeat=0;
				std::cout<<"Zadejte cislo hry (musí být validní)"<<std::endl;
				std::cin >> game_type;
				game_number=std::stoi(game_type);
			} while (repeat!=1);
			client.join_game(game_number);
		}

		// hrani
		int konec;
		std::string move="stop";

		do // dokud neni konec tak provadej tahy
		{
			std::cout<<"Jaký chceš provést tah? (go, right, left, stop, take, open)"<<std::endl;
			std::cin>>move;
			client.send_move(move);
			konec=client.accept_state_map();
		} while (!konec);

	}







	catch (Errors & e)
	{
		std::cerr<<e.get_message()<<std::endl;
		exit(1);
	}

	return 0;
}
