#-------------------------------------------------
#
# Project created by QtCreator 2014-04-07T12:13:58
#
#-------------------------------------------------

QT       += core gui
QT+=network

QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET  = bludiste2014


TEMPLATE = app


SOURCES +=\
        game_setup.cpp \
    bludiste2014.cpp \
    server_connection_window.cpp

SOURCES+=
./../../bludiste2014-cli.cpp
SOURCES+=./../../client.cpp
SOURCES+=./../../client_gui.cpp
SOURCES+=./../../errors.cpp


HEADERS  += game_setup.h \
    server_connection_window.h
HEADER  +=./../../errors.h
HEADER  +=./../../client.h
HEADER  +=./../../client_gui.h

FORMS    += game_setup.ui \
    server_connection_window.ui
