#include <stdlib.h>
#include "Main.h"
#include "Window.cpp"
#include "ScreenHelper.h"
#include "Colors.h"
#include "WorldState.cpp"

using namespace EasyGL;

static WorldState world = WorldState();
static OpenGL gl = world.GetOpenGL();
static int screenWidth, screenHeight;

Color black = Color(BLACK),
	yellow = Color(YELLOW);

void Init() {
	gl.ClearColor(black)
		.Enable(GL_DEPTH_TEST)
		.EnableArray(GL_VERTEX_ARRAY)
		.EnableArray(GL_NORMAL_ARRAY)
		.EnableArray(GL_COLOR_ARRAY)
		.SetShadeModel(GL_SMOOTH);
}

void Display() {

	gl.Clear(CLEAR_MODE)
		.SetViewport(0, 0, screenWidth, screenHeight);

	world.SetObserver(Observer(WORLD_INIT_FOV, (float) screenWidth / screenHeight, WORLD_MIN_Z, WORLD_MAX_Z,
		Point3D(0, 0, 10),
		Point3D(0, 0, 0),
		Vector3D(0, 1, 0)));

	gl.SetColor(yellow);

	glFlush();
	glutWireTeapot(2);
	glutSwapBuffers();
}

void ASCIIKeysListener(unsigned char key, int x, int y) {

}

void nonASCIIKeysListener(int key, int x, int y) {

}

int main(int argc, char * argv[]) {
	GetDesktopResolution(screenWidth, screenHeight);

	Init();

	Window w = Window().SetDisplayMode(DISPLAY_MODE)
		.SetWidth(screenWidth)
		.SetHeight(screenHeight)
		.SetPosX(WIN_POS_X)
		.SetPosY(WIN_POS_Y)
		.SetTitle(WIN_TITLE)
		.Open(&argc, argv);

	Init();

	w.AddDisplayCallback(Display)
		.AddKeyboardListeners(ASCIIKeysListener, nonASCIIKeysListener)
		.Run();

	return EXIT_SUCCESS;
}
