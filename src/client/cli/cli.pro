#-------------------------------------------------
#
# Project created by QtCreator 2014-04-21T17:42:15
#
#-------------------------------------------------

QT       += core

QT+=network

QT       -= gui

TARGET = bludiste2014-cli
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -pthread

SOURCES += ./../../errors.cpp

SOURCES += main.cpp \
    ./../client.cpp \
    client_cli.cpp


HEADERS +=./../../errors.h
HEADERS += ./../../game_components.h
HEADERS += ./../../events_enumerator.h
HEADERS += \
    ./../client.h \
    client_cli.h
