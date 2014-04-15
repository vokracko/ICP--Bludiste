/**
*\file game_window.h
* Hlavičkový soubor definující třídu game_window. Vygenerováno pomocí QT Creator s rozšířením o některé atributy a metody.<br/>
* Je implementací okna ve kterém dochází k hraní hry. Importuje si třídu Game_field, která obsahuje matici hracího pole. 
*\author Michal Veselý (xvesel63)
*/


#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H


#include <QMainWindow>
#include "./../../client.h"
#include "game_window.h"
#include "game_field.h"

namespace Ui {
class game_window;
}

/**
\class game_window
* Třída dědící od třídy QMainWindow. Obsahuje odkaz na třídu Client, obsahující informace o hráři a implementaci metod pro komunikaci se serverem.
*/


class game_window : public QMainWindow
{
    Q_OBJECT
    Client * client;

public:
    explicit game_window(QWidget *parent = 0);
    ~game_window();

    void fullfill_client_reference(Client * client);
    void create_game_field();
    void print_map();
    
private slots:
    void on_send_command_button_clicked();

private:
    Ui::game_window *ui;
};

#endif // GAME_WINDOW_H

