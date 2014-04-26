/**
*\file game_window.cpp
* Soubor implementující třídu game_window. Vygenerováno pomocí QT Creator s rozšířením o některé atributy a metody.<br/>
* Implementuje hrací okno hry. Používá třídu Game_field pro zobrazení hrací plochy.
*\author Michal Veselý (xvesel63)
*/

#include "game_window.h"
#include "ui_game_window.h"
#include "./../../../errors.h"
#include "./../../../events_enumerator.h"

game_window::game_window(Client * client,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game_window)
{
    ui->setupUi(this);
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
    int width=13*this->client->width+315;
    int height=13*this->client->height+55;

    if (height<305) height=305;
    this->setGeometry(50,50,width,height);

    // nastaveni pozice a velikosti vnitrnich objektu okna
    this->ui->zadej_prikaz_label->setGeometry(10,10,130,25);
    this->ui->command_edit->setGeometry(140,10,150,25);
    this->ui->send_command_button->setGeometry(300,10,120,25);

    this->ui->game_info_label->setGeometry(this->client->width*13+25,40,200,25);
    this->ui->game_info_list->setGeometry(this->client->width*13+25,70,275,height-85);

    this->game_field = new Game_field(this->client->height,this->client->width);
    game_field->set_map(this->client->map);

    QApplication::processEvents();

    for (int i=0;i<this->client->height;i++)
        for (int j=0;j<this->client->width;j++)
            this->ui->grid->addWidget((this->game_field->field[i][j]),i,j);

    this->game_field->set_map(this->client->map);
    QApplication::processEvents();

    this->ui->game_info_list->addItem(QString::fromStdString(this->client->refer_color()));

    connect(this->client->client_socket,SIGNAL(readyRead()),this,SLOT(game_showing()));

}

/**
*\fn void game_window::assign_tooltips()
* Vyhledá na hrací ploše hráče a každému přiřadí tooltip obsahující počet kroků a čas strávený ve hře.
*/
void game_window::assign_tooltips()
{
    for (int i=0;i<this->client->height;i++)
        for (int j=0;j<this->client->width;j++)
        {
            this->game_field->field[i][j]->setToolTip(QString::fromStdString(this->client->get_tooltip(i,j)));
        }
    QApplication::processEvents();

}

/**
*\fn void game_window::show_happend_events(unsigned char events[MAX_EVENTS],int events_count)
* Vypíše do list widgetu umístěném v hracím okně poslední události, které nastali.
* \param events Pole událostí jenž nastali při posledním zaslání mapy od sereveru
* \param events_count Počet událostí které nastali
*/
void game_window::show_happend_events(unsigned char events[MAX_EVENTS],int events_count)
{
    for (int i=0;i<events_count;i++)
    {
        std::string event=this->client->recognize_event(events[i]);
        if (event.compare("Byl jsi zabit")==0)
        {
            this->ui->send_command_button->setVisible(false);
            this->ui->command_edit->setVisible(false);
            this->ui->zadej_prikaz_label->setVisible(false);
        }
        this->ui->game_info_list->addItem(QString::fromStdString(event));
    }
}


/**
*\fn void game_window::game_showing()
* Slot který je spušťěn signálem readyRead, když přijdou data ze serveru.
* Obstarává vykreslování a hrací plochy po příchodu aktuálního stavu hry od serveru. 
* Současně se stará o detekci konce hry a jeho obsluhu a o vypisování událostí které během hry nastali.
*/
void game_window::game_showing()
{
    // pole udalosti
    unsigned char events[MAX_EVENTS]={0,};
    int events_count=0;

    // vraci true pokud je konec hry:
    // pokud dojde ke konci hry, tak se tato informace uchová
    // a umožní se tak funkce pro zobrazování informací o hře 
    if (this->client->accept_state_map(events,&events_count))
    {
        // KONEC HRY
        // vypise specificke udalosti
        this->show_happend_events(events,events_count);
        //zobrazi mapu
        this->game_field->set_map(this->client->map);
        QApplication::processEvents();
        // vypise cas hry
        this->ui->game_info_list->addItem(QString::fromStdString(this->client->get_game_time()));
        
        // schova widgety pro zadavani prikazu
        this->ui->send_command_button->setVisible(false);
        this->ui->command_edit->setVisible(false);
        this->ui->zadej_prikaz_label->setVisible(false);
        
        // nastavi tooltipy
        this->assign_tooltips();
        return;
    }
    // pokud neni konec hry
    // vypise specificke udalosti
    this->show_happend_events(events,events_count);

    this->game_field->set_map(this->client->map);
    QApplication::processEvents();
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
         this->ui->game_info_list->addItem(QString::fromStdString(e.get_message()));
    }
    this->ui->command_edit->setText("");
}

