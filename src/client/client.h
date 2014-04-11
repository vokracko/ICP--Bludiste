#pragma once

/**
*\file client.h
*Hlavičkový soubor pro třídu Client <br/>
*Obsahuje aktualni stav hry<br/> 
*Šířku a výšku hracího pole<br/>
*Barvu daného klienta<br/>
*Časovou prodlevu mezi tahy<br/>
*Pozici hráče ve hře
*počet navštívených polí a počet kroků
*čas strávený ve hře
*\author Michal Veselý (xvesel63)
*/

#include <iostream>
#include <QtCore>
#include <QtNetwork>
#include <string>
#include <QObject>
#include <QTcpSocket>

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
	QTcpSocket * client_socket;

public:
	int color; 
	int pos_x,pos_y;
	int width,height;
	char map[50][50];
	int time_in_game;
	int steps;
	int visit_boxes;
	std::string games;
	std::string maps;
	double timeout;	
public:
	explicit Client(QObject *parent=0);
	~Client();
	void send_move(std::string command);
	int accept_state_map();
	int connect_socket(const char * host);
	void create_game(double timeout,int map_type);
	void join_game(int game_id);
	void get_games();
	void show_maps();
};