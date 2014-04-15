/**
*\file game_window.cpp
* Soubor implementující třídu game_window. Vygenerováno pomocí QT Creator s rozšířením o některé atributy a metody.<br/>
* Implementuje hrací okno hry. Používá třídu Game_field pro zobrazení hrací plochy.
*\author Michal Veselý (xvesel63)
*/

#include "game_window.h"
#include "ui_game_window.h"
#include "./../../errors.h"
#include <unistd.h>


game_window::game_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game_window)
{
    ui->setupUi(this);
}


/**
*\fn void game_window::fullfill_client_reference(Client * client)
* Naplní odkaz na třídu Client obsahující funkce pro komunikaci se serverem a informace o hráči.
*/
void game_window::fullfill_client_reference(Client * client)
{
    this->client=client;
}

/**
*\fn void game_window::create_game_field()
* Funkce pro vytvoření hracího okna. Dynamicky nastavuje velikost okna podle rozměrů hrací plochy. 
* Dynamicky umisťuje jednotlivé komponenty podle rozměrů okna. 
* alokuje hrací plochu a propojuje ji s mřížkou umístěnou v grafickém rozhraní.
*/
void game_window::create_game_field()
{
    // 13 je velikost jednoho hraciho policka
    // sirka je potom 13 krat pocet bodu do sirky + 5 (mirne odsazeni)
    // obdobne vyska, pricita se 60 pro vypis chybovych hlasek a zadavani prikazu pohybu
    int width=13*this->client->width+15;
    int height=13*this->client->height+80;
    if (width<475) width=475;
    if (height<330) height=330;
    this->setGeometry(50,50,width,height);

    // nastaveni pozice a velikosti vnitrnich objektu okna
    this->ui->when_error_label->setGeometry(10,5,width-20,25);
    this->ui->zadej_prikaz_label->setGeometry(10,30,130,25);
    this->ui->command_edit->setGeometry(140,30,150,25);
    this->ui->send_command_button->setGeometry(300,30,120,25);


    //QImage box("./../../../images/green-up.png");
    //this->ui->game_field->addItem(box);

    // vytvoreni herniho pole

    this->game_field = new Game_field(this->client->height,this->client->width);
    this->game_field->set_map(this->client->map);
    for (int i=0;i<this->client->height;i++)
        for (int j=0;j<this->client->width;j++)
            this->ui->grid->addWidget((this->game_field->field[i][j]),i,j);

    //this->ui->grid=&(*game_field);


   // game_field->field[0][0]->setPixmap(*(game_field->wall));
    //this->ui->grid->addWidget((game_field->field[0][0]),0,0);
    //game_field->field[0][0]->setPixmap(*(game_field->empty));
    //game_field->field[0][0]->setPixmap(*(game_field->monster_up));
}



void game_window::print_map()
{
    this->client->accept_state_map();
    this->game_field->set_map(this->client->map);

    this->client->accept_state_map();
    this->game_field->set_map(this->client->map);
}

game_window::~game_window()
{
    delete game_field;
    delete ui;
}


/**
*\fn void game_window::on_send_command_button_clicked()
* Slot reagující na signál vyvolaný stisknutím tlačítka potvrzení příkazu. V případě chyby (neexistujícího příkazu)
* dojde k vyvolání výjimky a vypsání chybové hlášky (bez ukončení programu).
*/
void game_window::on_send_command_button_clicked()
{
    try
    {
        this->client->send_move(this->ui->command_edit->text().toStdString());
    }
    catch (Errors & e)
    {
         this->ui->when_error_label->setText(QString::fromStdString(e.get_message()));
    }
}
