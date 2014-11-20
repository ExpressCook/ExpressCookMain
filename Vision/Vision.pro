#-------------------------------------------------
#
# Project created by QtCreator 2014-11-20T13:44:32
#
#-------------------------------------------------

QT       -= gui

TARGET = Vision
TEMPLATE = lib
CONFIG += staticlib

SOURCES += vision.cpp

HEADERS += vision.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
