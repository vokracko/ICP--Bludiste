/**
*\file game_setup.cpp

* Implementuje metody třídy game_setup. Vygenerované pomocí QT Creator a přidáním implementace metod. <br/>
*Umožňuje připojení se do existující hry a vytvoření nové hry. Po vytvoření či připojení vytváří
* instanci třídy game_window pro samotné hraní hry.
*\author Michal Veselý (xvesel63)
*/

#include "game_setup.h"


game_setup::game_setup(Client * client,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::game_setup)
{
    ui->setupUi(this);
    this->client=client;
    this->game_window_w=NULL;

}

game_setup::~game_setup()
{
    delete ui;
    if (game_window_w!=NULL)
        delete game_window_w;
}


/**
*\fn void game_setup::get_maps()
* Volání metody show_maps() třídy Client, pro získání map k dispozici od serveru a jejich zobrazení do listu umístěném v okně
* metodou insert_lines.<br/>
* V případě chyby je vyvolána výjimka a vypsána chyba (nedojde k ukončení programu).
*/
void game_setup::get_maps()
{
    try
    {
       this->client->show_maps();
    }
    catch (Errors & e)
    {
        this->ui->when_error_label->setText(QString::fromStdString(e.what()));
        return;
    }
    this->ui->maps_list->clear();
    this->insert_lines(this->client->maps,this->ui->maps_list);
}

/**
*\fn void game_setup::show_available_games()
* Zavolá funkci get_games() třídy Client a zobrazí všechny rozehrané hry v okně.
* V případě chyby je vyvolána výjimka a vypsána chyba (nedojde k ukončení programu).
*/
void game_setup::show_available_games()
{
    try
    {
       this->client->get_games();
    }
    catch (Errors & e)
    {
        this->ui->when_error_label->setText(QString::fromStdString(e.what()));
        return;
    }
    this->ui->games_viewer->clear();
    this->insert_lines(this->client->games,this->ui->games_viewer);
}


/**
*\fn void game_setup::insert_lines(std::string str,QListWidget * list)
* Naparsuje textový řetězec str a zobrazí jednotlivé položky do komponenty instance třídy QListWidget.
* \param str Textový řetězec obsahující informace oddělené novým řádkem.
* \param list Odkaz na instanci třídy QListWidget jenž umožňuje výběr konkrétní položky.
*/
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


/**
*\fn void game_setup::on_refresh_button_clicked()
* Slot reagující na signál vyvolaný kliknutím na tlačítko aktualizovat. Vyvolá metodu get_games a dojde k zobrazení aktuálně rozehraných her.
*/
void game_setup::on_refresh_button_clicked()
{
    try
    {
        this->client->get_games();
    }
    catch (Errors & e)
    {
        this->ui->when_error_label->setText(QString::fromStdString(e.what()));
        return;
    }
    this->ui->games_viewer->clear();
    this->insert_lines(this->client->games,this->ui->games_viewer);
}


/**
*\fn void game_setup::on_connect_game_button_clicked()
* Slot reagující na signál vyvolaný kliknutím na tlačítko pro připojení ke hře. <br/>
* Dojde k odeslání vybrané hry serveru s žádostí o připojení se ke hře. V případě neúspěchu je vypsáno chybové hlášení a dojde k vyvolání výjimky.
* (Běh programu se neukončí).<br/>
* V případě úspěchu se vytvoří hrací okno.
*/
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
            this->ui->when_error_label->setText(QString::fromStdString(e.what()));
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

/**
*\fn void game_setup::on_create_game_button_clicked()
* Slot reagující na signál vyvolaný kliknutím na tlačítko pro vytvoření hry. <br/>
* Dojde k odeslání vybrané mapy serveru s žádostí o vytvoření hry. V případě neúspěchu je vypsáno chybové hlášení a dojde k vyvolání výjimky.
* (Běh programu se neukončí). <br/>
* V případě úspěchu se vytvoří hrací okno.
*/
void game_setup::on_create_game_button_clicked()
{
    int map_selected=-1;
    double timeout;
    if (this->ui->maps_list->currentItem()!=NULL)
    {
        sscanf(this->ui->maps_list->currentItem()->text().toStdString().c_str(),"%d",&map_selected);
        timeout=this->ui->timeout_edit->value();
        //std::cout<<timeout<<"  x  "<<map_selected<<std::endl;
        try
        {
            this->client->create_game(timeout,map_selected);
        }
        catch (Errors & e)
        {
             this->ui->when_error_label->setText(QString::fromStdString(e.what()));
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

/**
*\fn void game_setup::create_game_window()
* Vyvolá vytvoření hracího okna a naplnění reference na třídu Client.
*/
void game_setup::create_game_window()
{
    game_window_w = new game_window(this->client);
    game_window_w->show();
    this->hide();
    game_window_w->create_game_field();
    //game_window_w->print_map();

}
