/**
*\file server_connection_window.cpp
*Implementuje funkce třídy server_connection_window. <br/>
*Obsahuje funkci pro navázání reference na třídu Client a slot reagující na signál vygenerováný kliknutím na tlačítko připojit.
*\author Michal Veselý (xvesel63)
*/


#include "server_connection_window.h"
#include "ui_server_connection_window.h"
#include "./../../errors.h"

server_connection_window::server_connection_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::server_connection_window)
{
    ui->setupUi(this);
}

server_connection_window::~server_connection_window()
{
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
        game_setup *game_setup_w = new game_setup;
        game_setup_w->show();
        this->close();
        game_setup_w->fullfill_client_reference(this->client);
        game_setup_w->get_maps();
        game_setup_w->show_available_games();
    }
}

/**
*\fn void server_connection_window::fullfill_client_reference(Client * client)
* Provádí navázání reference na třídu Client, která obsahuje veškeré informace o hráči a funkce pro práci s komunikací se serverem.
*/
void server_connection_window::fullfill_client_reference(Client * client)
{
	this->client=client;
}
