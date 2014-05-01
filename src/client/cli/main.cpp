/**
*\file main.cpp
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

/**
\fn int get_cin_integer()
 \brief Načte z cin číslo typu integer.
 \return number pokud je zadano spravne a -1 pokud nespravne
*/
int get_cin_integer()
{
    std::string str;
    std::cin>>str;
    char * endptr;
    int number=(int)strtol(str.c_str(),&endptr,10);
    if (*endptr=='\0') return number;
    else return -1;
}

/**
\fn double get_cin_double()
 \brief Načte z cin číslo typu double.
 \return double číslo pokud je zadáno spravne a -1.0 pokud nesprávně
*/
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

/**
\fn void  INThandler(int sig)
\brief Reakce na ukončení programu signálem ctrl+c
* V případě že je program ukončen signálem ctrl+c je serveru zaslána informace o ukončení hry (v destruktoru klienta, který je zde invokován).<br />
* V případě že je hra již ve stádiu hraní, tak se současně ukončí čtecí proces.
*/
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

/**
\fn int main (int argc, char * argv[])
* \brief Řídí celou cli aplikaci, pracující s třídou Client_cli (potomek Client).
* Získá od uživatele server ke kterému se chce připojit, nechá jej vybrat si zda se chce připojit do existující hry nebo vytvořit novou,
* plus případné parametry hry (timeout, mapa, číslo hry apod.). Poté už probíhá samotné hraní hry.
*/
int main (int argc, char * argv[])
{
    QCoreApplication a(argc, argv);
    setlocale(LC_NUMERIC,"C");
    signal(SIGINT, INThandler);

    std::string host,game_type = "";

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

        // vyčistí obrazovku
        client->clear_screen();

        // vypsání informací o hře (první mapa a barva)
        client->print_map();
        client->print_color();
        std::cout<<std::endl;

        //samotné hraní hry
        client->playing();

    return a.exec();
}
