#ifndef JOB_H
#define JOB_H
#include<vector>
#include<abstractfood.h>

using namespace std;

class Job
{
public:
    Job(int num, int type, bool doPeel, bool doSlice);
    static Job* CreateJob(int num, const QString &type, const QString &ops);

    int numFruit;
    bool doPeel;
    bool doSlice;
    vector<AbstractFood*> fruits;

    int getTotalSteps();
};

#endif // JOB_H
