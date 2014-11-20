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

}

void taskPage::on_potato_clicked()
{

}

void taskPage::on_Exit_clicked()
{
    MainWindow *home = new MainWindow();
    home->showFullScreen();
    this->destroy();
}

void taskPage::on_realExit_clicked()
{
    this->destroy();
}