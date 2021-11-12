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
        OBS_VERTICAL_STEP = 0.1,
        OBS_HORIZONTAL_STEP = 0.1;
Point3D OBS_INIT_POS = Point3D(5.0, 5.0, 5.0),
        OBS_INIT_TARGET = Point3D(5.0, 0.0, 0.0);
Vector3D OBS_INIT_UP_AXIS = Vector3D(0.0, 1.0, 0.0);


//#region Observer Parameters



#endif