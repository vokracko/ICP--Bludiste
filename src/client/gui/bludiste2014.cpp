/*
*\file bludiste2014.cpp
* Soubor obsahující funkci main pro verzi hry Bludiště2014 s grafickým rozhraním <br />
* Pouze spouští zobrazení okna vyžadující připojení k hernímu serveru
*\author Michal Veselý (xvesel63)
*/


#include "game_setup.h"
#include "server_connection_window.h"
#include "game_window.h"
#include <QApplication>

/** 
\fn int main(int argc, char *argv[])
\brief Spustí počáteční okno pro zadání herního serveru.
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client client;
    server_connection_window server_connection_w(&client);
    server_connection_w.show();
    
    return a.exec();
}
