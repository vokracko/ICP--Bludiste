/**
*\file bludiste2014_cli.cpp
*Obsahuje funkci main, demonstruje klienta pro konzolovou verzi bludiště
*\author Michal Veselý (xvesel63)
*/

#include "client_cli.h"
#include <QTcpSocket>
#include <iostream>
#include "./../../errors.h"
#include <locale.h>
#include <fcntl.h>
#include <string.h>

// nacte z cin integer
// vraci number pokud je zadano spravne a -1 pokud nespravne
int get_cin_integer()
{
    std::string str;
    std::cin>>str;
    char * endptr;
    int number=(int)strtol(str.c_str(),&endptr,10);
    if (*endptr=='\0') return number;
    else return -1;
}

// nacte z cin float
// vraci number pokud je zadano spravne a -1.0 pokud nespravne
double get_cin_double()
{
    std::string str;
    std::cin>>str;
    char * endptr;
    double number=(double)strtod(str.c_str(),&endptr);
    if (*endptr=='\0') return number;
    else return -1.0;
}


Client_cli * client= new Client_cli;

void  INThandler(int sig)
{
     signal(sig, SIG_IGN);
     if (client->game_begin) client->end_processes();
     else
     {
        delete client;
     }
     std::cout<<"\n\nHra byla ukončena (násilí nic nevyřeší)!\n\n";
     exit(0);
}

void read_from_cin(std::string * msg)
{
    std::cin>>*msg;
}

void send_message(std::string msg)
{
    client->send_move(msg);
}


/**
\fn Main
* Řídí celou cli aplikaci, pracující s třídou Client_cli (potomek Client).
*/
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
            join=get_cin_integer();
        } while (join!=1 && join!=2);

        // zalozeni nove hry
        if (join==1)
        {
            do // dokud neni zadan spravny timeout
            {
                std::cout<<"Zadejte timeout hry (v intervalu <0.5 ; 5>)"<<std::endl;
                //game_type="";
                //std::cin>>game_type;
                timeout=get_cin_double();
            } while (timeout < 0.5 || timeout > 5);

            do // dokud neni zadan spravne index mapy
            {
                std::cout<<"Zadejte cislo mapy (musí být validní)"<<std::endl;
                //game_type="";
                //std::cin >> game_type;
                map_number=get_cin_integer();
            } while (map_number < 0);
            client->create_game(timeout,map_number);
        }
        else
        {
            do // dokud neni zadano spravne cislo hry
            {
                std::cout<<"Zadejte cislo hry (musí být validní)"<<std::endl;
                game_number=get_cin_integer();
            } while (game_number == -1);
            client->join_game(game_number);
        }
    }
    catch (Errors & e)
    {
        std::cerr<< e.what() <<std::endl;
        exit(1);
    }

        // hrani
        int konec;

        // vyčistí obrazovku
        client->clear_screen();
        client->print_map();
        client->print_color();
        std::cout<<std::endl;
        client->playing();




    return a.exec();
}
