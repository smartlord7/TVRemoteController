#ifndef WINDOW_H
#define WINDOW_H

#include "GL/glut.h"

namespace EasyGL {
	class GLWindow {
		private:
			unsigned int _displayMode;
			int _width, _height;
			double _posX, _posY;
			const char* title;
		public:
			GLWindow() {

			}

			GLWindow(unsigned int displayMode, int width, int height, int posX, int posY, const char* title) {
				this->_displayMode = displayMode;
				this->_width = width;
				this->_height = height;
				this->_posX = posX;
				this->_posY = posY;
				this->title = title;
			}

			~GLWindow() {

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

            double GetPosX() {
				return _posX;
			}

            double GetPosY() {
				return _posY;
			}

			const char * GetTitle() {
				return title;
			}

			GLWindow& SetDisplayMode(unsigned int displayMode) {
				this->_displayMode = displayMode;

				return *this;
			}

			GLWindow& SetWidth(int width) {
				this->_width = width;

				return *this;
			}

			GLWindow& SetHeight(int height) {
				this->_height = height;

				return *this;
			}

			GLWindow& SetPosX(double posX) {
				this->_posX = posX;

				return *this;
			}

			GLWindow& SetPosY(double posY) {
				this->_posY = posY;

				return *this;
			}

			GLWindow& SetTitle(const char* title) {
				this->title = title;

				return *this;
			}

        GLWindow& AddDisplayCallback(void (* displayFunc)()) {
            glutDisplayFunc(displayFunc);

            return *this;
        }

        GLWindow& AddKeyboardListeners(void (* asciiKeysHandler)( unsigned char, int, int ), void (* nonAsciiKeysHandler)( int, int, int ) ) {
            glutKeyboardFunc(asciiKeysHandler);
            glutSpecialFunc(nonAsciiKeysHandler);

            return *this;
        }

			GLWindow& Open(int* argc, char* argv[]) {
				glutInit(argc, argv);
				glutInitDisplayMode(_displayMode);
				glutInitWindowSize(_width, _height);
				glutInitWindowPosition(_posX, _posY);
				glutCreateWindow(title);

				return *this;
			}

			GLWindow& Run() {
				glutMainLoop();

				return *this;
			}

			GLWindow& Refresh() {
				glutSwapBuffers();

				return *this;
			}
	};
}

#endif