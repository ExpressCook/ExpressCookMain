#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<jobmanager.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

private slots:
    void on_clickanywhere_clicked();


    void on_realExit_clicked();

    void on_apple_clicked();

    void on_potato_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_delete_task1_clicked();

    void on_delete_task2_clicked();

    void on_cv_do_detection_clicked();

    void on_cv_button_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    JobManager jobManager;
};

#endif // MAINWINDOW_H
