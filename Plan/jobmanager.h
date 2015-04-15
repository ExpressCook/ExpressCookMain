#ifndef JOBMANAGER_H
#define JOBMANAGER_H
#include <qprogressbar.h>
#include <qwidget.h>
#include <job.h>

class JobManager
{
public:
    JobManager();
    virtual ~JobManager();

    //link progress bar
    void linkProgressBar(QProgressBar* b1,QProgressBar* b2);
    void linkMainWindow(QWidget* widget);

    //execute all the job
    void executeAll();

    //execute a single job
    //need to update the gui
    void executeJob(Job* job, QProgressBar* bar);
    void executeJobTest(Job* job, QProgressBar* bar);

    //is it possible to do
    bool validateJob(const Job* job);

    //clean the j1 and j2
    void clearJobs();

    //set jobs
    void setJob1(Job* job);
    void setJob2(Job* job);

private:
    //jobs
    Job* j1;
    Job* j2;

    //bars
    QProgressBar* b1;
    QProgressBar* b2;

    //main window
    QWidget* widget;
};

#endif // JOBMANAGER_H
