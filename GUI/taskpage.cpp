#include "taskpage.h"
#include "ui_taskpage.h"
#include "mainwindow.h"

taskPage::taskPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ExpressCookTaskPage)
{
    ui->setupUi(this);
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
    CentrePoint point = vision.AppleCentroid();
    //move the gantry to the point
    motor.bMoveTo(point.x, point.y);
    //move down the arm
    motor.bMoveDownTo(500);
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
    CentrePoint point = vision.PotatoCentroid();
    //move the gantry to the point
    motor.bMoveTo(point.x, point.y);
    //move down the arm
    motor.bMoveDownTo(500);
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
