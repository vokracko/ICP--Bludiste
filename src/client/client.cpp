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
    this->last_command_successfull=true;
    client_socket=NULL;
}
Client::~Client()
{
    if (this->client_socket!=NULL)
    {
        this->send_quit();
        delete this->client_socket;
    }   
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
// po nacteni se pokusi nacist znovu, kdyby nahodou neprisla vsechna data v prvni zprave
void read_from_socket(QTcpSocket * client_socket , std::string &msg)
{
    msg="";

    char buffer[BUFFER_SIZE]={0,};
    int cont=1;
    int cont2=1;
    while(cont>0)
    {
        cont=client_socket->read(buffer,100);
        msg+=buffer;
        memset(buffer,0,100);
    }
    if (cont<0) throw Errors(Errors::SOCKET_READ);
    while (cont2)
    {
        if(client_socket->waitForReadyRead(50))
        {
            cont=1;
            while(cont>0)
            {
                cont=client_socket->read(buffer,100);
                msg+=buffer;
                memset(buffer,0,100);
            }
            if (cont<0) throw Errors(Errors::SOCKET_READ);
        }
        else
        {
            cont2=0;
        }
    }
    
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
    sscanf(game_info.c_str(),"%d %d %d %d %d %lf\r\n",&(this->width),&(this->height),&(this->color),&(this->pos_x),&(this->pos_y), &(this->timeout));

    game_info=game_info.substr(game_info.find("\n")+1,game_info.size());
    // nacteni mapy
    int index=0;
    for (int i=0; i<this->height;i++)
        for (int j=0; j<this->width; j++)
        {   //std::cout<<index<<" ";
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
    sscanf(game_info.c_str(),"%d %d %d %d %d\r\n",&(this->width),&(this->height),&(this->color),&(this->pos_x),&(this->pos_y));
    // sscanf(game_info.c_str(),"%d %d",&(this->width),&(this->height));
    // nacteni mapy
    
    //std::cout<<"size: "<<game_info.size()<<"\n";
    //std::cout<<game_info;
   
    game_info=game_info.substr(game_info.find("\n")+1,game_info.size());

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
    if (command.compare("left")!=0 && command.compare("right")!=0 && command.compare("stop")!=0 && command.compare("go")!=0
        && command.compare("step")!=0 && command.compare("take")!=0 && command.compare("open")!=0)
    {
        throw Errors(Errors::UNKNOWN_COMMAND);
        return 0;
    }
    /*if (command.compare("go")==0) 
    {
        command="step";
        this->last_command="go";
        printf("cas %d\n",(int)(this->timeout*1000));
        QTimer::singleShot(((int)(this->timeout*1000)),this,SLOT(when_go()));
    }
    else
    {*/
        this->last_command=command;
    //}
    client_socket->write((command+"\r\n").c_str());
    if (!(client_socket->waitForBytesWritten(5000)))
    {
        throw Errors(Errors::WRITE_SOCKET);
        return 0;
    }
    return 1;
}


/**
*\fn int Client::parse_map(unsigned char events[MAX_EVENTS],int * events_count,std::string map_in_string, int event_index)
* Přečte ze socketu informace o aktuálním stavu hry a uloží je do atributu map.<br />
* V případě, že je konec hry získá informace o hře (celkový čas hry, doba hry každého hráče, a počet kroků kolik hráč udělal).<br />
* V případě že není konec hry, ale nastane nějaká speciální událost, je součástí této zprávy a bude vyhodnocena (například úmrtí některého hráče apod.).<br />
* Socket client_socket je propoj se slotem v třídě game_window a tato metoda je invokována v případě, že na socket přijdou data obsahující mapu (obdobně pro CLI mód). <br />
* Může dojít k rekurzivnímu volání v případě, že došlo ke spojení více zpráv dohromady.
*\return 1 pokud je konec hry, jinak 0
* \param events Pole enum hodnot do kterého naplní funkce specifické události, které vznikly
* \param events_count Celočíselná proměnná, do které uloží funkce počet specifických událostí, které vznikly
* \param map_in_string Textová reprezentace mapy která byla zaslána serverem (může dojít ke spojení více zpráv dohromady)
* \param event_index, index od kterého se má plnit parametr events, kvůli možnosti spojení více zpráv dohromady.
*/
int Client::parse_map(unsigned char events[MAX_EVENTS],int * events_count,std::string map_in_string, int event_index)
{
        // pokud je konec, vraci 1 a zpracuje udaje o hre
    std::cout<<"mapa: \n"<<map_in_string<<std::endl<<std::flush;

    if (map_in_string.substr(0,3).compare("end")==0)
    {
        std::cout<<"jsem tady na konci\n"<<std::flush;
        this->last_command_successfull=false;
        map_in_string=map_in_string.substr(3,map_in_string.size()-5);
        std::cout<<"jsem tady na konci 2\n"<<std::flush;
        sscanf(map_in_string.c_str(),"%d\n%d %d\n%d %d\n%d %d\n%d %d\r\n",&(this->game_duration),&(this->red_time),&(this->red_steps),&(this->green_time),
                                                    &(this->green_steps),&(this->blue_time),&(this->blue_steps),&(this->white_time),&(this->white_steps));
        std::cout<<"jsem tady na konci 3\n"<<std::flush;
        return 1;
    }

    int index=0;

    for (int i=0; i<this->height;i++)
        for (int j=0; j<this->width; j++)
            this->map[i][j]=map_in_string.at(index++);

    std::string event_string;

    std::cout<<"mapa pred ziskanim end indexu:\n"<<map_in_string<<std::endl;
    int end_message_index=map_in_string.find("\r\n")+2;
    std::cout<<"endmsgind "<<end_message_index<<" mapinstrsiz "<<map_in_string.size()<<std::endl;
    event_string=map_in_string.substr(index,end_message_index-2-index);
    std::cout<<"events: "<<event_string<<std::endl<<std::flush;    
    map_in_string=map_in_string.substr(end_message_index,map_in_string.size()-end_message_index);
    std::cout<<"zbytek: "<<map_in_string<<std::endl<<std::flush;
    *events_count+=event_string.size();
    


    for (unsigned i=0; i< event_string.size(); i++)
    {
        // naplni udalosti
        events[event_index]=event_string.at(i);
        // kvuli go, uklada jestli se posledni tah povedl nebo ne
        if (events[event_index]==MOVE_PASS) this->last_command_successfull=true;
        if (events[event_index]==MOVE_FAIL) this->last_command_successfull=false;
        event_index++;
    }

    if (map_in_string.size()!=0) 
    {
        return parse_map(events,events_count,map_in_string,event_index);
    }
    std::cout<<"konec jednoho parse\n\n"<<std::flush;
    // pokud konec neni vrati 0
    return 0;

}



/**
*\fn void Client::accept_state_map()
* Volá funkci parse_map, která naplní pole events událostmi které vznikli, events_count počtem těchto událostí a events_count počtem těchto událostí.
* Počítá i s možností spojení více zpráv dohromady.
*\return 1 pokud je konec hry, jinak 0
* \param events Pole enum hodnot do kterého naplní funkce specifické události, které vznikly
* \param events_count Celočíselná proměnná, do které uloží funkce počet specifických událostí, které vznikly
*/
int Client::accept_state_map(unsigned char events[MAX_EVENTS],int * events_count)
{
    std::string map_in_string;

    read_from_socket(client_socket,map_in_string);
    std::cout<<"acc state map cela zprava: "<<std::endl;

    return parse_map(events,events_count,map_in_string,0);
}

/**
*\fn std::string Client::recognize_event(int event_code)
* Rozpozná událost která nastala podle event_code a vrátí textovou reprezentaci této informace.
* \param events_code Hodnota enumerátoru z events_enumerator.h, identifikující události
* \return Textový řetězec reprezentující informaci o události jenž je vypsána.
*/
std::string Client::recognize_event(int event_code)
{
    std::cout<<"cislo udalosti: "<<event_code<<std::endl;
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

        case RED_KEY :
            return "Červený hráč si vzal klíč";
        case GREEN_KEY :
            return "Zelený hráč si vzal klíč";
        case BLUE_KEY :
            return "Modrý hráč si vzal klíč";
        case WHITE_KEY :
            return "Bílý hráč si vzal klíč";

        case RED_OPEN :
            return "Červený hráč otevřel bránu";
        case GREEN_OPEN :
            return "Zelený hráč otevřel bránu";
        case BLUE_OPEN :
            return "Modrý hráč otevřel bránu";
        case WHITE_OPEN :
            return "Bílý hráč otevřel bránu";

        case RED_WIN :
            return "Červený hráč zvítězil";
        case GREEN_WIN :
            return "Zelený hráč zvítězil";
        case BLUE_WIN :
            return "Modrý hráč zvítězil";
        case WHITE_WIN:
            return "Bílý hráč zvítězil";
        case YOU_WIN:
            return "Vyhrál jsi! Gratulejeme ;-)";
    };


    // jinak
    return "Něco opomněného se stalo";
}

/**
*\fn std::string Client::refer_color()
* Rozpozná na základě atributu color z třídy Client o jakou se jedná barvu a vrátí výsledek jako textovou informaci, jenž může být vypsána.
* \return Textový řetězec reprezentující informaci o barvě.
*/
std::string Client::refer_color()
{
    switch (this->color)
    {
        case WHITE:	return "Jste bílý hráč";
        case RED: return "Jste červený hráč";
        case BLUE: return "Jste modrý hráč";
        case GREEN: return "Jste zelený hráč";
    }
    return "takovou barvu neznám";
}

/**
*\fn void Client::send_quit()
* Pošle informaci o ukončení klienta serveru.
*/
void Client::send_quit()
{
    this->client_socket->write("quit\r\n");
}


/**
* \fn std::string Client::convert_string_time(int time_int)
* Převede čas ze sekund na string tvaru Xh Ym Zs
* \param time_int Čas v sekundach 
*/
std::string Client::convert_string_time(int time_int)
{
    int hours;
    int mins;
    int secs;
    hours=time_int/3600;
    time_int-=3600*hours;
    mins=time_int/60;
    time_int-=mins*60;
    secs=time_int;
    
    return std::to_string(hours)+"h "+std::to_string(mins)+"m "+std::to_string(secs)+"s";
}


/**
*\fn std::string Client::get_game_time()
* \return Vrátí textovou informaci a době trvání hry.
*/
std::string Client::get_game_time()
{
    return "Hra trvala "+convert_string_time(this->game_duration);
}

/**
*\fn std::string Client::get_tooltip(int x,int y)
* Získá informaci o konkrétním políčku a vrátí hint (tooltip), který má být tomuto políčku přiřazen.
* \param x X-ová souřadnice hráče na mapě
* \param y Y-ová souřadnice hráče na mapě
* \return Textový řetězec reprezentující informaci o hráči, obsahující počet kroků a čas strávený ve hře.
*/
std::string Client::get_tooltip(int x,int y)
{
    if (this->map[x][y]/10==WHITE)
    {
        return "Bílý hráč:\nPočet kroků: "+std::to_string(this->white_steps)+"\nČas strávený ve hře: "+convert_string_time(this->white_time);
    }
    
    if (this->map[x][y]/10==GREEN)
    {
        return "Zelený hráč:\nPočet kroků: "+std::to_string(this->green_steps)+"\nČas strávený ve hře: "+convert_string_time(this->green_time);
    }

    if (this->map[x][y]/10==BLUE)
    {
        return "Modrý hráč:\nPočet kroků: "+std::to_string(this->blue_steps)+"\nČas strávený ve hře: "+convert_string_time(this->blue_time);
    }

    if (this->map[x][y]/10==RED)
    {
        return "Červený hráč:\nPočet kroků: "+std::to_string(this->red_steps)+"\nČas strávený ve hře: "+convert_string_time(this->red_time);
    }
    return "";
}
