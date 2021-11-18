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
const char* WIN_TITLE = "TV Remote Controller  ";

//#endregion GLWindow Parameters

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