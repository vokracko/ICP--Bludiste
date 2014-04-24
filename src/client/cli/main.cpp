/**
*\file bludiste2014_cli.cpp
*Obsahuje funkci main, demonstruje klienta pro konzolovou verzi bludiště
*\author Michal Veselý (xvesel63)
*/

#include "client_cli.h"
#include <QTcpSocket>
#include <iostream>
#include "./../../errors.h"
#include <stdio.h>
#include <locale.h>
#include  <signal.h>
#include <deque>
#include  <unistd.h>
#include <thread>



Client_cli * client= new Client_cli;

void  INThandler(int sig)
{
     signal(sig, SIG_IGN);

     delete client;

     std::cout<<"\n\nHra byla ukončena (násilí nic nevyřeší)!\n\n";
     exit(0);
}

void read_from_cin(Client_cli * client)
{
    std::cin>>client->msg;
}

void catch_signal(Client_cli * client)
{
    client->connect_readyRead();
}

int main (int argc, char * argv[])
{
    QCoreApplication a(argc, argv);
    setlocale(LC_NUMERIC,"C");


    signal(SIGINT, INThandler);

    std::string host,game_type = "";
    int repeat=0;
    try
    {
        // ziskani serveru na pripojeni
        std::cout<<"Na jaky server se chcete pripojit? "<<std::endl;
        // host="localhost";
        std::cin>>host;
        std::cout<<std::endl;
        client->connect_socket(const_cast<char *>(host.c_str()));

        // vypis her
        std::cout<<"Jsou vam k dispozici tyto mapy:" <<std::endl<<std::endl;
        client->print_maps();

        std::cout<<"Jsou vam k dispozici tyto hry:"<<std::endl<<std::endl;
        client->print_games();


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
            client->create_game(timeout,map_number);
        }
        else
        {
            do // dokud neni zadano spravne cislo hry
            {
                repeat=0;
                std::cout<<"Zadejte cislo hry (musí být validní)"<<std::endl;
                repeat=scanf("%d",&game_number);
            } while (repeat!=1);
            client->join_game(game_number);
        }

        // hrani
        int konec;
        

        client->clear_screen();
        client->print_map();
        client->print_color();
        std::cout<<std::endl;

        

        //std::thread read_thread(read_from_cin,client); 
        std::thread catch_signal_thread(catch_signal,client);


        //read_thread.join();
        catch_signal_thread.join();

        //std::cout<<"jsem tadz\n";
        //read_from_cin(client);
        //std::cout<<"a pak i  tadz\n";
        //std::cout<<client->msg<<std::endl;

    }

    catch (Errors & e)
    {
        std::cerr<<e.get_message()<<std::endl;
        exit(1);
    }

    return a.exec();
}
