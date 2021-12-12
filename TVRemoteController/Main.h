#pragma once
// MAIN_H
#ifndef MAIN_H
#define MAIN_H

#include "Point3D.h"
#include "Vector3D.h"
#include "GL/glut.h"

using namespace Geometry;

//#region GLWindow Parameters

const int CHANNELS_TEXTURES_OFFSET = 3;
const int BUTTONS_TEXTURES_OFFSET = 12;
const int DISPLAY_MODE = GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH;
const double WIN_POS_X = 0,
    WIN_POS_Y = 0;
const char* WIN_TITLE = "TV Remote Controller  ";

//#endregion GLWindow Parameters

//#region Scenery Parameters

//#endregion Scenery Parameters

#endif