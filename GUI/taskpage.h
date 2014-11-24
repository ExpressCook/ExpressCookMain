#ifndef TASKPAGE_H
#define TASKPAGE_H

#include <QMainWindow>
#include <motorserial.h>
#include <vision.h>

namespace Ui {
class ExpressCookTaskPage;
}

class taskPage : public QMainWindow
{
    Q_OBJECT
public:
    explicit taskPage(QWidget *parent = 0);

signals:

public slots:

private slots:
    void on_apple_clicked();

    void on_potato_clicked();

    void on_Exit_clicked();

    void on_realExit_clicked();

private:
    Ui::ExpressCookTaskPage *ui;
    void checkRange(CentrePoint &point);
};

extern Vision vision;
extern MotorSerial motor;

#endif // TASKPAGE_H
