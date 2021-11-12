#include "Main.h"
#include "ScreenHelper.h"
#include "Window.h"
#include "WorldState.h"
#include "Circle3D.h"
#include "Cilinder3D.h"

static Window w = Window();
static WorldState world = WorldState();
static OpenGL gl = world.GetOpenGL();

Color BLACK = Color(0.0, 0.0, 0.0, 1.0),
WHITE = Color(1.0, 1.0, 1.0, 1.0),
YELLOW = Color(1.0, 1.0, 0.0, 1.0),
RED = Color(1.0, 0.0, 0.0, 1.0),
GREEN = Color(0.0, 1.0, 0.0, 1.0),
BLUE = Color(0.0, 0.0, 1.0, 1.0);

void Init() {
	gl.ClearColor(BLACK)
		.Enable(GL_DEPTH_TEST)
		.EnableArray(GL_VERTEX_ARRAY)
		.EnableArray(GL_NORMAL_ARRAY)
		.EnableArray(GL_COLOR_ARRAY)
		.SetShadeModel(GL_SMOOTH);
}

void DisplayAxis() {
	//Axis X
	gl.SetColor(RED);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(OBS_INIT_MAX_RENDER_DIST, 0, 0);
	glEnd();

	//Axis Y
	gl.SetColor(GREEN);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, OBS_INIT_MAX_RENDER_DIST, 0);
	glEnd();

	//AxisEixo Z
	gl.SetColor(BLUE);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, OBS_INIT_MAX_RENDER_DIST);
	glEnd();
}

void Display() {

	gl.Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
		.SetViewport(0, 0, w.GetWidth(), w.GetHeight());

	world.SetObserver(Observer(OBS_INIT_FOV, (float) w.GetWidth() / w.GetHeight(), OBS_INIT_MIN_RENDER_DIST, OBS_INIT_MAX_RENDER_DIST,
		Point3D(OBS_INIT_POS),
		Point3D(OBS_INIT_TARGET),
		Vector3D(OBS_INIT_UP_AXIS)));

	DisplayAxis();
	Cilinder3D cilinder = Cilinder3D(2, 2, 600);
	cilinder.SetColor(RED);
	gl.DrawObject(cilinder);

	glFlush();
	w.Refresh();
}

void ASCIIKeysListener(unsigned char key, int x, int y) {

}

void nonASCIIKeysListener(int key, int x, int y) {

}

int main(int argc, char * argv[]) {
	int screenWidth, screenHeight;
	GetDesktopResolution(screenWidth, screenHeight);

	Init();

	w = Window().SetDisplayMode(DISPLAY_MODE)
		.SetWidth(screenWidth)
		.SetHeight(screenHeight)
		.SetPosX(WIN_POS_X)
		.SetPosY(WIN_POS_Y)
		.SetTitle(WIN_TITLE)
		.Open(&argc, argv);

	w.AddDisplayCallback(Display)
		.AddKeyboardListeners(ASCIIKeysListener, nonASCIIKeysListener)
		.Run();

	return 0;
}
