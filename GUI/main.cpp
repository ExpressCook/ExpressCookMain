#include "mainwindow.h"
#include <QApplication>
#include <motorserial.h>
#include <vision.h>

Vision vision;
MotorSerial motor;

void initialize();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initialize();

    MainWindow w;
    w.showFullScreen();

    return a.exec();
}

void initialize()
{
    motor.init();
    motor.goToOrigin();
    motor.moveAwayForCamera();
    vision.imgCapture(0);

}
