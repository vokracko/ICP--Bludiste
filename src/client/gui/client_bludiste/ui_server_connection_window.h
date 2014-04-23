/********************************************************************************
** Form generated from reading UI file 'server_connection_window.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVER_CONNECTION_WINDOW_H
#define UI_SERVER_CONNECTION_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_server_connection_window
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLineEdit *server_name_edit;
    QPushButton *server_connect_button;
    QLabel *when_error_label;
    QMenuBar *menubar;

    void setupUi(QMainWindow *server_connection_window)
    {
        if (server_connection_window->objectName().isEmpty())
            server_connection_window->setObjectName(QStringLiteral("server_connection_window"));
        server_connection_window->resize(438, 157);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        QBrush brush2(QColor(159, 158, 158, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        server_connection_window->setPalette(palette);
        centralwidget = new QWidget(server_connection_window);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 421, 21));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        server_name_edit = new QLineEdit(centralwidget);
        server_name_edit->setObjectName(QStringLiteral("server_name_edit"));
        server_name_edit->setGeometry(QRect(20, 40, 301, 27));
        server_connect_button = new QPushButton(centralwidget);
        server_connect_button->setObjectName(QStringLiteral("server_connect_button"));
        server_connect_button->setGeometry(QRect(330, 40, 99, 27));
        when_error_label = new QLabel(centralwidget);
        when_error_label->setObjectName(QStringLiteral("when_error_label"));
        when_error_label->setGeometry(QRect(20, 80, 401, 17));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        when_error_label->setFont(font1);
        when_error_label->setStyleSheet(QStringLiteral("color:red"));
        server_connection_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(server_connection_window);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 438, 25));
        server_connection_window->setMenuBar(menubar);

        retranslateUi(server_connection_window);

        QMetaObject::connectSlotsByName(server_connection_window);
    } // setupUi

    void retranslateUi(QMainWindow *server_connection_window)
    {
        server_connection_window->setWindowTitle(QApplication::translate("server_connection_window", "Bludi\305\241t\304\233 2014 - p\305\231ipojen\303\255 k serveru", 0));
        label->setText(QApplication::translate("server_connection_window", "Zadejte server, ke kter\303\251mu se chcete p\305\231ipojit", 0));
        server_name_edit->setText(QApplication::translate("server_connection_window", "localhost", 0));
        server_connect_button->setText(QApplication::translate("server_connection_window", "p\305\231ipojit se", 0));
        when_error_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class server_connection_window: public Ui_server_connection_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVER_CONNECTION_WINDOW_H
