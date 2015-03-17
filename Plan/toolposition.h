/*
 * Define the constant which represents the tool position
 * and other configuration. These numbers are mainly used
 * inside the Executor
 */

#ifndef TOOLPOSITION_H
#define TOOLPOSITION_H

//the center point of the peeler
const int PEELER_X = 1700;
const int PEELER_Y = 0;
//the height that gripper touch the blade
const int PEELER_H = 810;
//the rotation speed during peelig
const int PEELER_ROTATION = 400;
//optimum blade position
const int BLADE_MIN = 45;
const int BLADE_MAX = 60;

//the start point of the slicer
const int SLICER_S_X = 1000;
const int SLICER_S_Y = 500;
//the end point of the slicer
const int SLICER_E_X = 1000;
const int SLICER_E_Y = 300;
//the height of the slicer blade
const int SLICER_H = 600;
//the length of the needle
const int NEEDLE_H = 100;

//the center of unloading area
const int UNLOAD_X = 1500;
const int UNLOAD_Y = 510;

//the height that gripper should extract after loading
const int LOADING_CARRY_H = 290;
//the residual height to ground after fully extension
const int LOADING_RES_H = 350;

#endif // TOOLPOSITION_H
