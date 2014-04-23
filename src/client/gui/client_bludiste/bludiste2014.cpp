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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client client;
    server_connection_window server_connection_w(&client);
    server_connection_w.show();


/*
game_window gw;
gw.show();
Client client;
client.width=20;
client.height=20;
static const char pole[20][20]={
    {'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
    {'w','p','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','p','w'},
    {'w','e','w','w','w','w','w','w','e','w','w','w','w','w','e','w','w','w','w','w'},
    {'w','e','e','w','w','w','w','w','e','e','k','e','e','w','e','w','w','w','w','w'},
    {'w','e','e','w','k','e','e','e','e','w','w','w','e','w','e','e','e','e','m','w'},
    {'w','e','w','w','w','w','w','w','e','e','e','e','e','e','w','w','w','w','w','w'},
    {'w','e','w','w','w','w','w','w','e','w','w','w','w','e','w','w','e','e','e','w'},
    {'w','e','e','w','w','w','w','w','e','w','g','e','e','e','e','w','e','w','e','w'},
    {'w','w','e','e','e','e','e','e','e','w','w','w','e','e','e','w','e','w','e','w'},
    {'w','w','e','w','w','w','e','w','w','w','e','e','e','e','e','w','e','w','e','w'},
    {'w','w','e','w','w','w','e','w','w','w','e','w','w','e','w','w','e','w','e','w'},
    {'w','e','e','w','e','e','e','w','e','e','e','w','w','e','e','e','e','w','e','w'},
    {'w','e','w','w','w','w','e','w','e','e','w','w','e','e','w','w','w','w','e','w'},
    {'w','e','w','w','w','w','w','w','e','e','w','w','e','e','w','e','e','e','e','w'},
    {'w','e','w','w','w','w','w','e','e','e','e','e','e','w','w','e','w','w','e','w'},
    {'w','e','e','w','w','w','e','e','e','e','e','e','e','w','w','e','w','e','e','w'},
    {'w','w','e','w','w','w','k','w','w','e','w','w','w','w','w','k','w','e','e','w'},
    {'w','w','e','w','w','w','w','w','w','e','w','w','w','w','w','w','w','w','e','w'},
    {'w','p','e','e','e','e','e','e','e','e','e','e','w','w','e','e','e','e','p','w'},
    {'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'}
};
for (int i=0;i<20;i++)
    for (int j=0;j<20;j++) client.map[i][j]=pole[i][j];

gw.fullfill_client_reference(&client);
gw.create_game_field();
gw.print_map();
*/
    return a.exec();
}
