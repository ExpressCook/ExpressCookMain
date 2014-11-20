#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "taskpage.h"

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

#endif // MAINWINDOW_H
