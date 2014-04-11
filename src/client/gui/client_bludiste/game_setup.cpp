#include "game_setup.h"
#include "ui_game_setup.h"

game_setup::game_setup(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game_setup)
{
    ui->setupUi(this);
}

game_setup::~game_setup()
{
    delete ui;
}

void game_setup::fullfill_client_reference(Client_gui * client)
{
    this->client=client;
}

void game_setup::get_maps()
{
    try
    {
       this->client->show_maps();
    }
    catch (Errors & e)
    {
        this->ui->when_error_label->setText(QString::fromStdString(e.get_message()));
        return;
    }
    this->ui->maps_list->clear();
    this->insert_lines(this->client->maps,this->ui->maps_list);
}

void game_setup::show_available_games()
{
    try
    {
       this->client->get_games();
    }
    catch (Errors & e)
    {
        this->ui->when_error_label->setText(QString::fromStdString(e.get_message()));
        return;
    }
    this->ui->games_viewer->clear();
    this->insert_lines(this->client->games,this->ui->games_viewer);
}

void game_setup::insert_lines(std::string str,QListWidget * list)
{
    std::deque <std::string> lines;
    std::string line;
    for (unsigned int i=0 ; i<str.size(); i++)
    {
        if (str.at(i)=='\r')
        {
            lines.push_back(line);
            line="";
            i++;
        }
        else
        {
            line+=str.at(i);
        }
    }
    for (unsigned int i=0 ; i<lines.size() ; i++)
       list->addItem(lines[i].c_str());
}



void game_setup::on_refresh_button_clicked()
{
    try
    {
        this->client->get_games();
    }
    catch (Errors & e)
    {
        this->ui->when_error_label->setText(QString::fromStdString(e.get_message()));
        return;
    }
    this->ui->games_viewer->clear();
    this->insert_lines(this->client->games,this->ui->games_viewer);
}



void game_setup::on_connect_game_button_clicked()
{
    int game_selected=-1;
    if (this->ui->games_viewer->currentItem()!=NULL)
    {
        sscanf(this->ui->games_viewer->currentItem()->text().toStdString().c_str(),"%d",&game_selected);
        try
        {
            this->client->join_game(game_selected);
        }
        catch (Errors & e)
        {
            this->ui->when_error_label->setText(QString::fromStdString(e.get_message()));
            return;
        }
        // pripojeni do hry
        this->create_game_window();
    }
    else
    {
        this->ui->when_error_label->setText("Pro připojení do hry musíte vybrat některou z her");
    }
}


void game_setup::on_create_game_button_clicked()
{
    int map_selected=-1;
    double timeout;
    if (this->ui->maps_list->currentItem()!=NULL)
    {
        sscanf(this->ui->maps_list->currentItem()->text().toStdString().c_str(),"%d",&map_selected);
        timeout=this->ui->timeout_edit->value();
        try
        {
            this->client->create_game(timeout,map_selected);
        }
        catch (Errors & e)
        {
             this->ui->when_error_label->setText(QString::fromStdString(e.get_message()));
             return;
        }

        // vytvoreni okna hry
        this->create_game_window();

    }
    else
    {
        this->ui->when_error_label->setText("Pro vytvoření hry musíte vybrat některou z map");
    }
}


void game_setup::create_game_window()
{
    game_window * game_window_w = new game_window;
    game_window_w->show();
    this->close();
    game_window_w->fullfill_client_reference(this->client);
    game_window_w->create_game_field();

}
