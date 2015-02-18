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

    target.files = Test
    target.path = /usr/lib



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

#add plan library
unix:!macx: LIBS += -L$$OUT_PWD/../Plan/ -lPlan

INCLUDEPATH += $$PWD/../Plan
DEPENDPATH += $$PWD/../Plan

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../Plan/libPlan.a

#opencv again!
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_core
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_highgui
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_imgproc
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_calib3d
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_flann
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_features2d

INCLUDEPATH += $$PWD/../opencv/include
DEPENDPATH += $$PWD/../opencv/include

