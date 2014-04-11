#include "server_connection_window.h"
#include "ui_server_connection_window.h"
#include "./../../errors.h"
#include "game_setup.h"


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
        //game_setup_w->ui->maps_list->addItem("ap");

    }
}

void server_connection_window::fullfill_client_reference(Client_gui * client)
{
	this->client=client;
}
