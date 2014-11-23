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

unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_core
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_highgui
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_imgproc

INCLUDEPATH += $$PWD/../opencv/include
DEPENDPATH += $$PWD/../opencv/include
