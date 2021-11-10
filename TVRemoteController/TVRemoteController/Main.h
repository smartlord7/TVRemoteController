#pragma once
// MAIN_H
#ifndef MAIN_H
#define MAIN_H

#include <GL/glut.h>

//#region Window Parameters

#define DISPLAY_MODE GLUT_DOUBLE | GLUT_RGB
#define WIN_POS_X 0
#define WIN_POS_Y 0
#define WIN_TITLE "TV Remote Controller"

//#endregion Window Parameters

//#region World Parameters

#define WORLD_INIT_FOV 45
#define WORLD_MIN_Z 0.1
#define WORLD_MAX_Z 10

//#endregion World Parameters

#define CLEAR_MODE GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT

#endif MAIN_H