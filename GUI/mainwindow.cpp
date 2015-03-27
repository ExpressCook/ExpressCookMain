#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->Task->setTabEnabled(0,false);
    ui->Task_2->setTabEnabled(0,false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clickanywhere_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_realExit_clicked()
{
    MainWindow w;
    w.~MainWindow();
}

void MainWindow::on_apple_clicked()
{
    if (ui->Task->isEnabled())
    {
        if (ui->Task_2->isEnabled())
        {
            // Message Box
        }
        else
        {
            ui->Task_2->setEnabled(true);
            ui->Task_tab_2->setEnabled(true);
            ui->fruit_name_2->setEnabled(true);
            ui->task_choice_2->setEditable(true);
            ui->fruit_num_2->setEnabled(true);
            ui->fruit_name_2->setText("Apple");
        }
    }
    else
    {
        ui->Task->setEnabled(true);
        ui->Task_tab_1->setEnabled(true);
        ui->fruit_name_1->setEnabled(true);
        ui->task_choice_1->setEnabled(true);
        ui->fruit_num_1->setEnabled(true);
        ui->fruit_name_1->setText("Apple");
    }
}

void MainWindow::on_potato_clicked()
{
    if (ui->Task->isEnabled())
    {
        if (ui->Task_2->isEnabled())
        {
            // Message Box
        }
        else
        {
            ui->Task_2->setEnabled(true);
            ui->Task_tab_2->setEnabled(true);
            ui->fruit_name_2->setEnabled(true);
            ui->task_choice_2->setEditable(true);
            ui->fruit_num_2->setEnabled(true);
            ui->fruit_name_2->setText("Potato");
        }
    }
    else
    {
        ui->Task->setEnabled(true);
        ui->Task_tab_1->setEnabled(true);
        ui->fruit_name_1->setEnabled(true);
        ui->task_choice_1->setEnabled(true);
        ui->fruit_num_1->setEnabled(true);
        ui->fruit_name_1->setText("Potato");
    }
}

void MainWindow::on_pushButton_clicked()
{
    int task_num = 0;
    if (ui->Task->isEnabled())
    {
        if (ui->Task_2->isEnabled())
        {
            task_num = 2;
            // Get task 2 info
        }
        task_num = 1;
        // Get task 1 info
    }
    // Send message to CPU

    ui->stackedWidget->setCurrentIndex(2);

    // Switched to progress monitor page
    while (ui->progressBar_1->value()<100)
    {
        ui->progressBar_1->setValue(ui->progressBar_1->value()+1);
        sleep(0.3);
    }

    sleep(1);
    while (ui->progressBar_2->value()<100)
    {
        ui->progressBar_2->setValue(ui->progressBar_2->value()+1);
        sleep(0.3);
    }
}



void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_4_clicked()
{
    MainWindow w;
    w.~MainWindow();
}
