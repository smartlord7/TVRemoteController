#include <iostream>
#include "GL/glut.h"
#include "Main.h"
#include "ScreenHelper.h"
#include "GLWindow.h"
#include "WorldState.h"
#include "Observer.h"
#include "RgbImage.h"
#include "Materials.h"

using namespace EasyGL;
using namespace std;

static GLWindow w = GLWindow();
static WorldState world = WorldState();
static Observer& obs = world.GetObserver();
static OpenGL gl = world.GetOpenGL();
static Spinner&  fan = world.GetFan();
static Controller& ctrl = world.GetController();
static Television& tel = world.GetTelevision();
static Grid& grid = world.GetGrid();
static bool firstRun = true;
static RgbImage img;
static GLUquadricObj * sphere = gluNewQuadric();

static Color BLACK = Color(0.0, 0.0, 0.0, 0.0),
WHITE = Color(1.0, 1.0, 1.0, 1.0),
YELLOW = Color(1.0, 1.0, 0.0, 1.0),
RED = Color(1.0, 0.0, 0.0, 1.0),
GREEN = Color(0.0, 1.0, 0.0, 1.0),
BLUE = Color(0.0, 0.0, 1.0, 1.0),
GREY = Color(0.86, 0.86, 0.86, 1.0),
ORANGE = Color(0.9, 0.4, 0.0, 1.0),
PINK = Color(0.9, 0.1, 0.2, 1.0),
CYAN = Color(0.1, 0.9, 0.7, 1.0),
OCEAN_BLUE = Color(0.3, 0.5, 1.0, 1.0);

static vector<string> buttonLabels = { "1", "2", "3", "^", "+AC", "-AC", "4", "5", "6", "v", "X", "X", "7", "8", "9", "+b", "X", "X", "ON/OFF", "+v", "-v", "-b", "X", "X"};
static GLfloat ambientLight[4] = { 0.3, 0.4,0.5, 1.0 };

static GLfloat localLightPos[4] = { 0.0, 3.0, 0.0, 1.0 };
static GLfloat localLightAmb[4] = { 0, 0, 0, 0.0 };
static GLfloat localLightDif[4] = { 0, 0, 0, 0.0 };
static GLfloat localLightSpec[4] = { 0, 0, 0, 0.0 };
static GLfloat spotlightOpening = 0.0;
static GLfloat spotlightAngInc = 3.0;
static GLfloat spotlightPos[4] = { 0.0, 2.0, 2.0, 1.0};
static GLfloat spotlightDir[3] = { 0, 0, -1 };
static GLfloat discoColor[3] = { 1.0, 0.5, 0.7 };
static GLuint textures[13];

void DisplayText(string str, GLfloat x, GLfloat y, GLfloat z) {
    glRasterPos3f(x, y, z);
    int i = 0;
    while (str[i])
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i++]);
}

void LoadTexture(const char * fileName, GLuint * textureId) {
    glGenTextures(1, textureId);
    glBindTexture(GL_TEXTURE_2D, * textureId);
    img.LoadBmpFile(fileName);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
        img.GetNumCols(),
        img.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
        img.ImageData());
}


void LoadTextures() {
    LoadTexture("texture_floor.bmp", &textures[0]);
    LoadTexture("texture_table.bmp", &textures[1]);
    LoadTexture("texture_walls.bmp", &textures[2]);
    LoadTexture("texture_channel1.bmp", &textures[3]);
    LoadTexture("texture_channel2.bmp", &textures[4]);
    LoadTexture("texture_channel3.bmp", &textures[5]);
    LoadTexture("texture_channel4.bmp", &textures[6]);
    LoadTexture("texture_channel5.bmp", &textures[7]);
    LoadTexture("texture_channel6.bmp", &textures[8]);
    LoadTexture("texture_channel7.bmp", &textures[9]);
    LoadTexture("texture_channel8.bmp", &textures[10]);
    LoadTexture("texture_channel9.bmp", &textures[11]);
}

void DisplayLights() {
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_POSITION, localLightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, localLightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, localLightDif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, localLightSpec);

    GLfloat spotLightColor[] = { 1, 0.0, 0.0, 0.0 };
    GLfloat spotlightAk = 1.0;
    GLfloat spotlightAl = 0;
    GLfloat spotlightAq = 0.0f;
    GLfloat spotlightExp = 0.0;

    glLightfv(GL_LIGHT1, GL_POSITION, spotlightPos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, spotLightColor);
    glLightfv(GL_SPECULAR, GL_DIFFUSE, spotLightColor);
    glLightfv(GL_AMBIENT, GL_DIFFUSE, spotLightColor);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, spotlightAk);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, spotlightAl);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, spotlightAq);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotlightOpening);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlightDir);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotlightExp);
}

void Init() {
    srand(time(NULL));

    gl.ClearColor(BLACK)
        .SetShadeModel(GL_SMOOTH)
        .Enable(GL_DEPTH_TEST)
        .Enable(GL_NORMALIZE)
        .Enable(GL_LIGHTING)
        .Enable(GL_LIGHT0)
        .Enable(GL_LIGHT1);

    LoadTextures();
    DisplayLights();

   vector<Color> colorChannels = { CYAN, YELLOW, RED, GREEN, BLUE, GREY, ORANGE, PINK, OCEAN_BLUE };
   vector<string> audioChannelsFileNames = { "audio_channel1", "audio_channel2", "audio_channel3", "audio_channel4", 
       "audio_channel5", "audio_channel6", "audio_channel7","audio_channel8", "audio_channel9" };
   tel.SetColorChannels(colorChannels);
   tel.SetOffMaterial(MATERIAL_BLACK_PLASTIC);
   tel.SetOnMaterial(MATERIAL_SILVER);
   tel.SetAudioChannelsFileNames(audioChannelsFileNames);
   world.GetFan().StartStop();
}

void DisplayWalls() {
    double ceilingHeight = 11.0;
    double s = grid.GetRes();

    Material::BindMaterial(MATERIAL_PEARL);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glPushMatrix();
        glNormal3d(1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3d(-15.0, 0.0, -15.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3d(-15.0, ceilingHeight, -15.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3d(-15.0, ceilingHeight, 15.0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3d(-15.0, 0.0, 15.0);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glNormal3d(-1.0, 0.0, 0.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3d(15.0, 0.0, -15.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3d(15.0, ceilingHeight, -15.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3d(15.0, ceilingHeight, 15.0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3d(15.0, 0.0, 15.0);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glNormal3d(0.0, 0.0, -1.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3d(-15.0, 0.0, 15.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3d(15.0, 0.0, 15.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3d(15.0, ceilingHeight, 15.0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3d(-15.0, ceilingHeight, 15.0);
        glEnd();
    glPopMatrix();

    for (double x = -15.0; x < 15.0; x += s) {
        for (double z = -15.0; z < 15.0; z += s) {
            glPushMatrix();
            glNormal3d(0.0, -1.0, 0.0);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3d(x, ceilingHeight, z);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3d(x, ceilingHeight, z + s);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3d(x + s, ceilingHeight, z + s);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3d(x + s, ceilingHeight, z);
            glEnd();
            glPopMatrix();
        }
    }

    glPushMatrix();
        glNormal3d(0.0, 0.0, 1.0);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3d(-15.0, 0.0, -15.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3d(15.0, 0.0, -15.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3d(15.0, ceilingHeight, -15.0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3d(-15.0, ceilingHeight, -15.0);
        glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void DisplayFloor() {
    bool materialFlag = true;
    double s = grid.GetRes();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    for (double x = -15.0; x < 15.0; x += s) {
        for (double z = -15.0; z < 15.0; z += s) {
            if (materialFlag) {
                Material::BindMaterial(MATERIAL_JADE);
            }
            else {
                Material::BindMaterial(MATERIAL_COPPER);
            }

            glPushMatrix();
            glNormal3d(0.0, 1.0, 0.0);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3d(x, 0.0, z);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3d(x, 0.0, z + s);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3d(x + s, 0.0, z + s);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3d(x + s, 0.0, z);
            glEnd();
            glPopMatrix();

        }
            materialFlag = !materialFlag;
    }
    glDisable(GL_TEXTURE_2D);
}

void DisplayTable() {
    glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glTranslated(0.0, 0.325, -8.0);
        glPushMatrix();
            glScaled(4.0, 0.25, 3.0);
            glTranslated(0.0, 2.0, 0.0);
            gl.DrawCube();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        glPushMatrix();
            glScaled(1.5, 1.25, 1.75);
            glTranslated(0.0, 1.0, 0.0);
            gl.DrawCube();
        glPopMatrix();

        Material::BindMaterial(MATERIAL_BLACK_PLASTIC);
        glPushMatrix();
            glScaled(2.0, 2.0, 2.5);
            glTranslated(0.0, 0.75, 0.0);
            gl.DrawCube();
        glPopMatrix();

        if (tel.IsOn()) {
            Material::BindMaterial(tel.GetOnMaterial());
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, textures[CHANNELS_TEXTURES_OFFSET + tel.GetChannel()]);
            glPushMatrix();
                glScaled(1.25, 1.25, 2.25);
                glTranslated(0.0, 1.0 + 0.25, 0.1);
                gl.DrawSquare();
            glPopMatrix();
            glDisable(GL_TEXTURE_2D);

        } else {
            Material::BindMaterial(tel.GetOffMaterial());
            glPushMatrix();
                glScaled(1.25, 1.25, 2.25);
                glTranslated(0.0, 1.0 + 0.25, 0.1);
                gl.DrawSquare();
                glTranslated(0.0, 1.0, 3.0);
            glPopMatrix();
        }

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
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
        glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glColorMaterial(GL_FRONT, GL_SPECULAR);
    glColorMaterial(GL_FRONT, GL_AMBIENT);
    glPushMatrix();
        glTranslated(1.5, 0.325 + 0.25 + 0.1 + 0.3, -8.0);
        glColor4f(discoColor[0], discoColor[1], discoColor[2], 0.9);
        glPushMatrix();
            glTranslated(0.0, 0.3, 0.0);
            glutSolidSphere(0.3, 100, 100);
        glPopMatrix();
        glColor4f(1, 1, 1, 0.2);
        glPushMatrix();
            glRotated(-90, 1.0, 0.0, 0.0);
            glutSolidCone(0.2, 0.3, 100, 100);
        glPopMatrix();
    glPopMatrix();
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_BLEND);
}


void UpdateTVLight() {
    localLightDif[0] = tel.GetBrightness();
    localLightDif[1] = tel.GetBrightness();
    localLightDif[2] = tel.GetBrightness();
    localLightSpec[0] = tel.GetBrightness();
    localLightSpec[1] = tel.GetBrightness();
    localLightSpec[2] = tel.GetBrightness();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, localLightDif);
}

void HandleButton(int i) {
    switch (i) {
    case 0:
    case 1:
    case 2:
        tel.SetChannel(i);
        break;
    case 6:
    case 7:
    case 8:
        tel.SetChannel(i - 3);
        break;
    case 12:
    case 13:
    case 14:
        tel.SetChannel(i - 6);
        break;
    case 18:
        tel.TurnOnOff();
        UpdateTVLight();
        break;
    case 19:
        tel.IncVolume();
        break;
    case 20:
        tel.DecVolume();
        break;
    case 3:
        tel.IncChannel();
        break;
    case 9:
        tel.DecChannel();
        break;
    case 4:
        fan.IncVelocity();
        break;
    case 5:
        fan.DecVelocity();
        break;
    case 10:
        tel.SetBrightness(tel.GetBrightness() + 0.01);
        UpdateTVLight();
        break;
    case 11:
        tel.SetBrightness(tel.GetBrightness() - 0.01);
        UpdateTVLight();
    default:
        break;
    };
}

void DisplayController() {
    Point3D target = obs.GetTarget();
    double x, z, buttonAmp = 0;
    int rows = 0, cols = 0, button = 0;

    Material::BindMaterial(MATERIAL_BLACK_PLASTIC);
    glPushMatrix();
        glTranslated(target.GetX(), target.GetY(), target.GetZ() + 2);
        glPushMatrix();
            glScaled(0.8, 0.175, 3);
            gl.DrawCube();
        glPopMatrix();

        Material::BindMaterial(MATERIAL_WHITE_PLASTIC);
        glPushMatrix();
            glScaled(0.10, 0.08, 0.10);
            glTranslated(0.0, 0.0, 15.0);
            glutSolidSphere(1.0, 30, 30);
            Material::BindMaterial(MATERIAL_BLACK_PLASTIC);
            glPushMatrix();
                glRotated(ctrl.GetSpinnerAngle() + 90, 0.0, 0.0, 1.0);
                glScaled(1.5, 0.75, 0.25);
                glTranslated(0.0, 0.0, 3.5);
                gl.DrawCube();
            glPopMatrix();
        glPopMatrix();

        for (x = -0.35; x <= 0.35; x += 0.2) {
            for (z = -1.0; z <= 1.0; z += 0.4) {
                if (rows == 0) {
                    cols++;
                }
                  
                if (!firstRun) {
                    Button& btn = ctrl.GetButtons()[button];

                    if (btn.IsInAnimation()) {
                        buttonAmp = ctrl.GetButtons()[button].GetAmplitude();

                        if (!btn.IsHandled()) {
                            HandleButton(button);
                            btn.SetHandled(true);
                        }
                    }
                    else {
                        buttonAmp = 0;
                    }
                }

                glPushMatrix();
                    glTranslated(x + 0.05, -buttonAmp + 0.02, z + 0.05);
                    if (ctrl.GetSelectedButton() == button) {
                        Material::BindMaterial(MATERIAL_JADE);
                    } else {
                        Material::BindMaterial(MATERIAL_WHITE_PLASTIC);
                    }

                    glScaled(0.06, 0.06, 0.06);
                    glRotated(90, 1.0, 0.0, 0.0);
                    glutSolidDodecahedron();
                glPopMatrix();

                button++;
            }

            rows++;
        }

        if (firstRun) {
            ctrl.InitButtons(rows, cols, buttonLabels);
        }
    glPopMatrix();

}

void DisplayFan() {
    glPushMatrix();
        glTranslated(0.0 + 5.0, 2.0, -8.0 - 1.0);
        glRotated(-45, 0.0, 1.0, 0.0);
        glPushMatrix();
            glScaled(0.25, 4.0, 0.25);
            Material::BindMaterial(MATERIAL_SILVER);
            gl.DrawCube();
        glPopMatrix();
        glPushMatrix();
        glTranslated(0.0, 2.0, 0.0);
            Material::BindMaterial(MATERIAL_BLACK_PLASTIC);
            glPushMatrix();
                glRotated(90.0, 1.0, 0.0, 0.0);
                gl.DrawCylinder(1, 0.5);
            glPopMatrix();

            Material::BindMaterial(MATERIAL_WHITE_PLASTIC);
            glPushMatrix();
                glRotated(90.0, 1.0, 0.0, 0.0);
                gl.DrawCylinder(0.75, 0.2);
            glPopMatrix();

            glPushMatrix();
                glTranslated(0.0, 0.0, 0.1);
                glPushMatrix();
                    Material::BindMaterial(MATERIAL_WHITE_PLASTIC);
                    glRotated(fan.GetAngle(), 0.0, 0.0, 1.0);
                    glScaled(1.5, 0.1, 1);
                    gl.DrawSquare();
                glPopMatrix();

                glPushMatrix();
                    Material::BindMaterial(MATERIAL_WHITE_PLASTIC);
                    glRotated(fan.GetAngle() + 90, 0.0, 0.0, 1.0);
                    glScaled(1.5, 0.1, 1);
                    gl.DrawSquare();
                glPopMatrix();
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
}

void DisplayFunc() {
    gl.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
      .SetViewport(0, 0, w.GetWidth(), w.GetHeight());

    if (firstRun) {
        world.SetObserver(Observer((float) w.GetWidth() / (float) w.GetHeight()));
    }

    DisplayLights();
    DisplayFloor();
    DisplayWalls();
    DisplayTable();
    DisplayController();
    DisplayFan();

	w.RefreshDisplay();

    if (firstRun) {
        firstRun = false;
    }
}

void UpdateSpotlightDirection() {
    Vector3D newDir = obs.GetTarget() - obs.GetPosition();

    spotlightDir[0] = newDir.GetX();
    spotlightDir[1] = newDir.GetY();
    spotlightDir[2] = newDir.GetZ();
}

void UpdateSpotlightPos() {
    Point3D pos = obs.GetPosition();
    
    spotlightPos[0] = pos.GetX();
    spotlightPos[1] = pos.GetY();
    spotlightPos[2] = pos.GetZ() - 8;

    UpdateSpotlightDirection();
}

void UpdateDiscoColor() {
    discoColor[0] = (double) rand() / (double) RAND_MAX;
    discoColor[1] = (double) rand() / (double) RAND_MAX;
    discoColor[2] = (double) rand() / (double) RAND_MAX;
}

void ASCIIKeysListener(unsigned char key, int x, int y) {
    if (firstRun) {
        return;
    }

    Point3D pos = world.GetObserver().GetPosition(),
            tgt = world.GetObserver().GetTarget();
    int btn = ctrl.GetSelectedButton();
    int row = btn / ctrl.GetCols(), col = btn % ctrl.GetCols();
    float nextAngle;

    switch (key) {
        case 'd':
        case 'D':
            obs.Move(WALK_RIGHT);
            break;
        case 'a':
        case 'A':
            obs.Move(WALK_LEFT);
            break;
        case 's':
        case 'S':
            obs.Move(WALK_BACK);
            break;
        case 'w':
        case 'W':
            obs.Move(WALK_FRONT);
            break;
        case ' ':
            obs.Move(FLY_UP);
            break;
        case '<':
        case '>':
            obs.Move(FLY_DOWN);
            break;
        case 'j':
        case 'J':
            if (row == 0) {
                ctrl.SetSelectedButton((ctrl.GetRows() - 1) * ctrl.GetCols() + col);
            } else {
                ctrl.SetSelectedButton((row - 1) * ctrl.GetCols() + col);
            }
            break;
        case 'l':
        case 'L':
            if (row == ctrl.GetRows() - 1) {
                ctrl.SetSelectedButton(col);
            } else {
                ctrl.SetSelectedButton((row + 1) * ctrl.GetCols() + col);
            }
            break;
        case 'i':
        case 'I':
            if (col == 0) {
                ctrl.SetSelectedButton((row + 1) * ctrl.GetCols() - 1);
            } else {
                ctrl.SetSelectedButton(row * ctrl.GetCols() + col - 1);
            }
            break;
        case 'k':
        case 'K':
            if (col == ctrl.GetCols() - 1) {
                ctrl.SetSelectedButton(row * ctrl.GetCols());
            } else {
                ctrl.SetSelectedButton(row * ctrl.GetCols() + col + 1);
            }

            break;
        case 'p':
        case 'P':
            ctrl.PressSelectedButton();
            break;
        case 'b':
        case 'B':
            nextAngle = spotlightOpening - 1.0;
            ctrl.DecSpinnerAngle();
            if (nextAngle >= 0) {
                spotlightOpening = nextAngle;
            }
            break;
        case 'm':
        case 'M':
            nextAngle = spotlightOpening + 1.0;
            ctrl.IncSpinnerAngle();
            if (nextAngle < 180) {
                spotlightOpening = nextAngle;
            }
            break;
        case '1':
            if (tel.IsOn()) {
                localLightDif[0] = 1;
                localLightDif[1] = 0;
                localLightDif[2] = 0;
                localLightSpec[0] = 1;
                localLightSpec[1] = 0;
                localLightSpec[2] = 0;
                glLightfv(GL_LIGHT0, GL_DIFFUSE, localLightDif);
            }
            break;
        case '2':
            if (tel.IsOn()) {
                localLightDif[0] = 0;
                localLightDif[1] = 1;
                localLightDif[2] = 0;
                localLightSpec[0] = 0;
                localLightSpec[1] = 1;
                localLightSpec[2] = 0;
                glLightfv(GL_LIGHT0, GL_DIFFUSE, localLightDif);
            }
            break;
        case '3':
            if (tel.IsOn()) {
                localLightDif[0] = 0;
                localLightDif[1] = 0;
                localLightDif[2] = 1;
                localLightSpec[0] = 0;
                localLightSpec[1] = 0;
                localLightSpec[2] = 1;
                glLightfv(GL_LIGHT0, GL_DIFFUSE, localLightDif);
            }
            break;
        case '4':
            grid.SetGridRes(grid.GetRes() - 0.1);
            break;
        case '5':
            grid.SetGridRes(grid.GetRes() + 0.1);
            break;
        default:
            return;
    }
    UpdateSpotlightPos();
    w.Refresh();
}

void NonASCIIKeysListener(int key, int x, int y) {
    if (firstRun) {
        return;
    }

    switch (key) {
        case GLUT_KEY_LEFT:
            obs.RotateCamera(CAMERA_LEFT);
            break;
        case GLUT_KEY_RIGHT:
            obs.RotateCamera(CAMERA_RIGHT);
            break;
        case GLUT_KEY_DOWN:
            obs.RotateCamera(CAMERA_DOWN);
            break;
        case GLUT_KEY_UP:
            obs.RotateCamera(CAMERA_UP);
        default:
            return;
    }
    UpdateSpotlightDirection();
    w.Refresh();
}

void ResizeFunc(int width, int height) {
    w.SetWidth(width).SetHeight(height);
    gl.SetViewport(0, 0, width, height);
    w.Refresh();
}

void TimerFunc(int value) {
    int time = 1;

    obs.UpdateCamera().UpdatePosition();
    world.SetTimer(world.GetTimer() + 100);
    world.GetFan().Spin(time);

    if (world.GetTimer() % 1000 == 0) {
        UpdateDiscoColor();
    }
    w.Refresh().
      AddTimerCallback(time, TimerFunc);

    if (!firstRun) {
        ctrl.UpdateController(time);
    }

}

void InitConfig(int argc, char* argv[]) {
    int screenWidth, screenHeight;
    GetDesktopResolution(screenWidth, screenHeight);

    w = GLWindow().SetDisplayMode(DISPLAY_MODE)
        .SetWidth(screenWidth)
        .SetHeight(screenHeight)
        .SetPosX(WIN_POS_X)
        .SetPosY(WIN_POS_Y)
        .SetTitle(WIN_TITLE)
        .Open(&argc, argv);

    Init();

    w.AddDisplayCallback(DisplayFunc)
        .AddKeyboardListeners(ASCIIKeysListener, NonASCIIKeysListener)
        .AddResizeCallback(ResizeFunc)
        .AddTimerCallback(100, TimerFunc)
        .Run();
}

int main(int argc, char * argv[]) {
    InitConfig(argc, argv);

	return 0;
}
