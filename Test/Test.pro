#-------------------------------------------------
#
# Project created by QtCreator 2014-11-21T16:50:58
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
    target.files = Test/Test
    target.path = /home/ubuntu/qt

INSTALLS += target

SOURCES += main.cpp

#add motor library
unix:!macx: LIBS += -L$$OUT_PWD/../Motor/ -lMotor

INCLUDEPATH += $$PWD/../Motor
DEPENDPATH += $$PWD/../Motor

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../Motor/libMotor.a

#add vision library
unix:!macx: LIBS += -L$$OUT_PWD/../Vision/ -lVision

INCLUDEPATH += $$PWD/../Vision
DEPENDPATH += $$PWD/../Vision

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../Vision/libVision.a

#opencv again!
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_core
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_highgui
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_imgproc

INCLUDEPATH += $$PWD/../opencv/include
DEPENDPATH += $$PWD/../opencv/include
