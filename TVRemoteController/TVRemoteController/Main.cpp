#include <stdlib.h>
#include "Main.h"
#include "Window.h"
#include "ScreenHelper.h"
#include "Colors.h"
#include "Window.cpp"

using namespace EasyGL;

void Init() {
	glClearColor(BLACK);		
	glEnable(GL_DEPTH_TEST);	
	glShadeModel(GL_SMOOTH);	

	
}

void Display() {

	glutWireTeapot(100);
	glutSwapBuffers();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

}

void ASCIIKeysListener(unsigned char key, int x, int y) {

}

void nonASCIIKeysListener(int key, int x, int y) {

}

int main(int argc, char * argv[]) {
	int screenWidth, screenHeight;
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
