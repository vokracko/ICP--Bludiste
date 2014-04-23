/********************************************************************************
** Form generated from reading UI file 'game_setup.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_SETUP_H
#define UI_GAME_SETUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_game_setup
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *connect_game_button;
    QLabel *label_2;
    QPushButton *create_game_button;
    QPushButton *refresh_button;
    QListWidget *games_viewer;
    QListWidget *maps_list;
    QLabel *when_error_label;
    QLabel *label_3;
    QDoubleSpinBox *timeout_edit;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *game_setup)
    {
        if (game_setup->objectName().isEmpty())
            game_setup->setObjectName(QStringLiteral("game_setup"));
        game_setup->resize(507, 672);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(18, 18, 18, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(68, 255, 65, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush3(QColor(255, 32, 35, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush3);
        QBrush brush4(QColor(29, 29, 29, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush5(QColor(0, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush5);
        QBrush brush6(QColor(0, 85, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        QBrush brush7(QColor(255, 255, 0, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush7);
        QBrush brush8(QColor(159, 158, 158, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush8);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush7);
        game_setup->setPalette(palette);
        centralWidget = new QWidget(game_setup);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(170, 40, 161, 21));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        connect_game_button = new QPushButton(centralWidget);
        connect_game_button->setObjectName(QStringLiteral("connect_game_button"));
        connect_game_button->setGeometry(QRect(10, 320, 161, 27));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Button, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush);
        connect_game_button->setPalette(palette1);
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        connect_game_button->setFont(font1);
        connect_game_button->setAutoFillBackground(false);
        connect_game_button->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255)"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(140, 350, 241, 31));
        label_2->setFont(font);
        create_game_button = new QPushButton(centralWidget);
        create_game_button->setObjectName(QStringLiteral("create_game_button"));
        create_game_button->setGeometry(QRect(10, 590, 161, 27));
        create_game_button->setFont(font1);
        refresh_button = new QPushButton(centralWidget);
        refresh_button->setObjectName(QStringLiteral("refresh_button"));
        refresh_button->setGeometry(QRect(290, 320, 201, 27));
        games_viewer = new QListWidget(centralWidget);
        games_viewer->setObjectName(QStringLiteral("games_viewer"));
        games_viewer->setGeometry(QRect(10, 70, 481, 241));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush8);
        games_viewer->setPalette(palette2);
        maps_list = new QListWidget(centralWidget);
        maps_list->setObjectName(QStringLiteral("maps_list"));
        maps_list->setGeometry(QRect(10, 380, 481, 161));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush8);
        maps_list->setPalette(palette3);
        when_error_label = new QLabel(centralWidget);
        when_error_label->setObjectName(QStringLiteral("when_error_label"));
        when_error_label->setGeometry(QRect(10, 10, 481, 20));
        QFont font2;
        font2.setPointSize(13);
        font2.setBold(true);
        font2.setWeight(75);
        when_error_label->setFont(font2);
        when_error_label->setStyleSheet(QStringLiteral("color: red"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 560, 281, 17));
        QFont font3;
        font3.setPointSize(13);
        label_3->setFont(font3);
        timeout_edit = new QDoubleSpinBox(centralWidget);
        timeout_edit->setObjectName(QStringLiteral("timeout_edit"));
        timeout_edit->setGeometry(QRect(300, 556, 62, 24));
        timeout_edit->setFont(font2);
        timeout_edit->setStyleSheet(QStringLiteral("color: black"));
        timeout_edit->setMinimum(0.5);
        timeout_edit->setMaximum(5);
        timeout_edit->setSingleStep(0.5);
        timeout_edit->setValue(2);
        game_setup->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(game_setup);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 507, 25));
        game_setup->setMenuBar(menuBar);

        retranslateUi(game_setup);

        QMetaObject::connectSlotsByName(game_setup);
    } // setupUi

    void retranslateUi(QMainWindow *game_setup)
    {
        game_setup->setWindowTitle(QApplication::translate("game_setup", "Bludi\305\241t\304\233 2014", 0));
        label->setText(QApplication::translate("game_setup", "Hry k dispozici", 0));
        connect_game_button->setText(QApplication::translate("game_setup", "p\305\231ipojit se do hry", 0));
        label_2->setText(QApplication::translate("game_setup", "Vytvo\305\231en\303\255 nov\303\251 hry", 0));
        create_game_button->setText(QApplication::translate("game_setup", "vytvo\305\231it hru", 0));
        refresh_button->setText(QApplication::translate("game_setup", "aktualizovat rozehran\303\251 hry", 0));
        when_error_label->setText(QString());
        label_3->setText(QApplication::translate("game_setup", "Zvol si timeout v rozmez\303\255 0.5 - 5 sec", 0));
    } // retranslateUi

};

namespace Ui {
    class game_setup: public Ui_game_setup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_SETUP_H
