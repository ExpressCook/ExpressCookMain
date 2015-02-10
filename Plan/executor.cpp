#include "executor.h"
#include "toolposition.h"

Executor::Executor()
{
    //initial motor
    motor.init();
    motor.goToOrigin();

    //initial camera
    motor.moveAwayForCamera();
    vision.imgCapture(0);
}

Executor::~Executor()
{
    //finialize motor
    motor.goToOrigin();

    //fianlize vision
}

Executor& Executor::getInstance()
{
    //lazy classical singleton implementation
    //guaratee to be destroyed
    static Executor executor;
    return executor;
}

bool Executor::load(AbstractFood &food)
{
    //make sure the view of camera is not obscured
    motor.moveAwayForCamera();
    //take the picture
    vision.imgCapture(1);

    //compute the number of available fruits
    int num; bool result = false;
    num=vision.compute();
    if(num>0)
    {
        //return the center point value of apple
        CentrePoint point = vision.CalculateCentroid(food.getType());
        //move the gantry to the point
        if(point.x!=-1 || point.y!=-1)
        {
            motor.bMoveTo(point.x,point.y);
            motor.bMoveDownTillHit();

            //register the height of food
            food.height = motor.getRevLPos()
                          + LOADING_RES_H;

            motor.bMoveDownTo(LOADING_CARRY_H);
            result = true;
        }
    }
    return result;
}

bool Executor::unload(AbstractFood &food)
{
    motor.bMoveTo(UNLOAD_X,UNLOAD_Y);
    motor.bMoveDownTo(0);
}

bool Executor::peel(AbstractFood &food)
{
    //approaching the peeler station
    motor.bMoveTo(PEELER_X-10,PEELER_Y-10);

    //loading into peeler
    motor.bMoveDownTo(PEELER_H-food.height);
    motor.rotateWith(PEELER_ROTATION);
    motor.bMoveTo(PEELER_X, PEELER_Y);

    //start peeling
    motor.bMoveDownTo(PEELER_H);

    //unload from peeler
    motor.bMoveTo(PEELER_X-10,PEELER_Y-10);
    motor.rotateWith(0);
}

bool Executor::slice(AbstractFood &food)
{

}



