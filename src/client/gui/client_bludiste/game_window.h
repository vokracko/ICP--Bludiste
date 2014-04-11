#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H


#include <QMainWindow>
#include "./../../client_gui.h"
#include "game_window.h"

namespace Ui {
class game_window;
}

class game_window : public QMainWindow
{
    Q_OBJECT
    Client_gui * client;
    
public:
    explicit game_window(QWidget *parent = 0);
    ~game_window();

    void fullfill_client_reference(Client_gui * client);
    void create_game_field();
    
private:
    Ui::game_window *ui;
};

#endif // GAME_WINDOW_H
