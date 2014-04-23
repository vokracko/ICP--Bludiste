/**
*\file client_cli.cpp
* Soubor obsahující implementaci metod třídy Client_cli<br/>
* Rozšiřuje metody třídy Klient pouze o některé funkce výpisu, původní funkcionalita je jinak zachována a neměněna
*\author Michal Veselý (xvesel63)
*/

#include "client_cli.h"


void Client_cli::clear_screen()
{
    std::cout << "\x1B[2J\x1B[H";
}


/**
*\fn void Client_cli::print_map()
* Vypíše stav hrací plochy
*/
void Client_cli::print_map()
{
    for (int i=0; i < height; i++)
    {
        for (int j=0; j < width; j++)
        {
            std::cout << this->identify_element(map[i][j]);
        }
        std::cout<<std::endl;
    }
}

char Client_cli::identify_element(char element)
{
    switch (element)
    {
        case WALL :
            return 'W';
        case EMPTY :
            return ' ';
        case GATE_OPEN :
            return 'O';
        case GATE_CLOSE :
            return 'G';
        case KEY :
            return 'K';

        default:
            if (element==MONSTER_UP || element==MONSTER_DOWN || element==MONSTER_LEFT || element==MONSTER_RIGHT )
                return 'H';
            if (element/10==this->color)
            {
                switch (element%10)
                {
                    case 1:
                        return 'A';
                    case 2:
                        return '<';
                    case 3:
                        return 'V';
                    case 4:
                        return '>';
                    default : return 'A';
                };
            }
            else
            {
                return 'P';
            }
    };
    return 'X';
}


/**
*\fn void Client_cli::print_games()
* Vypíše rozehrané hry, ke kterým se lze připojit
*/
void Client_cli::print_games()
{
    this->get_games();
    std::cout<<this->games<<std::endl<<std::endl;
}

/**
*\fn void Client_cli::print_maps()
* Vypíše mapy, které jsou k dispozici pro založení nové hry
*/
void Client_cli::print_maps()
{
    this->show_maps();
    std::cout<<this->maps<<std::endl<<std::endl;
}

void Client_cli::print_color()
{
    std::cout<<std::endl<<this->refer_color()<<std::flush;
    events_list->push_back(this->refer_color());
}

void Client_cli::connect_readyRead()
{
    connect(this->client_socket,SIGNAL(readyRead()),this,SLOT(game_event()));

}

void Client_cli::print_times()
{

    std::cout<<"Čas strávený hráči ve hře a počet kroků, který vykonali:\n";

    if (this->white_time!=0.0)
        std::cout<<"čas bílého hráče: "<<white_time<<"  počet kroků: "<<white_steps<<std::endl;
    if (this->red_time!=0.0)
        std::cout<<"čas červeného hráče: "<<red_time<<"  počet kroků: "<<red_steps<<std::endl;
    if (this->blue_time!=0.0)
        std::cout<<"čas modrého hráče: "<<blue_time<<"  počet kroků: "<<blue_steps<<std::endl;
    if (this->green_time!=0.0)
        std::cout<<"čas zeleného hráče: "<<green_time<<"  počet kroků: "<<green_steps<<std::endl;

}

void Client_cli::print_all_events()
{
    std::cout<< "Všechny události co nastali během hry:\n\n";
    for (unsigned i=0; i<events_list->size() ;i++)
    {
        std::cout<<events_list->front()<<std::endl;
        events_list->pop_front();
    }
}

void Client_cli::game_event()
{

        // pole udalosti
    char events[MAX_EVENTS]={0,};
    int events_count;
    clear_screen();

    // vraci true pokud je konec hry:
    if (this->accept_state_map(events,&events_count))
    {
        // KONEC HRY
        print_all_events();
        std::cout<<this->get_game_time()<<std::endl;
        events_list->push_back(this->get_game_time());
        this->print_times();
        return;
    }
    // pokud neni konec hry
    // vypis specificke události do listu
    this->print_map();

    for (int i=0;i<events_count;i++)
    {
        std::string event=this->recognize_event(events[i]);
        if (event.compare("Byl jsi zabit")==0)
        {
            // kdyz umres
        }
        std::cout<<event<<std::endl;
        events_list->push_back(event);
    }

    std::cout<<std::endl<<this->msg;
    // zobrazeni mapy
    
}


Client_cli::Client_cli(QObject * parent): Client(parent)
{
    events_list = new std::deque <std::string>;
}
Client_cli::~Client_cli()
{
    delete events_list;
}
