#include "mainwindow.h"
#include <QApplication>

void initialize();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
    //StackedWidget w;
    w.showFullScreen();
    return a.exec();
}
