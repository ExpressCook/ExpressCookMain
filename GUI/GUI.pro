#-------------------------------------------------
#
# Project created by QtCreator 2014-11-20T11:04:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app
    target.files = GUI/GUI
    target.path = /home/ubuntu/qt

INSTALLS += target

SOURCES += main.cpp\
        mainwindow.cpp \
    taskpage.cpp

HEADERS  += mainwindow.h \
    taskpage.h

FORMS    += mainwindow.ui \
    taskpage.ui

RESOURCES += \
    test.qrc
    test.qrc \
