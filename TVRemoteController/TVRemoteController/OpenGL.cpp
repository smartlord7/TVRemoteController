#include "OpenGL.h"
#include "Color.cpp"
#include <GL/glut.h>

namespace EasyGL {
	class OpenGL {
	private:

	public:
		OpenGL() {
		}

		~OpenGL() {

		}

		OpenGL& LookAt(double eyeX, double eyeY, double eyeZ, double lookX, double lookY, double lookZ, double upX, double upY, double upZ) {
			gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);

			return *this;
		}

		OpenGL& ResetMatrix() {
			glLoadIdentity();

			return *this;
		}

		OpenGL& SetPerspective(double fieldOfVision, double aspect, double minZ, double maxZ) {
			gluPerspective(fieldOfVision, aspect, minZ, maxZ);

			return *this;
		}

		OpenGL& SetViewport(int x, int y, GLsizei width, GLsizei height) {
			glViewport(0, 0, width, height);

			return *this;
		}

		OpenGL& SetMatrixMode(GLenum mode) {
			glMatrixMode(mode);

			return *this;
		}

		OpenGL& ClearColor(Color color) {
			glClearColor(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());

			return *this;
		}

		OpenGL& Clear(GLbitfield mode) {
			glClear(mode);

			return *this;
		}

		OpenGL& SetColor(Color color) {
			glColor4f(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());

			return *this;
		}

		OpenGL& SetShadeModel(GLenum shadeModel) {
			glShadeModel(GL_SMOOTH);

			return *this;
		}

		OpenGL& Enable(GLenum feature) {
			glEnable(feature);

			return *this;
		}

		OpenGL& EnableArray(GLenum array) {
			glEnableClientState(array);

			return *this;
		}
	};
}
