#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "taskpage.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->clickanywhere, SIGNAL(click()), this, SLOT(openTaskPage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clickanywhere_clicked()
{
    this->destroy();
    mMyTaskPage = new taskPage();
    mMyTaskPage->showFullScreen();

}

void MainWindow::openTaskPage()
{
}

