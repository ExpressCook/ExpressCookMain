#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "taskpage.h"
#include <motorserial.h>
#include <vision.h>

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
      void openTaskPage();

private slots:
    void on_clickanywhere_clicked();

private:
    Ui::MainWindow *ui;
    taskPage *mMyTaskPage;

};

extern Vision vision;
extern MotorSerial motor;

#endif // MAINWINDOW_H
