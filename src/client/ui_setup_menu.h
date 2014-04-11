/********************************************************************************
** Form generated from reading UI file 'setup_menu.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUP_MENU_H
#define UI_SETUP_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setup_menu
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Setup_menu)
    {
        if (Setup_menu->objectName().isEmpty())
            Setup_menu->setObjectName(QStringLiteral("Setup_menu"));
        Setup_menu->resize(400, 300);
        centralWidget = new QWidget(Setup_menu);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Setup_menu->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Setup_menu);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 25));
        Setup_menu->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Setup_menu);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Setup_menu->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Setup_menu);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Setup_menu->setStatusBar(statusBar);

        retranslateUi(Setup_menu);

        QMetaObject::connectSlotsByName(Setup_menu);
    } // setupUi

    void retranslateUi(QMainWindow *Setup_menu)
    {
        Setup_menu->setWindowTitle(QApplication::translate("Setup_menu", "Bludiste 2014", 0));
    } // retranslateUi

};

namespace Ui {
    class Setup_menu: public Ui_Setup_menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUP_MENU_H
