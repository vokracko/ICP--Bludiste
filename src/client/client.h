/**
*\file client.h
*Hlavičkový soubor pro třídu Client <br/>
*Obsahuje aktualni stav hry<br/> 
*Šířku a výšku hracího pole<br/>
*Barvu daného klienta<br/>
*Časovou prodlevu mezi tahy<br/>
*Pozici hráče ve hře
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
protected:
	int color; 
	int pos_x,pos_y;
	int width,height;
	int map[50][50];
	double timeout;	
public:
	explicit Client(QObject *parent=0);
	~Client();
	void send_move();
	void accept_state_map();
	void show_games();
	void connect_socket(char * host);
	void create_game(int width, int height, double timeout);
	void join_game();
};