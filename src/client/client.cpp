/**
*\file client.cpp 
* Soubor obsahující implementaci metod třídy Client
*\author Michal Veselý (xvesel63)
*/

#include "client.h"
#include <iostream>
#include <QHostAddress>
#include "errors.h"

Client::Client(QObject * parent): QObject(parent){;}
Client::~Client(){;}

/**
*\fn void Client::connect_socket(char * host)
* Provede a zkontroluje připojení ke QT socketu.
*\param host Adresa, na kterou se připojuje client
*/
void Client::connect_socket(char * host)
{
	client_socket = new QTcpSocket(this);
	QHostAddress addr(QString::fromStdString(host));
	client_socket->connectToHost(host, 1234);
	if (client_socket->waitForConnected(3000))
	{
		std::cout<<"jsem tam"<<std::endl;
	}
	else throw Errors(Errors::SOCKET_CONNECT);
}

void Client::join_game()
{
	;
}


/**
*\fn void Client::create_game(int width, int height, double timeout)
* Pošle serveru žádost o vytvoření nové hry
*\param width Šířka v počtech hracích políček (omezeno na 20-50).
* V případě nedodržení limitu velikosti dojde k vyvolání vyjímky
*\param height Výška programu, stejný limit i reakce na jeho nedodržení jako u width
*\param timeout Časový interval, ve kterém dochází ke změnám ve hře  
*/	
void Client::create_game(int width, int height, double timeout)
{
	if (timeout > 5 || timeout < 0.5) throw Errors(Errors::TIMEOUT); // spatnej timeout, musi byt <0.5,5>
	if (width < 20 || width > 50) throw Errors(Errors::BOXES_WIDTH); // spatna sirka
	if (height < 20 || height > 50) throw Errors(Errors::BOXES_HEIGHT); // spatna vyska 
	
	this->width=width;
	this->height=height;
	this->timeout=timeout;
}
	
void Client::send_move()
{
	;
}
void Client::accept_state_map()
{
	;
}
void Client::show_games()
{
	;
}