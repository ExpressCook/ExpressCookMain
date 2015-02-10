#-------------------------------------------------
#
# Project created by QtCreator 2015-01-26T13:49:47
#
#-------------------------------------------------

QT       -= gui

TARGET = Vision
TEMPLATE = lib
CONFIG += staticlib

SOURCES += vision.cpp \
    visioninitialization.cpp \
    visionImproved.cpp

HEADERS += vision.h \
    visioninitialization.h \
    visionImproved.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_core
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_highgui
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_imgproc
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_calib3d
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_flann
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_features2d

INCLUDEPATH += $$PWD/../opencv/include
DEPENDPATH += $$PWD/../opencv/include
