/**
*\file client_cli.cpp
* Soubor obsahující implementaci metod třídy Client_cli<br/>
* Rozšiřuje metody třídy Klient pouze o některé funkce výpisu, původní funkcionalita je jinak zachována a neměněna
*\author Michal Veselý (xvesel63)
*/

#include "client_cli.h"
#include <sys/types.h>
#include <sys/wait.h>

/**
*\fn void Client_cli::clear_screen()
* Smaže obsah konzole a přesune kursor do pravého horního rohu
*/
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


/**
*\fn char Client_cli::identify_element(char element)
* Převede vstupní znak na výstupní znak srozumitelně reprezentující význam prvku na mapě. <br />
* W = zeď, O=otevřená brána , G=zavřená brána, K=klíč, H=hlídač, P=protihráč a hráč hrající na tomto klientovi je reprezentován znaky "A,<,>,V" podle natočení.
* \return Znak symbolizující element na mapě
* \param element Znak získaný od serveru, jehož význam chceme konvertovat do srozumitelné podoby.
*/
char Client_cli::identify_element(char element)
{
    switch (element)
    {
        case Box::WALL :
            return 'W';
        case Box::EMPTY :
            return ' ';
        case Box::GATE + Box::OPEN :
            return 'O';
        case Box::GATE + Box::CLOSED :
            return 'G';
        case Box::KEY :
            return 'K';

        default:
            if (element==Box::MONSTER + Box::UP || element==Box::MONSTER + Box::DOWN || element==Box::MONSTER+Box::LEFT || element==Box::MONSTER +Box::RIGHT )
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

void Client_cli::end_processes()
{
    kill(this->pid_child,SIGTERM);
    delete this;
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

/**
*\fn void Client_cli::print_color()
* Vypíše barvu a uloží si ji do seznamu událostí.
*/
void Client_cli::print_color()
{
    this->last_message=this->refer_color()+"\n";
    std::cout<<this->last_message;
}

/**
*\fn void Client_cli::connect_readyRead()
* připojí signál readyRead k socketu klienta.
*/
void Client_cli::connect_readyRead()
{
    connect(this->client_socket,SIGNAL(readyRead()),this,SLOT(game_event()));

}


/**
*\fn void Client_cli::print_times()
* Vypíše čas, který strávili jednotlivý hráči ve hře a počet kroků, které vykonali.
*/
void Client_cli::print_times()
{
    std::cout<<"Čas strávený hráči ve hře a počet kroků, který vykonali:\n";

    if (this->white_time!=0.0)
        std::cout<<"čas bílého hráče: "<<this->convert_string_time(this->white_time)<<"  počet kroků: "<<white_steps<<std::endl;
    if (this->red_time!=0.0)
        std::cout<<"čas červeného hráče: "<<this->convert_string_time(this->red_time)<<"  počet kroků: "<<red_steps<<std::endl;
    if (this->blue_time!=0.0)
        std::cout<<"čas modrého hráče: "<<this->convert_string_time(this->blue_time)<<"  počet kroků: "<<blue_steps<<std::endl;
    if (this->green_time!=0.0)
        std::cout<<"čas zeleného hráče: "<<this->convert_string_time(this->green_time)<<"  počet kroků: "<<green_steps<<std::endl;
}

void Client_cli::sap_events_message(int events_count,unsigned char events[MAX_EVENTS])
{
    bool end=false;
    std::string event;
    if (events_count!=0)
            this->last_message="";


    for (int i=0;i<events_count;i++)
    {

        event=this->recognize_event(events[i]);
        this->last_message+=(event+"\n");
        std::cout<<this->last_message<<std::endl;

        if (event == "Byl jsi zabit")
        {
            this->end_processes();
            exit(0);
        }

    }
}

/**
*\fn void Client_cli::game_event()
* Slot, který je vyvolán při signálu readyRead. Vyčistí obrazovku, přijme stav mapy a události které nastali a vše vypíše.
* Zároveň definuje chování na konci hry a v případě zabití hráče.
*/
void Client_cli::game_event()
{

        // pole udalosti
    unsigned char events[MAX_EVENTS]={0,};
    int events_count=0;
    clear_screen();

    // vraci true pokud je konec hry:
    if (this->accept_state_map(events,&events_count))
    {
        // KONEC HRY
        this->print_map();
        sap_events_message(events_count,events);

        std::cout<<this->get_game_time()<<std::endl;
        this->print_times();

        end_processes();
        exit(0) ;
        return;
    }
    // pokud neni konec hry
    // vypis specificke události do listu
    this->print_map();
    sap_events_message(events_count,events);
}

void Client_cli::playing()
{
    this->game_begin=true;
    int pid=fork();

    if (pid==0)
    {
        while (1)
        {
            std::string move;
            std::cin>>move;
            try
            {
                this->send_move(move);
            }
            catch (Errors & e)
            {
                std::cout<< e.what() <<std::endl;
                if (e.code!=Errors::UNKNOWN_COMMAND)
                {
                    exit(1);
                }
            }
        }
    }
    else if (pid>0)
    {
        this->pid_child=pid;
        this->connect_readyRead();
    }
    else
    {
        try
        {
            throw Errors(Errors::FORK);
        }
         catch (Errors & e)
        {
            std::cerr<< e.what() <<std::endl;
            exit(1);
        }
    }
}

Client_cli::Client_cli(QObject * parent): Client(parent)
{
    game_begin=false;
}
Client_cli::~Client_cli()
{

}
