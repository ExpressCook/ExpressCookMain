#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unistd.h>
#include <job.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->Task->setTabEnabled(0,false);
    ui->Task_2->setTabEnabled(0,false);
    ui->progressBar_1->setVisible(false);
    ui->progressBar_2->setVisible(false);

    //set up job manager
    jobManager.linkProgressBar(ui->progressBar_1,ui->progressBar_2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clickanywhere_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->Task->setEnabled(false);
    ui->Task_tab_1->setEnabled(false);
    ui->fruit_name_1->setEnabled(false);
    ui->task_choice_1->setEnabled(false);
    ui->fruit_num_1->setEnabled(false);
    ui->fruit_name_1->setText("Fruit");
    ui->delete_task1->setEnabled(false);

    ui->Task_2->setEnabled(false);
    ui->Task_tab_2->setEnabled(false);
    ui->fruit_name_2->setEnabled(false);
    ui->task_choice_2->setEnabled(false);
    ui->fruit_num_2->setEnabled(false);
    ui->fruit_name_2->setText("Fruit");
    ui->delete_task2->setEnabled(false);
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
            ui->task_choice_2->setEnabled(true);
            ui->fruit_num_2->setEnabled(true);
            ui->fruit_name_2->setText("Apple");
            ui->delete_task2->setEnabled(true);
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
        ui->delete_task1->setEnabled(true);
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
            ui->task_choice_2->setEnabled(true);
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
    if (ui->Task->isEnabled())
    {
        // create the job1
        jobManager.setJob1(Job::CreateJob(ui->fruit_num_1->value(),
                                       ui->fruit_name_1->text(),
                                       ui->task_choice_1->currentText()));
        ui->progressBar_1->setVisible(true);
        ui->progress_1_label->setText(ui->fruit_name_1->text());
        if (ui->Task_2->isEnabled())
        {
            // create the job2
            jobManager.setJob2(Job::CreateJob(ui->fruit_num_2->value(),
                                           ui->fruit_name_2->text(),
                                           ui->task_choice_2->currentText()));
            ui->progressBar_2->setVisible(true);
            ui->progress_2_label->setText(ui->fruit_name_2->text());
        }
    }

    // Switched to progress monitor page
    ui->stackedWidget->setCurrentIndex(2);
    ui->pushButton_3->setEnabled(false);
    // Send message to CPU
    jobManager.executeAll();
    ui->pushButton_3->setEnabled(true);
}



void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_2_clicked()
{
    jobManager.clearJobs();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_4_clicked()
{
    MainWindow w;
    w.~MainWindow();
}

void MainWindow::on_delete_task1_clicked()
{
    ui->Task->setEnabled(false);
    ui->Task_tab_1->setEnabled(false);
    ui->fruit_name_1->setEnabled(false);
    ui->task_choice_1->setEnabled(false);
    ui->fruit_num_1->setEnabled(false);
    ui->fruit_name_1->setText("Fruit");
    ui->delete_task1->setEnabled(false);
}

void MainWindow::on_delete_task2_clicked()
{
    ui->Task->setEnabled(false);
    ui->Task_tab_2->setEnabled(false);
    ui->fruit_name_2->setEnabled(false);
    ui->task_choice_2->setEnabled(false);
    ui->fruit_num_2->setEnabled(false);
    ui->fruit_name_2->setText("Fruit");
    ui->delete_task2->setEnabled(false);
}
