#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include <QMainWindow>
#include "./../../client_gui.h"
#include <deque>
#include <QListWidget>

namespace Ui {
class game_setup;
}

class game_setup : public QMainWindow
{
    Q_OBJECT
    Client_gui * client;
public:
    explicit game_setup(QWidget *parent = 0);
    ~game_setup();

    void fullfill_client_reference(Client_gui * client);
    
private slots:
    void on_refresh_button_clicked();

    void on_show_games_button_clicked();

private:
    Ui::game_setup *ui;

    void insert_lines(std::string str,QListWidget * list);
};

#endif // GAME_SETUP_H
