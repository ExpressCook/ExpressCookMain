#include<apple.h>
#include<potato.h>
#include "job.h"
#include "stdio.h"
Job::Job(int num, int type, bool doPeel, bool doSlice)
{
    this->numFruit = num;
    this->doPeel = doPeel;
    this->doSlice = doSlice;

    //fill the list with new apple
    for(int i=0; i<num; i++)
    {
        if(type == 1)
            fruits.push_back(new Apple());
        else if(type == 0)
            fruits.push_back(new Potato());
    }
}

Job* Job::CreateJob(int num, const QString &type, const QString &ops)
{
    int ty = AbstractFood::parseType(type);
    bool doPeel,doSlice;
    if(ops.compare("peel")==0)
    {
        doPeel = true;
        doSlice = false;
    }
    else if(ops.compare("slice")==0)
    {
        doPeel = false;
        doSlice = true;
    }
    else if(ops.compare("peel+slice")==0)
    {
        doPeel = true;
        doSlice = true;
    }

    return new Job(num,ty,doPeel,doSlice);
}

int Job::getTotalSteps()
{
    int steps = 0;
    if(doPeel && doSlice)
        steps = 4*numFruit;
    else if(doPeel)
        steps = 3*numFruit;
    else if(doSlice)
        steps = 3*numFruit;

    return steps;
}

