#-------------------------------------------------
#
# Project created by QtCreator 2014-11-20T11:39:57
#
#-------------------------------------------------

QT       -= gui

TARGET = Motor
TEMPLATE = lib
CONFIG += staticlib

SOURCES += motorserial.cpp \
    serialib.cpp

HEADERS += motorserial.h \
    serialib.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
