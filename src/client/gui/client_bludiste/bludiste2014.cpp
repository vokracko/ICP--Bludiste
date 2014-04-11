/*
*\file errors.h
* Obsahuje implementaci hlavičky třídy Errors
*\author Michal Veselý (xvesel63)
*/


#include "game_setup.h"
#include "server_connection_window.h"
#include "game_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client_gui client;
    server_connection_window server_connection_w;
    server_connection_w.show();
    server_connection_w.fullfill_client_reference(&client);

/*
    game_setup game_setup_w;
    game_setup_w.show();
*/
    return a.exec();
}
