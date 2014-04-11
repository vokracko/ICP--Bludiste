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
    this->client->get_games();
    this->ui->games_viewer->clear();
    this->insert_lines(this->client->games,this->ui->games_viewer);
}

void game_setup::on_show_games_button_clicked()
{
    this->client->show_maps();
    this->ui->maps_list->clear();
    this->insert_lines(this->client->maps,this->ui->maps_list);
}
