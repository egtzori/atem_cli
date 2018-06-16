#-------------------------------------------------
#
# Project created by QtCreator 2018-06-16T14:23:14
#
#-------------------------------------------------

QT       += core

QT       += gui
QT       += network

TARGET = atem_cli
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

LIBS += -lqatemcontrol

HEADERS += \
    App.h

