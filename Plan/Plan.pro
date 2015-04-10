#-------------------------------------------------
#
# Project created by QtCreator 2015-02-10T15:27:14
#
#-------------------------------------------------

QT       -= gui
QT       += widgets

TARGET = Plan
TEMPLATE = lib
CONFIG += staticlib

SOURCES += executor.cpp \
    abstractfood.cpp \
    apple.cpp \
    potato.cpp \
    job.cpp \
    jobmanager.cpp

HEADERS += executor.h \
    abstractfood.h \
    apple.h \
    potato.h \
    toolposition.h \
    job.h \
    jobmanager.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

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
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_calib3d
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_flann
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_features2d
INCLUDEPATH += $$PWD/../opencv/include
DEPENDPATH += $$PWD/../opencv/include
