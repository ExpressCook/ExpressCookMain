/*
 * Implemnet the core functionalities and execution sequences
 * Funcitons implemented includes: load, unload, peel, slice
 */

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

    return true;
}

bool Executor::peel(AbstractFood &food)
{
    //approaching the peeler station
    motor.bMoveYTo(PEELER_Y+200);
    motor.bMoveXTo(PEELER_X);

    //loading into peeler
    motor.bMoveDownTo(PEELER_H-food.height);
    motor.rotateWith(PEELER_ROTATION);
    motor.bMoveTo(PEELER_X, PEELER_Y);

    //start peeling
    for (int i=0;i<=food.height;i=i+2)
        motor.bMoveDownTo(PEELER_H-food.height+i);

    //unload from peeler
    motor.bMoveTo(PEELER_X-50,PEELER_Y+50);
    motor.rotateWith(0);
    motor.bMoveDownTo(LOADING_CARRY_H);

    return true;
}

bool Executor::slice(AbstractFood &food)
{
    //loading into slicer
    motor.bMoveTo(SLICER_S_X,SLICER_S_Y);

    //slicing
    while(true)
    {
        motor.bMoveDownTillHit();

        //check the height
        if(SLICER_H - motor.getLPos()<=NEEDLE_H)
            break;

        motor.bMoveTo(SLICER_E_X,SLICER_E_Y);
        motor.bMoveDownBy(-5);
        motor.bMoveTo(SLICER_S_X,SLICER_S_Y);
    }

    //unload from slicer
    motor.bMoveDownTo(LOADING_CARRY_H);
    motor.bMoveTo(SLICER_S_X,SLICER_S_Y);

    return true;
}
