#ifndef SERVER_CONNECTION_WINDOW_H
#define SERVER_CONNECTION_WINDOW_H

#include <QMainWindow>
#include "./../../client_gui.h"

namespace Ui {
class server_connection_window;
}

class server_connection_window : public QMainWindow
{
    Q_OBJECT
    
    Client_gui * client;

public:
    explicit server_connection_window(QWidget *parent = 0);
    ~server_connection_window();
    void fullfill_client_reference(Client_gui * client);
    
private slots:
    void on_server_connect_button_clicked();

private:
    Ui::server_connection_window *ui;
};

#endif // SERVER_CONNECTION_WINDOW_H
