/**
*\file server_connection_window.cpp
*Implementuje funkce třídy server_connection_window. <br/>
*Obsahuje funkci pro navázání reference na třídu Client a slot reagující na signál vygenerováný kliknutím na tlačítko připojit.
*\author Michal Veselý (xvesel63)
*/


#include "server_connection_window.h"


server_connection_window::server_connection_window(Client * client,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::server_connection_window)
{
    ui->setupUi(this);
    this->client=client;
    this->game_setup_w=NULL;
}

server_connection_window::~server_connection_window()
{
    if (game_setup_w!=NULL) delete game_setup_w;
    delete ui;
}

/**
*\fn void server_connection_window::on_server_connect_button_clicked()
*Funkce reagující na signál vyvolaný kliknutím na tlačítko připojit. <br/>
*Dojde k pokusu o připojení k serveru v okně pro zadání adresy serveru. Pokud se k serveru nepodaří připojit, vygeneruje se výjimka která se projeví
* vypsáním chybové hlášky. Program umožňuje nové zadání adresy serveru (vyvoláním výjimky nedojde k ukončení programu).
*/
void server_connection_window::on_server_connect_button_clicked()
{
    int ec=0;
    try
    {
        ec=this->client->connect_socket(this->ui->server_name_edit->text().toStdString().c_str());
    }
    catch (Errors & e)
	{
        this->ui->when_error_label->setText(QString::fromStdString(e.get_message()));
	}
    if (ec)
    {
        game_setup_w = new game_setup(client);
        game_setup_w->show();
        this->hide();
        game_setup_w->get_maps();
        game_setup_w->show_available_games();
    }
}

