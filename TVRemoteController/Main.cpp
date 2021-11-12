#include <iostream>
#include "Main.h"
#include "ScreenHelper.h"
#include "GLWindow.h"
#include "WorldState.h"
#include "Circle3D.h"
#include "Cilinder3D.h"
#include "GL/glut.h"

using namespace std;

static auto w = GLWindow();
static WorldState world = WorldState();
static OpenGL gl = world.GetOpenGL();
static bool firstRun = true;

Color BLACK = Color(0.0, 0.0, 0.0, 1.0),
WHITE = Color(1.0, 1.0, 1.0, 1.0),
YELLOW = Color(1.0, 1.0, 0.0, 1.0),
RED = Color(1.0, 0.0, 0.0, 1.0),
GREEN = Color(0.0, 1.0, 0.0, 1.0),
BLUE = Color(0.0, 0.0, 1.0, 1.0);

void Init() {
	gl.ClearColor(BLACK)
		.Enable(GL_DEPTH_TEST)
		.Enable(GL_CULL_FACE)
		.EnableArray(GL_VERTEX_ARRAY)
		.EnableArray(GL_NORMAL_ARRAY)
		.EnableArray(GL_COLOR_ARRAY)
		.SetShadeModel(GL_SMOOTH);
}

void DisplayAxis() {
	//Axis X
	gl.SetColor(RED);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(OBS_INIT_MAX_RENDER_DIST / 4, 0, 0);
	glEnd();

	//Axis Y
	gl.SetColor(GREEN);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, OBS_INIT_MAX_RENDER_DIST / 4, 0);
	glEnd();

	//Axis Z
	gl.SetColor(BLUE);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, OBS_INIT_MAX_RENDER_DIST / 4);
	glEnd();
}

void DisplayControllerButtons() {
    gl.SetColor(RED);
    glTranslated(0.0, CONTROLLER_BUTTON_HEIGHT-world.GetButtonYPos(), 0.0);
    glPushMatrix();
    gl.DrawCylinder(CONTROLLER_BUTTON_RADIUS, CONTROLLER_BUTTON_HEIGHT);
    glPopMatrix();

    if (world.GetButtonState() != 0) {
        if (world.GetButtonPressIterations() != 0 && world.GetButtonState() == 1) {
            world.SetButtonYPos(world.GetButtonYPos() + CONTROLLER_BUTTON_PRESS_STEP);
            world.SetButtonPressIterations(world.GetButtonPressIterations() - 1);
        } else if (world.GetButtonPressIterations() == 0 && world.GetButtonState() == 1) {
            world.SetButtonPressIterations(50);
            world.SetButtonState(2);
        } else if (world.GetButtonPressIterations() != 0 && world.GetButtonState() == 2) {
            world.SetButtonYPos(world.GetButtonYPos() - CONTROLLER_BUTTON_PRESS_STEP);
            world.SetButtonPressIterations(world.GetButtonPressIterations() - 1);
        } else if (world.GetButtonPressIterations() == 0 && world.GetButtonState() == 2) {
            world.SetButtonState(0);
        }

        glutPostRedisplay();
    }
}

void DisplayController() {
    gl.SetColor(YELLOW);
    glPushMatrix();
    glRotated(-90 + world.GetControllerYAngle(), 0, 1, 0);
    glRotated(world.GetControllerZAngle(), 0, 0, 1);
    glTranslated(0, 0, -CONTROLLER_SIZE_Z / 2);
    glPushMatrix();
    glScaled(CONTROLLER_SIZE_X, CONTROLLER_SIZE_Y, CONTROLLER_SIZE_Z);
    glutSolidCube(1);
    gl.SetColor(BLACK);
    glutWireCube(1);
    glPopMatrix();
    DisplayControllerButtons();
    glPopMatrix();
}

void DisplayFunc() {
    gl.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        .SetViewport(0, 0, w.GetWidth(), w.GetHeight());

    if (firstRun) {
        world.SetObserver(Observer(OBS_INIT_FOV, (float) w.GetWidth() / w.GetHeight(), OBS_INIT_MIN_RENDER_DIST,
                                   OBS_INIT_MAX_RENDER_DIST,
                                   OBS_INIT_POS,
                                   OBS_INIT_TARGET,
                                   OBS_INIT_UP_AXIS));
        firstRun = false;
    }


       DisplayAxis();
    DisplayController();

	glFlush();
	w.Refresh();
}

void ASCIIKeysListener(unsigned char key, int x, int y) {
    Point3D pos = world.GetObserver().GetPosition(),
            tgt = world.GetObserver().GetTarget();

    switch (key) {
        case 'd':
            pos.SetX(pos.GetX() + OBS_HORIZONTAL_STEP);
            tgt.SetX(tgt.GetX() + OBS_HORIZONTAL_STEP);
            break;
        case 'a':
            pos.SetX(pos.GetX() - OBS_HORIZONTAL_STEP);
            tgt.SetX(tgt.GetX() - OBS_HORIZONTAL_STEP);
            break;
        case 's':
            pos.SetZ(pos.GetZ() + OBS_HORIZONTAL_STEP);
            tgt.SetZ(tgt.GetZ() + OBS_HORIZONTAL_STEP);
            break;
        case 'w':
            pos.SetZ(pos.GetZ() - OBS_HORIZONTAL_STEP);
            tgt.SetZ(tgt.GetZ() - OBS_HORIZONTAL_STEP);
            break;
        case ' ':
            pos.SetY(pos.GetY() + OBS_VERTICAL_STEP);
            tgt.SetY(tgt.GetY() + OBS_VERTICAL_STEP);
            break;
        case '<':
            pos.SetY(pos.GetY() - OBS_VERTICAL_STEP);
            tgt.SetY(tgt.GetY() - OBS_VERTICAL_STEP);
            break;
        case 'j':
            world.SetControllerYAngle(world.GetControllerYAngle() + CONTROLLER_SPIN_STEP);
            break;
        case 'l':
            world.SetControllerYAngle(world.GetControllerYAngle() - CONTROLLER_SPIN_STEP);
            break;
        case 'i':
            world.SetControllerZAngle(world.GetControllerZAngle() + CONTROLLER_SPIN_STEP);
            break;
        case 'k':
            world.SetControllerZAngle(world.GetControllerZAngle() - CONTROLLER_SPIN_STEP);
            break;
        case 'p':
            if (world.GetButtonState() == 0) {
                world.SetButtonState(1);
                world.SetButtonPressIterations(50);
            }
            break;
    }

    world.GetObserver().SetPosition(pos);
    world.GetObserver().SetTarget(tgt);
    glutPostRedisplay();
}

void nonASCIIKeysListener(int key, int x, int y) {
    Point3D tgt = world.GetObserver().GetTarget();

    switch (key) {
        case GLUT_KEY_LEFT:
            tgt.SetX(tgt.GetX() - OBS_HORIZONTAL_STEP);
            break;
        case GLUT_KEY_RIGHT:
            tgt.SetX(tgt.GetX() + OBS_HORIZONTAL_STEP);
            break;
        case GLUT_KEY_DOWN:
            tgt.SetY(tgt.GetY() - OBS_VERTICAL_STEP);
            break;
        case GLUT_KEY_UP:
            tgt.SetY(tgt.GetY() + OBS_VERTICAL_STEP);
            break;
    }

    world.GetObserver().SetTarget(tgt);
    glutPostRedisplay();
}

int main(int argc, char * argv[]) {
	int screenWidth, screenHeight;
	GetDesktopResolution(screenWidth, screenHeight);

	Init();

	w = GLWindow().SetDisplayMode(DISPLAY_MODE)
		.SetWidth(screenWidth)
		.SetHeight(screenHeight)
		.SetPosX(WIN_POS_X)
		.SetPosY(WIN_POS_Y)
		.SetTitle(WIN_TITLE)
		.Open(&argc, argv);

	w.AddDisplayCallback(DisplayFunc)
		.AddKeyboardListeners(ASCIIKeysListener, nonASCIIKeysListener)
		.Run();

	return 0;
}