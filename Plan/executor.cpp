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
    motor.wakeAll();
    motor.goToOrigin();

    //initial camera
}

Executor::~Executor()
{
    //finialize motor
    motor.goToOrigin();
    motor.sleepAll();
    //fianlize vision
}

Executor& Executor::getInstance()
{
    //lazy classical singleton implementation
    //guaratee to be destroyed
    static Executor executor;
    return executor;
}

QString Executor::cvTest()
{
    motor.wakeAll();
    motor.moveAwayForCamera();
    vision.takePicture();
    vision.detect();
    QString text = "  Number of Apples   = " + QString::number(vision.numOfApples());
    text =  text + "\nNumber of Potatoes = " + QString::number(vision.numOfPotatoes());
    motor.sleepAll();
    return text;
}

bool Executor::load(AbstractFood &food)
{
    motor.wakeAll();
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

        //if in the right hand side, try reroute
        if(point.x<300)
        {
            //in the upper right
            if(point.y<375)
            {
                motor.bMoveYTo(0);
                motor.bMoveXTo(1000);
            }
            //in the bottom right
            else
            {
                motor.bMoveYTo(750);
                motor.bMoveXTo(1000);
            }
        }
        ret = true;
    }
    motor.sleepAll();
    return ret;
}

bool Executor::fakeLoad(AbstractFood &food)
{
    motor.wakeAll();
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
    motor.sleepAll();
    return true;
}

bool Executor::unload(AbstractFood &food)
{
    motor.wakeAll();
    motor.bMoveTo(UNLOAD_X,UNLOAD_Y);
    motor.bMoveDownTo(0);
    motor.sleepAll();
    return true;
}

bool Executor::peel(AbstractFood &food)
{
    motor.wakeAll();
    //approaching the peeler station with dynamic position
    motor.bMoveYTo(PEELER_Y + food.width/2 + 100);
    motor.bMoveXTo(PEELER_X);

    //bound the food height
    if(PEELER_H-food.height +5<LOADING_CARRY_H)
        food.height = PEELER_H + 5 -LOADING_CARRY_H;

    motor.bMoveDownTo(PEELER_H-food.height +10);

    //loading into peeler with feed back
    motor.rotateWith(PEELER_ROTATION);
    while(motor.getPeelDis()>BLADE_MAX+5)
    {
        motor.bMoveYBy(-10);
        if(motor.getYPos()==5)
            break;
    }

    //start peeling
    for (int i=10;i<=food.height-5;i=i+5)
    {
        motor.moveDownTo(PEELER_H-food.height+i);

        //dynamic adjust peeler position
        if(motor.getPeelDis()<BLADE_MIN)
            motor.moveYBy(3);
        else if(motor.getPeelDis()>BLADE_MAX)
            motor.moveYBy(-3);

        while(motor.getLPos() < PEELER_H-food.height+i-2)
        {
            if(motor.getLPos() >= 814)
                break;
        };
    }

    //unload from peeler
    motor.bMoveYBy(80);
    motor.rotateWith(0);
    motor.bMoveDownTo(LOADING_CARRY_H);
    food.isPeeled = true;

    motor.sleepAll();
    return true;
}

bool Executor::slice(AbstractFood &food)
{
    motor.wakeAll();
    //loading into slicer
    motor.bMoveTo(SLICER_S_X,SLICER_S_Y);
    motor.bMoveDownTillHit(25);
    motor.bMoveDownBy(-(60-food.defaultThick));
    motor.rotateWith(SLICE_ROT);

    int end_l_pos = 0;
    int unload_l = 100;
    if(food.getType()==1)
        unload_l = 50;
    bool has_unload = false;

    //slicing
    while(true)
    {
        end_l_pos = motor.getLPos();

        //check is finish
        if(end_l_pos>=SLICER_H)
            break;

        motor.bMoveTo(SLICER_E_X,SLICER_E_Y);
        motor.rotateWith(0);

        if(end_l_pos>=SLICER_H-50 && !has_unload)
        {
            //try to unload a little
            has_unload = true;
            motor.bMoveDownTo(LOADING_CARRY_H-unload_l);
            motor.bMoveTo(SLICER_S_X,SLICER_S_Y);
            motor.rotateWith(SLICE_ROT);
            motor.bMoveDownTo(end_l_pos-unload_l+food.defaultThick);
        }
        else
        {
            //normal slicing routine
            motor.bMoveDownBy(-50);
            motor.bMoveTo(SLICER_S_X,SLICER_S_Y);
            motor.rotateWith(SLICE_ROT);
            motor.bMoveDownBy(50+food.defaultThick);
        }
    }

    //unload from slicer
    motor.bMoveDownTo(LOADING_CARRY_H);
    motor.rotateWith(0);
    motor.bMoveTo(SLICER_S_X,SLICER_S_Y);
    food.isSliced = true;

    motor.sleepAll();
    return true;
}
