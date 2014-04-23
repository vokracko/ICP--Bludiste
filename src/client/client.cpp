/**
*\file client.cpp
* Soubor obsahující implementaci metod třídy Client
*\author Michal Veselý (xvesel63)
*/

#include "client.h"
#include <iostream>
#include <QHostAddress>
#include <string>

Client::Client(QObject * parent): QObject(parent)
{
    setlocale(LC_NUMERIC,"C");
    color=4;
    white_steps=0;
    red_steps=0;blue_steps=0;
    green_steps=0;
    white_time=0;
    red_time=0;
    blue_time=0;
    green_time=0;
    game_duration=0;
}
Client::~Client()
{
    if (this->client_socket!=NULL)
        this->send_quit();
}

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
* Přečte ze socketu informace o aktuálním stavu hry a uloží je do atributu map.<br />
* V případě, že je konec hry získá informace o hře (celkový čas hry, doba hry každého hráče, a počet kroků kolik hráč udělal).<br />
* V případě že není konec hry, ale nastane nějaká speciální událost, je součástí této zprávy a bude vyhodnocena (například úmrtí některého hráče apod.).<br />
* Socket client_socket je propoj se slotem v třídě game_window a tato metoda je invokována v případě, že na socket přijdou data obsahující mapu (obdobně pro CLI mód). <br />
*\return 1 pokud je konec hry, jinak 0
* \param events Pole enum hodnot do kterého naplní funkce specifické události, které vznikly
* \param events_count Celočíselná proměnná, do které uloží funkce počet specifických událostí, které vznikly
*/
int Client::accept_state_map(char events[MAX_EVENTS],int * events_count)
{
    std::string map_in_string;

    read_from_socket(client_socket,map_in_string);

    // pokud je konec, vraci 1 a zpracuje udaje o hre
    if (map_in_string.substr(0,5).compare("end\r\n")==0)
    {
        map_in_string=map_in_string.substr(5,map_in_string.size());
        sscanf(map_in_string.c_str(),"%lf\n%lf %d\n%lf %d\n%lf %d\n%lf %d\n",&(this->game_duration),&(this->white_time),&(this->white_steps),&(this->red_time),
               &(this->red_steps),&(this->green_time),&(this->green_steps),&(this->blue_time),&(this->blue_steps));
        return 1;
    }

    int index=0;
    for (int i=0; i<this->height;i++)
        for (int j=0; j<this->width; j++)
            this->map[i][j]=map_in_string.at(index++);

    map_in_string=map_in_string.substr(index,map_in_string.size());

    *events_count=map_in_string.size();
    //std::cout<<*events_count<<"\n";

    for (int i=0; i< *events_count; i++)
    {
        events[i]=map_in_string.at(i);
    }

    // pokud konec neni vrati 0
    return 0;
}

std::string Client::recognize_event(int event_code)
{
    if (event_code==WHITE_KILLED && color==WHITE)
        return "Byl jsi zabit";
    if (event_code==RED_KILLED && color==RED)
        return "Byl jsi zabit";
    if (event_code==BLUE_KILLED && color==BLUE)
        return "Byl jsi zabit";
    if (event_code==GREEN_KILLED && color==GREEN)
        return "Byl jsi zabit";

    switch (event_code)
    {
        case WHITE_KILLED:
            return "Bílý hráč byl zabit";
        case RED_KILLED:
            return "Červený hráč byl zabit";
        case GREEN_KILLED:
            return "Zelený hráč byl zabit";
        case BLUE_KILLED:
            return "Modrý hráč byl zabit";

        case WHITE_CONNECTED:
            return "Bílý hráč byl připojen do hry";
        case RED_CONNECTED:
            return "Červený hráč byl připojen do hry";
        case GREEN_CONNECTED:
            return "Zelený hráč byl připojen do hry";
        case BLUE_CONNECTED:
            return "Modrý hráč byl připojen do hry";

        case WHITE_DISCONNECTED:
            return "Bílý hráč se odpojil ze hry";
        case RED_DISCONNECTED:
            return "Červený hráč se odpojil ze hry";
        case GREEN_DISCONNECTED:
            return "Zelený hráč se odpojil ze hry";
        case BLUE_DISCONNECTED:
            return "Modrý hráč se odpojil ze hry";

        case MOVE_PASS:
            return "Tah byl úspěšný";
        case MOVE_FAIL:
            return "Tah byl neúspěšný";
    };

    // jinak
    return "Něco opomněného se stalo";
}

std::string Client::refer_color()
{
    switch (this->color)
    {
        case WHITE:	return "Jste bílý hrýč";
        case RED: return "Jste červený hrýč";
        case BLUE: return "Jste modrý hrýč";
        case GREEN: return "Jste zelený hrýč";
    }
    return "takovou barvu neznám";
}

void Client::send_quit()
{
    this->client_socket->write("quit\r\n");
}

std::string Client::get_game_time()
{
    return "Hra trvala "+std::to_string(this->game_duration);
}


std::string Client::get_tooltip(int x,int y)
{
    if (this->map[x][y]/10==WHITE)
    {
        return "Bílý hráč:\nPočet kroků: "+std::to_string(this->white_steps)+"\nČas strávený ve hře: "+std::to_string(this->white_time);
    }
    
    if (this->map[x][y]/10==GREEN)
    {
        return "Zelený hráč:\nPočet kroků: "+std::to_string(this->green_steps)+"\nČas strávený ve hře: "+std::to_string(this->green_time);
    }

    if (this->map[x][y]/10==BLUE)
    {
        return "Modrý hráč:\nPočet kroků: "+std::to_string(this->blue_steps)+"\nČas strávený ve hře: "+std::to_string(this->blue_time);
    }

    if (this->map[x][y]/10==RED)
    {
        return "Červený hráč:\nPočet kroků: "+std::to_string(this->red_steps)+"\nČas strávený ve hře: "+std::to_string(this->red_time);
    }
    return "";
}
