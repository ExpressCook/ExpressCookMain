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

void taskPage::on_apple_clicked()
{
    //make sure the view of camera is not obscured
    motor.moveAwayForCamera();
    //take the picture
    vision.imgCapture(1);
    //compute the number of available fruits
    int num;
    num=vision.compute();
    cout<<"Number is"<<num<<endl;
    if(num==0)
    {
        cout<<"Pantry out of stock."<<endl;
    }
    // continue to do the rest if atleast 1 fruit is found
    if(num>0)
    {
        //return the center point value of apple
        CentrePoint point = vision.CalculateCentroid(1);
        //move the gantry to the point
        if(point.x==-1 && point.y==-1)
        {
            cout<<"Fruit requested out of stock"<<endl;
        }
        else
        {            
            int x = round(point.x);
            int y = round(point.y);

            motor.bMoveTo(x, y);
            //move down the arm
            motor.bMoveDownTo(800);
            usleep(5000000);
            //move up the arm
            motor.bMoveDownTo(100);
        }

    }
}

void taskPage::on_potato_clicked()
{
    //make sure the view of camera is not obscured
    motor.moveAwayForCamera();
    //take the picture
    vision.imgCapture(1);
    //compute the number of available fruits
    int num=vision.compute();
    cout<<"Number is"<<num<<endl;
    if(num==0)
    {
        cout<<"Pantry out of stock."<<endl;
    }
    // continue to do the rest if atleast 1 fruit is found
    if(num>0)
    {
        //return the center point value of apple
        CentrePoint point = vision.CalculateCentroid(0);
        if(point.x==-1 && point.y==-1)
        {
            cout<<"Requested fruit out of stock"<<endl;
        }
        else
        {
            //move the gantry to the point
            int x = round(point.x);
            int y = round(point.y);
            motor.bMoveTo(x,y);
            //move down the arm
            motor.bMoveDownTo(800);
            usleep(5000000);
            //move up the arm
            motor.bMoveDownTo(100);
        }

    }

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


