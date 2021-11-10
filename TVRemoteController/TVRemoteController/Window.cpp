#include "Window.h"
#include <GL/glut.h>

namespace EasyGL {
	class Window {
		private:
			unsigned int _displayMode;
			int _width, _height, _posX, _posY;
			const char* title;
		public:
			Window() {

			}

			Window(unsigned int displayMode, int width, int height, int posX, int posY, char* title) {
				this->_displayMode = displayMode;
				this->_width = width;
				this->_height = height;
				this->_posX = posX;
				this->_posY = posY;
				this->title = title;
			}

			~Window() {

			}

			unsigned int GetDisplayMode() {
				return _displayMode;
			}

			int GetWidth() {
				return _width;
			}

			int GetHeight() {
				return _height;
			}

			int GetPosX() {
				return _posX;
			}

			int GetPosY() {
				return _posY;
			}

			const char * GetTitle() {
				return title;
			}

			Window& SetDisplayMode(unsigned int displayMode) {
				this->_displayMode = displayMode;

				return *this;
			}

			Window& SetWidth(int width) {
				this->_width = width;

				return *this;
			}

			Window& SetHeight(int height) {
				this->_height = height;

				return *this;
			}

			Window& SetPosX(int posX) {
				this->_posX = posX;

				return *this;
			}

			Window& SetPosY(int posY) {
				this->_posY = posY;

				return *this;
			}

			Window& SetTitle(const char* title) {
				this->title = title;

				return *this;
			}

			Window& AddDisplayCallback(void (GLUTCALLBACK* func)(void)) {
				glutDisplayFunc(func);

				return *this;
			}

			Window& AddKeyboardListeners(void (GLUTCALLBACK* asciiKeysHandler)(unsigned char key, int x, int y), void (GLUTCALLBACK* nonAsciiKeysHandler)(int key, int x, int y)) {
				glutKeyboardFunc(asciiKeysHandler);
				glutSpecialFunc(nonAsciiKeysHandler);

				return *this;
			}

			Window& Open(int* argc, char* argv[]) {
				glutInit(argc, argv);
				glutInitDisplayMode(_displayMode);
				glutInitWindowSize(_width, _height);
				glutInitWindowPosition(_posX, _posY);
				glutCreateWindow(title);

				return *this;
			}

			Window& Run() {
				glutMainLoop();

				return *this;
			}
	};
}
