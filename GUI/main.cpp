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

    MainWindow w;
    w.showFullScreen();

    return a.exec();
}

void initialize()
{
    motor.init();
    vision.imgCapture(0);
}
