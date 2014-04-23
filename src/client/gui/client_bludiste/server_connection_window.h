/**
*\file server_connection_window.h
*Hlavičkový soubor pro třídu server_connection_window <br/>
*Vygenerován pomocí QT Creator s přidáním některých funkcí<br/> 
*server_connection_window řeší získání adresy serveru, ke které se chce hráč připojit a pokud server existuje tak hráče připojí
*\author Michal Veselý (xvesel63)
*/

#ifndef SERVER_CONNECTION_WINDOW_H
#define SERVER_CONNECTION_WINDOW_H

#include <QMainWindow>
#include "./../../client.h"
#include "game_setup.h"

namespace Ui {
class server_connection_window;
}

/**
\class server_connection_window
* Obsahuje zobrazitelné okno, ve kterém je vyžadována adresa serveru. Dochází ke kontrole zda server existuje (pomocí funkcí třídy Client)
* a v pozitivním případě dojde k připojení k serveru. V případě že server neexistuje dojde k vyvolání vyjímky, okno vypíše chybové hlášení 
*, a hráč má možnost pokusit se připojit znovu (vyvoláním výjimky nedojde k vypnutí programu). <br/><br/>
* Grafické rozhraní okna pro připojení bylo vytvořeno pomocí QT Creatoru a je uloženo v server_connection_window.ui.
*/

class server_connection_window : public QMainWindow
{
    Q_OBJECT
    
    Client * client;
    game_setup *game_setup_w;

public:
    explicit server_connection_window(Client * client,QWidget *parent = 0);
    ~server_connection_window();
    
private slots:
    void on_server_connect_button_clicked();

    //void on_server_connection_window_destroyed();

private:
    Ui::server_connection_window *ui;
};

#endif // SERVER_CONNECTION_WINDOW_H
