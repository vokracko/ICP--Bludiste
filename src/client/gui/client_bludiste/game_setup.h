#ifndef GAME_SETUP_H
#define GAME_SETUP_H

#include <QMainWindow>
#include "./../../client_gui.h"
#include <deque>
#include <QListWidget>
#include "./../../errors.h"
#include "game_window.h"

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

    void get_maps();
    void show_available_games();

private slots:
    void on_refresh_button_clicked();

    void on_connect_game_button_clicked();

    void on_create_game_button_clicked();

private:
    Ui::game_setup *ui;

    void insert_lines(std::string str,QListWidget * list);
    void create_game_window();
};

#endif // GAME_SETUP_H