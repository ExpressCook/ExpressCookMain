#ifndef TOOLPOSITION_H
#define TOOLPOSITION_H

//the center point of the peeler
const int PEELER_X = 1000;
const int PEELER_Y = 600;
//the height that gripper touch the blade
const int PEELER_H = 400;
//the rotation speed during peelig
const int PEELER_ROTATION = 500;

//the center of unloading area
const int UNLOAD_X = 800;
const int UNLOAD_Y = 500;

//the height that gripper should extract after loading
const int LOADING_CARRY_H = 100;
//the residual height to ground after fully extension
const int LOADING_RES_H = 100;

#endif // TOOLPOSITION_H
