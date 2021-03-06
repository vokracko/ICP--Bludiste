/**
*\file client.h
*Hlavičkový soubor pro třídu Client <br/>
*Obsahuje aktualni stav hry<br/>
*Šířku a výšku hracího pole<br/>
*Barvu daného klienta<br/>
*Časovou prodlevu mezi tahy<br/>
*Pozici hráče ve hře <br/>
*počet navštívených polí a počet kroků<br/>
*čas strávený ve hře <br/>
*\author Michal Veselý (xvesel63)
*/


#pragma once

#include <iostream>
#include <QtCore>
#include <string>
#include <QObject>
 #include <QTcpSocket>
#include <QTimer>
#include "./../errors.h"
#include "./../box.h"


#define BUFFER_SIZE 1024
#define MAX_EVENTS 25

/**
\class Client
* Umožňuje připojit klienta k serveru pomocí QT <br/>
* Poslat serveru žádost o vytvoření nové hry <br/>
* Poslat žádost serveru o připojení se do již existující hry <br/>
* Zaslat serveru poslední tah, který se hráč chystá vykonat<br/>
* Přijmout změny posledního tahu hry<br/>
* Zobrazit všechny hry, k nimž je možnost se připojit a podrobnější informace k nim<br/>
*/

class Client: public QObject
{
    Q_OBJECT
public:
    QTcpSocket * client_socket;

private:
    int pos_x,pos_y;
    double timeout;
    bool connected_to_host;
protected:
    int color;
    int white_steps,red_steps,blue_steps,green_steps;
    int white_time,red_time,blue_time,green_time,game_duration;
public:
    int width,height;
    std::string games;
    std::string maps;
    char map[50][50];

public:
    explicit Client(QObject *parent=0);
    ~Client();
    int send_move(std::string command);
    void send_quit();
    int accept_state_map(unsigned char events[MAX_EVENTS],int * events_count);
    int connect_socket(const char * host);
    int create_game(double timeout,int map_type);
    int join_game(int game_id);
    int get_games();
    int show_maps();
    std::string get_game_time();
    std::string recognize_event(int event_code);
    std::string refer_color();
    std::string get_tooltip(int x,int y);

private:
    int parse_map(unsigned char events[MAX_EVENTS],int * events_count,std::string map_in_string,int event_index);

protected:
    std::string convert_string_time(int time_int);

};
