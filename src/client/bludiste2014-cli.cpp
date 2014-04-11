/**
*\file bludiste2014_cli.cpp
*Obsahuje funkci main, demonstruje klienta pro konzolovou verzi bludiště
*\author Michal Veselý (xvesel63)
*/

#include "client_cli.h"
#include <QCoreApplication>
#include <iostream>
#include "errors.h"

int main (int argc, char * argv[])
{
	QCoreApplication a(argc, argv);
	Client_cli client;

	std::string host,game_type;
	int repeat=0;
	try
	{
		// ziskani serveru na pripojeni
		std::cout<<"Na jaky server se chcete pripojit? "<<std::endl;
		std::cin>>host;
		std::cout<<std::endl;
		client.connect_socket(const_cast<char *>(host.c_str())); 	

		// vypis her
		std::cout<<"Jsou vam k dispozici tyto hry:"<<std::endl<<std::endl;
		client.print_games();

		// vyber mezi join a create
		std::cout<<"Přejete se připojit k některé z těchto her, nebo si založit vlastní?"<<std::endl;
		
		int game_or_map,readed_int;
		float timeout;
		
		// dokud neni zadan spravny vyber, opakuj
		do
		{
			repeat=0;

			std::cout<<"Pro vytvoření hry vyberte typ mapy (1,2,3) a časový interval ve formátu [map_type timeout]"<<std::endl;
			std::cout<<"Pro připojeni se do existující hry zadejte identifikator hry ve formátu [ID_hry]"<<std::endl;
			std::cin>>game_type;
			std::cout<<std::endl;

			readed_int=sscanf(game_type.c_str(),"%d%f",&game_or_map,&timeout);
			if (readed_int==1) client.join_game(game_or_map); 
			else if (readed_int==2) client.create_game(timeout,game_or_map);
			else repeat=1;
		} while (repeat);

		// hrani
		int konec;
		std::string move="stop";
		konec=client.accept_state_map();
		do 
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