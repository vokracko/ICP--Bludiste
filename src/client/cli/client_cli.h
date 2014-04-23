#pragma once
/**
*\file client_cli.h
* Soubor obsahující implementaci hlavičky třídy Client_cli<br/>
*Potomek Třídy Client, jenž reimplementuje některé funkce tak, aby pracovali pouze s konzolí
*\author Michal Veselý (xvesel63)
*/

#include "./../client.h"
#include "./../../game_components.h"
#include "./../../events_enumerator.h"
#include <deque>
#include <QObject>


/**
\class Client_cli
* Rozšiřuje třídu Client o metody výpisu na konzoli pro konzolovou verzi hry.
*/
class Client_cli : public Client
{
    Q_OBJECT
public:
    std::string msg;

private:
    std::deque<std::string> * events_list;
public:
    void print_map();
    void print_games();
    void print_maps();
    void print_color();
    void connect_readyRead();
    void clear_screen();
    Client_cli(QObject *parent=0);
    ~Client_cli();
    

private:
    char identify_element(char element);
    void print_all_events();
    void print_times();

public slots:
    void game_event();
    
};
