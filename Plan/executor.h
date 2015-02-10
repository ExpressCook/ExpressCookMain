#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <motorserial.h>
#include <vision.h>
#include "abstractfood.h"

class Executor
{

public:
    /*! Implement the singleton pattern
     * \brief getInstance
     * \return
     */
    static Executor& getInstance();

    bool load(AbstractFood &food);
    bool unload(AbstractFood &food);
    bool peel(AbstractFood &food);
    bool slice(AbstractFood &food);

private:
    Executor();
    ~Executor();
    Executor(Executor const&);       // Don't Implement
    void operator=(Executor const&); // Don't implement

    Vision vision;
    MotorSerial motor;
};

#endif // EXECUTOR_H
