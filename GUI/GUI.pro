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

HEADERS  += mainwindow.h \

FORMS    += mainwindow.ui \


RESOURCES += \
    test.qrc
    test.qrc \

#add plan library
unix:!macx: LIBS += -L$$OUT_PWD/../Plan/ -lPlan

INCLUDEPATH += $$PWD/../Plan
DEPENDPATH += $$PWD/../Plan

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../Plan/libPlan.a

#add the motor library
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



