#include "jobmanager.h"
#include <executor.h>
#include <qmessagebox.h>

using namespace std;

JobManager::JobManager()
{
    j1 = NULL;j2 = NULL;
}

JobManager::~JobManager()
{
    clearJobs();
}

void JobManager::linkProgressBar(QProgressBar *b1, QProgressBar *b2)
{
    this->b1 = b1;
    this->b2 = b2;
}

void JobManager::linkMainWindow(QWidget *widget)
{
    this->widget = widget;
}

void JobManager::executeAll()
{
    if(this->j1 != NULL)
        executeJob(this->j1,this->b1);
    else
        b1->setValue(b1->maximum());

    if(this->j2 != NULL)
        executeJob(this->j2,this->b2);
    else
        b2->setValue(b2->maximum());
}

void JobManager::executeJob(Job* job, QProgressBar* bar)
{
    cout<<"job started"<<endl;

    bar->setValue(0);
    Executor& exe = Executor::getInstance();
    vector<AbstractFood*> & allFruits = job->fruits;
    for(vector<AbstractFood*>::iterator it = allFruits.begin();
        it != allFruits.end(); ++it)
    {
        AbstractFood* food = *it;
        // load
        cout<<"start loading..."<<endl;
        if(!exe.load(*food))
        {
            cout<<"fail to load!"<<endl;
            QMessageBox::information(widget,"Fail","Fail to load food!");
            continue;
        }
        bar->setValue(bar->value()+1);
        // peel
        if(job->doPeel)
        {
            cout<<"start peeling..."<<endl;
            if(!exe.peel(*food))
            {
                cout<<"fail to peel!"<<endl;
                continue;
            }
            bar->setValue(bar->value()+1);
        }
        // slice
        if(job->doSlice)
        {
            cout<<"start slicing..."<<endl;
            if(!exe.slice(*food))
            {
                cout<<"fail to slice!"<<endl;
                continue;
            }
            bar->setValue(bar->value()+1);
        }
        // unload
        cout<<"start unloading..."<<endl;
        if(!exe.unload(*food))
        {
            cout<<"fail to unload!"<<endl;
            continue;
        }
        bar->setValue(bar->value()+1);
    }
    cout<<"job done..."<<endl;
}

void JobManager::executeJobTest(Job *job, QProgressBar *bar)
{
    cout<<"job started"<<endl;
    bar->setValue(0);
    vector<AbstractFood*> & allFruits = job->fruits;
    for(vector<AbstractFood*>::iterator it = allFruits.begin();
        it != allFruits.end(); ++it)
    {
        AbstractFood* food = *it;
        // load
        cout<<"start loading:"<< food->getName().toStdString() <<endl;
        QThread::sleep(2);
        bar->setValue(bar->value()+1);
        // peel
        if(job->doPeel)
        {
            cout<<"start peeling..."<<endl;
            QThread::sleep(2);
            bar->setValue(bar->value()+1);
        }
        // slice
        if(job->doSlice)
        {
            cout<<"start slicing..."<<endl;
            QThread::sleep(2);
            bar->setValue(bar->value()+1);
        }
        // unload
        cout<<"start unloading..."<<endl;
        QThread::sleep(2);
        bar->setValue(bar->value()+1);
    }
    cout<<"job done..."<<endl;
}

bool JobManager::validateJob(const Job *job)
{
    //use vision to check there is enough food
    return true;
}

void JobManager::clearJobs()
{
    delete j1;
    delete j2;

    j1 = NULL;
    j2 = NULL;

    b1->reset();
    b2->reset();
}



void JobManager::setJob1(Job* job)
{
    this->j1 = job;
    b1->setMinimum(0);
    b1->setMaximum(job->getTotalSteps());
}

void JobManager::setJob2(Job *job)
{
    this->j2 = job;
    b2->setMinimum(0);
    b2->setMaximum(job->getTotalSteps());
}

