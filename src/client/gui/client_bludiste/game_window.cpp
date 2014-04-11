#include "game_window.h"
#include "ui_game_window.h"

game_window::game_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game_window)
{
    ui->setupUi(this);
}

void game_window::fullfill_client_reference(Client_gui * client)
{
    this->client=client;
}

void game_window::create_game_field()
{
    // 13 je velikost jednoho hraciho policka
    // sirka je potom 13 krat pocet bodu do sirky + 5 (mirne odsazeni)
    // obdobne vyska, pricita se 60 pro vypis chybovych hlasek a zadavani prikazu pohybu
    this->setBaseSize(13*this->client->width+5,13*this->client->height+60);

    // vytvoreni hernich poli
    for (int i=0;i<this->client->height;i++)
        for (int j=0; j<this->client->width;j++)
        {
            ;
        }
}

game_window::~game_window()
{
    delete ui;
}
