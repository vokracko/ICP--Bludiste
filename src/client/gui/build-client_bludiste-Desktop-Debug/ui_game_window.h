/********************************************************************************
** Form generated from reading UI file 'game_window.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_WINDOW_H
#define UI_GAME_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game_window
{
public:
    QWidget *centralwidget;
    QLineEdit *command_edit;
    QLabel *zadej_prikaz_label;
    QLabel *when_error_label;
    QPushButton *send_command_button;
    QWidget *gridLayoutWidget;
    QGridLayout *grid;
    QMenuBar *menubar;

    void setupUi(QMainWindow *game_window)
    {
        if (game_window->objectName().isEmpty())
            game_window->setObjectName(QStringLiteral("game_window"));
        game_window->setWindowModality(Qt::NonModal);
        game_window->setEnabled(true);
        game_window->resize(647, 515);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush2(QColor(159, 158, 158, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        game_window->setPalette(palette);
        centralwidget = new QWidget(game_window);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        command_edit = new QLineEdit(centralwidget);
        command_edit->setObjectName(QStringLiteral("command_edit"));
        command_edit->setGeometry(QRect(140, 30, 131, 27));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        font.setWeight(75);
        command_edit->setFont(font);
        command_edit->setStyleSheet(QStringLiteral("color:blue"));
        zadej_prikaz_label = new QLabel(centralwidget);
        zadej_prikaz_label->setObjectName(QStringLiteral("zadej_prikaz_label"));
        zadej_prikaz_label->setGeometry(QRect(10, 30, 111, 21));
        zadej_prikaz_label->setFont(font);
        zadej_prikaz_label->setStyleSheet(QStringLiteral("color: white"));
        when_error_label = new QLabel(centralwidget);
        when_error_label->setObjectName(QStringLiteral("when_error_label"));
        when_error_label->setGeometry(QRect(10, 10, 511, 17));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(true);
        font1.setWeight(75);
        when_error_label->setFont(font1);
        when_error_label->setStyleSheet(QLatin1String("color:red\n"
""));
        send_command_button = new QPushButton(centralwidget);
        send_command_button->setObjectName(QStringLiteral("send_command_button"));
        send_command_button->setGeometry(QRect(320, 30, 99, 27));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 70, 91, 111));
        grid = new QGridLayout(gridLayoutWidget);
        grid->setSpacing(0);
        grid->setObjectName(QStringLiteral("grid"));
        grid->setSizeConstraint(QLayout::SetMinAndMaxSize);
        grid->setContentsMargins(0, 0, 0, 0);
        game_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(game_window);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 647, 25));
        game_window->setMenuBar(menubar);

        retranslateUi(game_window);

        QMetaObject::connectSlotsByName(game_window);
    } // setupUi

    void retranslateUi(QMainWindow *game_window)
    {
        game_window->setWindowTitle(QApplication::translate("game_window", "Bludi\305\241t\304\233 2014", 0));
        zadej_prikaz_label->setText(QApplication::translate("game_window", "Zadej p\305\231\303\255kaz:", 0));
        when_error_label->setText(QString());
        send_command_button->setText(QApplication::translate("game_window", "prov\303\251st", 0));
    } // retranslateUi

};

namespace Ui {
    class game_window: public Ui_game_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_WINDOW_H
