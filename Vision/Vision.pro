#-------------------------------------------------
#
# Project created by QtCreator 2014-11-20T13:44:32
#
#-------------------------------------------------

QT       -= gui

TARGET = Vision
TEMPLATE = lib
CONFIG += staticlib

SOURCES += vision.cpp \
           color_constancy.cpp

HEADERS += vision.h  \
    color_constancy.hpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#opencv again!
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_core
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_highgui
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_imgproc
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_calib3d
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_flann
unix:!macx: LIBS += -L$$PWD/../opencv/lib/ -lopencv_features2d

INCLUDEPATH += $$PWD/../opencv/include
DEPENDPATH += $$PWD/../opencv/include
