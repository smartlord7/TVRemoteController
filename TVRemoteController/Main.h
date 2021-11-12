#pragma once
// MAIN_H
#ifndef MAIN_H
#define MAIN_H

#include "Point3D.h"
#include "Vector3D.h"
#include "GL/glut.h"

using namespace Geometry;

//#region GLWindow Parameters

const int DISPLAY_MODE = GLUT_DOUBLE | GLUT_RGB;
const double WIN_POS_X = 0,
    WIN_POS_Y = 0;
const char* WIN_TITLE = "TV Remote Controller";

//#endregion GLWindow Parameters

//#region Observer Parameters

const double OBS_INIT_FOV = 45.0,
        OBS_INIT_MIN_RENDER_DIST = 0.1,
        OBS_INIT_MAX_RENDER_DIST = 40.0,
        OBS_VERTICAL_STEP = 0.3,
        OBS_HORIZONTAL_STEP = 0.3;
Point3D OBS_INIT_POS = Point3D(0.2, 1, 5.3),
        OBS_INIT_TARGET = Point3D(3.6, 1, -0.7);
Vector3D OBS_INIT_UP_AXIS = Vector3D(0.0, 1.0, 0.0);

//#region Observer Parameters

//#region Scenery Parameters

const double CONTROLLER_SIZE_X = 3,
        CONTROLLER_SIZE_Y = 0.25,
        CONTROLLER_SIZE_Z = 1,
        CONTROLLER_NUMBER_OF_BUTTONS_PER_ROW = 3,
        CONTROLLER_NUMBER_OF_BUTTONS_PER_COL = 6,
        CONTROLLER_BUTTON_HEIGHT = 0.1,
        CONTROLLER_BUTTON_PADDING = 0.1,
        CONTROLLER_BUTTON_PRESS_STEP = 0.001,
        CONTROLLER_BUTTON_RADIUS = 0.1,
        //CONTROLLER_BUTTON_RADIUS = (CONTROLLER_SIZE_X - ((CONTROLLER_NUMBER_OF_BUTTONS_PER_ROW + 1) * CONTROLLER_BUTTON_PADDING)) / CONTROLLER_NUMBER_OF_BUTTONS_PER_ROW,
        CONTROLLER_SPIN_STEP = 2;

//#endregion Scenery Parameters

#endif