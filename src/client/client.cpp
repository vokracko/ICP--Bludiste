/**
*\file client.cpp
* Soubor obsahující implementaci metod třídy Client
*\author Michal Veselý (xvesel63)
*/

#include "client.h"
#include <iostream>
#include <QHostAddress>
#include "../errors.h"
#include <string>


Client::Client(QObject * parent): QObject(parent){setlocale(LC_NUMERIC,"C");	}
Client::~Client(){;}

/**
*\fn void Client::connect_socket(char * host)
* Provede a zkontroluje připojení ke QT socketu.
*\param host Adresa, na kterou se připojuje client
*\return True, pokud se podaří připojit, jinak False
*/
int Client::connect_socket(const char * host)
{
	client_socket = new QTcpSocket(this);
	QHostAddress addr(QString::fromStdString(host));
	client_socket->connectToHost(host, 1234);
	if (client_socket->waitForConnected(5000))
	{
		return 1;
	}
	else
	{
		throw Errors(Errors::SOCKET_CONNECT);
	}
	return 0;
}

// nacte data ze socketu
// vyvola vyjimku v pripade chyby
void read_from_socket(QTcpSocket * client_socket , std::string &msg)
{	
	msg="";
	char buffer[100]={0,};
	int cont=1;
	while(cont>0)
	{
		cont=client_socket->read(buffer,100);
		msg+=buffer;
		memset(buffer,0,100);
	}
	if (cont<0) throw Errors(Errors::SOCKET_READ);
}

/**
*\fn void get_games()
* Přijme od serveru informace o všech rozehraných hrách
* \return True, pokud nedojde k vyvolání výjimky
*/
int Client::get_games()
{
	client_socket->write("list\r\n");
	if (this->client_socket->waitForReadyRead(5000))
	{
		read_from_socket(this->client_socket,this->games);
	}
	else
	{
		throw Errors(Errors::SOCKET_READ);
		return 0;
	}
	// pokud nejsou zadne vytvorene hry
	if ((this->games).compare("0\r\n")==0) this->games="\r\n";
	return 1;
}


/**
*\fn void show_maps()
* Přijme od serveru informace o všech mapách k dispozici
* \return True, pokud nedojde k vyvolání výjimky
*/
int Client::show_maps()
{
	client_socket->write("maps\r\n");
	if (this->client_socket->waitForReadyRead(5000))
	{
		read_from_socket(this->client_socket,this->maps);
		return 1;
	}
	else
	{
		throw Errors(Errors::SOCKET_READ);
		return 0;
	}
}


/**
*\fn void Client::join_game(int game_id)
*Pošle serveru žádost o připojení do hry
*\param game_id Unikátní identifikátor hry generovaný serverem
* \return True, pokud nedojde k vyvolání výjimky
*/
int Client::join_game(int game_id)
{
	// zaslani zadosti o pripojeni do hry game_id
	client_socket->write((std::to_string(game_id)+"\r\n").c_str());
	if (!(client_socket->waitForBytesWritten(5000)))
	{
		throw Errors(Errors::WRITE_SOCKET);
		return 0;
	}

	//nacte si informace o hre a ulozi
	std::string game_info;

	if (client_socket->waitForReadyRead(5000)) read_from_socket(client_socket,game_info);
	else
	{
		throw Errors(Errors::SOCKET_READ);
		return 0;
	}

	// pokud se nepodarilo hru vytvorit, server posle invalid
	if (game_info.compare("invalid\r\n")==0)
	{
		throw Errors(Errors::NOT_JOINED);
		return 0;
	}

	// naskladani dat tam kam patri
	sscanf(game_info.c_str(),"%d %d %d %d %d",&(this->width),&(this->height),&(this->color),&(this->pos_x),&(this->pos_y));

	game_info=game_info.substr(game_info.find("\n")+1,game_info.size());
	std::cout<<game_info.size()<<"\n";
	// nacteni mapy
	int index=0;
	for (int i=0; i<this->height;i++)
		for (int j=0; j<this->width; j++)
		{   std::cout<<index<<" ";
			this->map[i][j]=game_info.at(index++);
		}
	return 1;
}


/**
*\fn void Client::create_game(int width, int height, double timeout)
* Pošle serveru žádost o vytvoření nové hry
*\param width Šířka v počtech hracích políček (omezeno na 20-50).
* V případě nedodržení limitu velikosti dojde k vyvolání vyjímky
*\param height Výška programu, stejný limit i reakce na jeho nedodržení jako u width
*\param timeout Časový interval, ve kterém dochází ke změnám ve hře
*\return True (různé od 0) pokud se podařilo vytvořit hru, jinak False
*/
int Client::create_game(double timeout, int map_type)
{
	if (timeout > 5 || timeout < 0.5)
	{
		throw Errors(Errors::TIMEOUT); // spatnej timeout, musi byt <0.5,5>
		return 0;
	}
	this->timeout=timeout;

	// zadost o vytoreni hry tvaru
	// timeout typ_mapy

	client_socket->write((std::to_string(this->timeout)+" "+std::to_string(map_type)+"\r\n").c_str());
	if (!(client_socket->waitForBytesWritten(5000)))
	{
		throw Errors(Errors::WRITE_SOCKET);
		return 0;
	}

	//nacte si informace o hre a ulozi
	std::string game_info;

	if (client_socket->waitForReadyRead(5000)) read_from_socket(client_socket,game_info);
	else
	{
		throw Errors(Errors::SOCKET_READ);
		return 0;
	}

	// pokud se nepodarilo hru vytvorit, server posle invalid
	if (game_info.compare("invalid\r\n")==0)
	{
		throw Errors(Errors::GAME_NOT_CREATED);
		return 0;
	}
	//std::cout<<"size: "<<game_info.size()<<"\n\n";
	// naskladani dat tam kam patri
	sscanf(game_info.c_str(),"%d %d %d %d %d",&(this->width),&(this->height),&(this->color),&(this->pos_x),&(this->pos_y));
	// sscanf(game_info.c_str(),"%d %d",&(this->width),&(this->height));
	// nacteni mapy
	game_info=game_info.substr(game_info.find("\n")+1,game_info.size());
	
	//std::cout<<game_info.size()<<"\n";
	//std::cout<<game_info;
	int index=0;
	for (int i=0; i<this->height;i++)
	{
		for (int j=0; j<this->width; j++)
		{
			this->map[i][j]=game_info.at(index++);
	    	//std::cout<<map[i][j];
		}
		//std::cout<<"\n";
	}
	return 1;
}

/**
\fn void Client::send_move(std::string command)
* Pošle serveru informaci o aktuálním tahu hráče
*\param std::string command Příkaz reprezentující tah (go,right,left,stop,take,open)
* \return True, pokud nedojde k vyvolání výjimky
*/
int Client::send_move(std::string command)
{
	if (command.compare("left")!=0 && command.compare("right")!=0 && command.compare("stop")!=0
	    && command.compare("go")!=0 && command.compare("take")!=0 && command.compare("open")!=0)
	{
		throw Errors(Errors::UNKNOWN_COMMAND);
		return 0;
	}
	client_socket->write((command+"\r\n").c_str());
	if (!(client_socket->waitForBytesWritten(5000)))
	{
		throw Errors(Errors::WRITE_SOCKET);
		return 0;
	}
	return 1;
}

/**
*\fn void Client::accept_state_map()
* Přečte ze socketu informace o aktuálním stavu hry a uloží je do atributu map
*\return 1 pokud je konec hry, jinak 0
*/
int Client::accept_state_map()
{
	std::string map_in_string;

	if (client_socket->waitForReadyRead(2000))
	{
		read_from_socket(client_socket,map_in_string);
	}
	else throw Errors(Errors::SOCKET_READ);

	// pokud je konec, vrati 1
	if (map_in_string.compare("end")==0) return 1;

	int index=0;
	for (int i=0; i<this->height;i++)
		for (int j=0; j<this->width; j++)
			this->map[i][j]=map_in_string.at(index++);

	// pokud konec neni vrati 0
	return 0;
}

