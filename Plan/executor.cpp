/*
 * Implemnet the core functionalities and execution sequences
 * Funcitons implemented includes: load, unload, peel, slice
 */

#include "executor.h"
#include "toolposition.h"
#include <vector>

Executor::Executor()
{
    //initial motor
    motor.init();
    motor.goToOrigin();

    //initial camera
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
    bool ret = false;

    //make sure the view of camera is not obscured
    motor.moveAwayForCamera();
    vision.takePicture();

    //detect all the fruits in drawer
    vision.detect();
    DetectionResults result = vision.getFirst(food.getType());
    cv::Point2f point = result.centroid;

    if(result.fruitType!=-1)
    {
        //move the gantry to the center point, pick the fruit
        motor.bMoveTo(point.x,point.y);
        motor.bMoveDownTillHit(food.loadForce);
        //register the size of food
        food.height = motor.getRevLPos() + LOADING_RES_H;
        food.length = result.topLeft.x-result.bottomRight.x;
        food.width = result.bottomRight.y - result.topLeft.y;
        food.centerX = point.x;
        food.centerY = point.y;

        //retract the linear actuator
        motor.bMoveDownTo(LOADING_CARRY_H);
        ret = true;
    }
    return ret;
}

bool Executor::fakeLoad(AbstractFood &food)
{
    motor.bMoveTo(0,0);
    motor.bMoveDownTillHit(food.loadForce);
    food.height = motor.getRevLPos() + LOADING_RES_H;

    if(food.getType()==1) //apple
    {
        food.width = 100;
        food.length =100;
    }
    else //potato
    {
        food.width = 200;
        food.length =200;
    }

    motor.bMoveDownTo(LOADING_CARRY_H);
    return true;
}

bool Executor::unload(AbstractFood &food)
{
    motor.bMoveTo(UNLOAD_X,UNLOAD_Y);
    motor.bMoveDownTo(0);

    return true;
}

bool Executor::peel(AbstractFood &food)
{
    //approaching the peeler station with dynamic position
    motor.bMoveYTo(PEELER_Y + food.width/2 + 100);
    motor.bMoveXTo(PEELER_X);
    motor.bMoveDownTo(PEELER_H-food.height + 5);

    //loading into peeler with feed back
    motor.rotateWith(PEELER_ROTATION);
    while(motor.getPeelDis()>BLADE_MAX+150)
    {
        motor.bMoveYBy(-10);
        if(motor.getYPos()==0)
            break;
    }

    //start peeling
    for (int i=5;i<=food.height-5;i=i+5)
    {
        motor.moveDownTo(PEELER_H-food.height+i);

        //dynamic adjust peeler position
        if(motor.getPeelDis()<BLADE_MIN)
            motor.moveYBy(3);
        else if(motor.getPeelDis()>BLADE_MAX)
            motor.moveYBy(-3);

        while(motor.getLPos() != PEELER_H-food.height+i){};
    }

    //unload from peeler
    motor.bMoveYBy(80);
    motor.rotateWith(0);
    motor.bMoveDownTo(LOADING_CARRY_H);
    food.isPeeled = true;

    return true;
}

bool Executor::slice(AbstractFood &food)
{
    //loading into slicer
    motor.bMoveTo(SLICER_S_X,SLICER_S_Y);
    motor.bMoveDownTillHit(25);
    motor.bMoveDownBy(-(70-food.defaultThick));
    motor.rotateWith(SLICE_ROT);

    //slicing
    while(true)
    {
        //check the height
        if(motor.getLPos()>=SLICER_H)
            break;

        motor.bMoveTo(SLICER_E_X,SLICER_E_Y);
        motor.bMoveDownBy(-50);
        motor.bMoveTo(SLICER_S_X,SLICER_S_Y);
        motor.bMoveDownBy(50+food.defaultThick);
    }

    //unload from slicer
    motor.bMoveDownTo(LOADING_CARRY_H);
    motor.rotateWith(0);
    motor.bMoveTo(SLICER_S_X,SLICER_S_Y);
    food.isSliced = true;

    return true;
}
