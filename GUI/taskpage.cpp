#include "taskpage.h"
#include "ui_taskpage.h"
#include "mainwindow.h"
#include <unistd.h>

taskPage::taskPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExpressCookTaskPage)
{
    ui->setupUi(this);
}

void taskPage::checkRange(CentrePoint &center)
{
    if(center.x<0)
        center.x=0;

    if(center.x>1700)
        center.x=1700;

    if(center.y<0)
        center.y = 0;

    if(center.y>720)
        center.y=720;
}

void taskPage::on_apple_clicked()
{
    //make sure the view of camera is not obscured
    motor.moveAwayForCamera();
    //take the picture
    vision.imgCapture(1);
    //compute
    vision.compute();
    //return the center point value of apple
    CentrePoint point = vision.CalculateCentroid(1);
    //move the gantry to the point
    checkRange(point);
    int x = round(point.x);
    int y = round(point.y);

    motor.bMoveTo(x, y);
    //move down the arm
    motor.bMoveDownTo(800);
    usleep(5000000);
    //move up the arm
    motor.bMoveDownTo(100);
}

void taskPage::on_potato_clicked()
{
    //make sure the view of camera is not obscured
    motor.moveAwayForCamera();
    //take the picture
    vision.imgCapture(1);
    //compute
    vision.compute();
    //return the center point value of apple
    CentrePoint point = vision.CalculateCentroid(0);
    //move the gantry to the point
    checkRange(point);
    int x = round(point.x);
    int y = round(point.y);
    motor.bMoveTo(x, y);
    //move down the arm
    motor.bMoveDownTo(800);
    usleep(5000000);
    //move up the arm
    motor.bMoveDownTo(100);
}

void taskPage::on_Exit_clicked()
{
    //move the arm to origin
    motor.goToOrigin();

    MainWindow *home = new MainWindow();
    home->showFullScreen();
    this->destroy();
}

void taskPage::on_realExit_clicked()
{
    this->destroy();
}


