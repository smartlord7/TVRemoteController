#include <iostream>
#include "Main.h"
#include "ScreenHelper.h"
#include "GLWindow.h"
#include "WorldState.h"
#include "Observer.h"
#include "Circle3D.h"
#include "Cilinder3D.h"
#include "GL/glut.h"
#include "RgbImage.h"

using namespace EasyGL;
using namespace std;

static GLWindow w = GLWindow();
static WorldState world = WorldState();
static Observer& obs = world.GetObserver();
static OpenGL gl = world.GetOpenGL();
static bool firstRun = true;
static RgbImage img;

Color BLACK = Color(0.0, 0.0, 0.0, 1.0),
WHITE = Color(1.0, 1.0, 1.0, 1.0),
YELLOW = Color(1.0, 1.0, 0.0, 1.0),
RED = Color(1.0, 0.0, 0.0, 1.0),
GREEN = Color(0.0, 1.0, 0.0, 1.0),
BLUE = Color(0.0, 0.0, 1.0, 1.0),
GREY = Color(0.86, 0.86, 0.86, 1.0);

static float vertexes[] = {
        1.0f,1.0f,1.0f,   -1.0f,1.0f,1.0f,   -1.0f,-1.0f,1.0f,   1.0f,-1.0f,1.0f,      // face #1
        1.0f,1.0f,1.0f,    1.0f,-1.0f,1.0f,   1.0f,-1.0f,-1.0f,  1.0f,1.0f,-1.0f,      // face #2
        1.0f,1.0f,1.0f,    1.0f,1.0f,-1.0f,  -1.0f,1.0f,-1.0f,  -1.0f,1.0f,1.0f,       // face #3
       -1.0f,-1.0f,-1.0f, -1.0f,1.0f,-1.0f,   1.0f,1.0f,-1.0f,   1.0f,-1.0f,-1.0f,     // face #4
       -1.0f,-1.0f,-1.0f, -1.0f,-1.0f,1.0f,  -1.0f,1.0f,1.0f,   -1.0f,1.0f,-1.0f,      // face #5
       -1.0f,-1.0f,-1.0f,  1.0f,-1.0f,-1.0f,  1.0f,-1.0f,1.0f,  -1.0f,-1.0f,1.0f      // face #6
};

static float colors[] = {
        1,0,0,  1,0,0,  1,0,0,  1,0,0,      // face #1 is red
        0,1,0,  0,1,0,  0,1,0,  0,1,0,      // face #2 is green
        0,0,1,  0,0,1,  0,0,1,  0,0,1,      // face #3 is blue
        1,1,0,  1,1,0,  1,1,0,  1,1,0,      // face #4 is yellow
        0,1,1,  0,1,1,  0,1,1,  0,1,1,      // face #5 is cyan
        1,0,1,  1,0,1,  1,0,1,  1,0,1, }; // face #6 is red

float normals[] = {
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,
    -1.0f, 0.0f, 0.0f,

};

GLuint textures[4];
GLfloat texturesCoordes[] = {
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1,
0, 0,
1, 0,
1, 1,
0, 1 };


void InitLights() {
    glEnable(GL_LIGHT0);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    GLfloat LAmbient[4] = { 0.2f, 0.2f, 0.2f, 1.0 };
    GLfloat LDiffuse[4] = { 1.0f, 1.0f, 1.0f, 1.f };
    GLfloat LSpecular[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
    GLfloat LPosition[4] = {0, 5, 0 };
    GLfloat LSpotDirec[3] = { 0.0,0.0,0.0 };
    GLfloat LSpotCutOff = 180.0f;
    GLfloat LSpotExponent = 0.0f;
    GLfloat LAttenuationConst = 1.0f;
    GLfloat LAttenuationLinear = 0.0f;
    GLfloat LAttenuationQuadrat = 0.0f;

    glLightfv(GL_LIGHT0, GL_AMBIENT, LAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, LPosition);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, LSpotDirec);
    glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, &LSpotCutOff);
    glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, &LSpotExponent);
    glLightfv(GL_LIGHT0, GL_CONSTANT_ATTENUATION, &LAttenuationConst);
    glLightfv(GL_LIGHT0, GL_LINEAR_ATTENUATION, &LAttenuationLinear);
    glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, &LAttenuationQuadrat);
}

void LoadTextures() {
    glGenTextures(1, &textures[0]);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    img.LoadBmpFile("texture_floor.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
        img.GetNumCols(),
        img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
        img.ImageData());
}

void Init() {
	gl.ClearColor(BLACK)
		.Enable(GL_CULL_FACE)
        .Enable(GL_NORMALIZE)
        .Enable(GL_LIGHTING)
        .Enable(GL_COLOR_MATERIAL)
		.Enable(GL_DEPTH_TEST)
        .Enable(GL_BLEND)
		.EnableArray(GL_VERTEX_ARRAY)
		.EnableArray(GL_NORMAL_ARRAY)
		.EnableArray(GL_COLOR_ARRAY)
		.SetShadeModel(GL_SMOOTH);

    glTexCoordPointer(2, GL_FLOAT, 0, texturesCoordes);
    LoadTextures();
    InitLights();
}


void DisplayAxis() {
    double maxRenderDist = obs.GetMaxRenderDist();

	//Axis X
	gl.SetColor(RED);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(maxRenderDist / 4, 0, 0);
	glEnd();

	//Axis Y
	gl.SetColor(GREEN);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, maxRenderDist / 4, 0);
	glEnd();

	//Axis Z
	gl.SetColor(BLUE);
	glBegin(GL_LINES);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, maxRenderDist / 4);
	glEnd();
}

void DisplayFloor() {
    bool colorFlag = false;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[0]);

    for (double x = -10; x <= 10; x++) {
        for (double z = -10; z <= 10; z++) {
            if (colorFlag){
                gl.SetColor(WHITE);
            }
            else {
                gl.SetColor(BLACK);
            }

            glTexCoord2f(0.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f);
            glTexCoord2f(1.0f, 1.0f);
            glTexCoord2f(0.0f, 1.0f);

            glBegin(GL_QUADS);
            glVertex3d(x, 0, z);
            glVertex3d(x, 0, z + 1.0);
            glVertex3d(x + 1.0, 0, z + 1.0);
            glVertex3d(x + 1.0, 0, z);
            glEnd();

            colorFlag = !colorFlag;
        }
   }

    glDisable(GL_TEXTURE_2D);
}

void DisplayTable() {
    glPushMatrix();
        glTranslated(0.0, 0.325, -8.0);
        gl.SetColor(GREEN);
        glPushMatrix();
            glScaled(4.0, 0.25, 3.0);
            glTranslated(0.0, 2.0, 0.0);
            gl.DrawCube();
        glPopMatrix();

        gl.SetColor(GREY);
        glPushMatrix();
            glScaled(1.5, 1.25, 1.75);
            glTranslated(0.0, 1.0, 0.0);
            gl.DrawCube();
        glPopMatrix();

        gl.SetColor(WHITE);
        glPushMatrix();
            glScaled(1.5, 1.5, 2.5);
            glTranslated(0.0, 1.0, 0.0);
            gl.DrawCube();
        glPopMatrix();

        gl.SetColor(BLACK);
        glPushMatrix();
        glScaled(1.25, 1.25, 2.25);
        glTranslated(0.0, 1.0 + 0.25, -0.10);
        gl.DrawSquare();
        glPopMatrix();

        gl.SetColor(BLUE);
        glPushMatrix();
            glScaled(0.1, 1 - 0.25, 0.1);
            glPushMatrix();
                glTranslated(-16.0, 0.0, -2.0);
                gl.DrawCube();
            glPopMatrix();
            glPushMatrix();
                glTranslated(-16.0, 0.0, 2.0);
                gl.DrawCube();
            glPopMatrix();
            glPushMatrix();
                glTranslated(16.0, 0.0, -2.0);
                gl.DrawCube();
            glPopMatrix();
            glPushMatrix();
            glTranslated(16.0, 0.0, 2.0);
                gl.DrawCube();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void DisplayController() {
    Point3D target = obs.GetTarget();
    double x, z;

    gl.SetColor(YELLOW);
    glPushMatrix();
        glTranslated(target.GetX(), target.GetY(), target.GetZ() + 2);
        glPushMatrix();
            glScaled(0.8, 0.125, 3);
            gl.DrawCube();
        glPopMatrix();
        gl.SetColor(RED);

        for (x = -0.35; x <= 0.35; x += 0.2) {
            for (z = -1.0; z <= 1.0; z += 0.4) {
                glPushMatrix();
                    glTranslated(x + 0.05, 0, z + 0.05);
                    gl.DrawCylinder(0.05, 0.05);
                glPopMatrix();
            }
        }
    glPopMatrix();
}

void DisplayFan() {
    glPushMatrix();
        glTranslated(0.0 + 5.0, 2.0, -8.0 - 1.0);
        glRotated(-45, 0.0, 1.0, 0.0);
        glPushMatrix();
            glScaled(0.25, 4.0, 0.25);
            gl.SetColor(GREEN);
            gl.DrawCube();
        glPopMatrix();
        glPushMatrix();
        glTranslated(0.0, 2.0, 0.0);
            gl.SetColor(RED);
            glPushMatrix();
                glRotated(90.0, 1.0, 0.0, 0.0);
                gl.DrawCylinder(1, 0.5);
            glPopMatrix();

            gl.SetColor(YELLOW);
            glPushMatrix();
                glRotated(90.0, 1.0, 0.0, 0.0);
                gl.DrawCylinder(0.75, 0.2);
            glPopMatrix();

            gl.SetColor(BLACK);
            glPushMatrix();
                glScaled(1.0, 0.1, 1.0);
                gl.DrawSquare();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void DisplayFunc() {
    gl.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
        .SetViewport(0, 0, w.GetWidth(), w.GetHeight());

    if (firstRun) {
        world.SetObserver(Observer((float) w.GetWidth() / (float) w.GetHeight()));
        firstRun = false;
    }

    DisplayFloor();
    DisplayTable();
    DisplayController();
    DisplayFan();

	glFlush();
	w.RefreshDisplay();
}

void ASCIIKeysListener(unsigned char key, int x, int y) {
    Point3D pos = world.GetObserver().GetPosition(),
            tgt = world.GetObserver().GetTarget();

    switch (key) {
        case 'd':
        case 'D':
            obs.MoveHorizontally(WALK_RIGHT);
            break;
        case 'a':
        case 'A':
            obs.MoveHorizontally(WALK_LEFT);
            break;
        case 's':
        case 'S':
            obs.MoveHorizontally(WALK_BACK);
            break;
        case 'w':
        case 'W':
            obs.MoveHorizontally(WALK_FRONT);
            break;
        case ' ':
            obs.MoveVertically(FLY_UP);
            break;
        case '<':
        case '>':
            obs.MoveVertically(FLY_DOWN);
            break;
        default:
            return;
    }

    w.Refresh();
}

void NonASCIIKeysListener(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_LEFT:
            obs.MoveCamera(CAMERA_LEFT);
            break;
        case GLUT_KEY_RIGHT:
            obs.MoveCamera(CAMERA_RIGHT);
            break;
        case GLUT_KEY_DOWN:
            obs.MoveCamera(CAMERA_DOWN);
            break;
        case GLUT_KEY_UP:
            obs.MoveCamera(CAMERA_UP);
            break;
        default:
            return;
    }

    w.Refresh();
}

void ResizeFunc(int width, int height) {
    w.SetWidth(width).SetHeight(height);
    gl.SetViewport(0, 0, width, height);
    w.Refresh();
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
		.AddKeyboardListeners(ASCIIKeysListener, NonASCIIKeysListener)
        .AddResizeCallback(ResizeFunc)
		.Run();

	return 0;
}
