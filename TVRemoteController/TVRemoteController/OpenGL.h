#ifndef OPENGL_H
#define OPENGL_H

#include "math.h"
#include "Color.h"
#include "Math.h"
#include "Object3D.h"
#include <GL/glut.h>

namespace EasyGL {
	class OpenGL {
	private:
		void _DrawObject(Object3D obj, GLenum mode) {
			glBegin(mode);
			for (Point3D vertex : obj.GetVertexes()) {
				glVertex3d(vertex.GetX(), vertex.GetY(), vertex.GetZ());
			}
			glEnd();
		}

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

		OpenGL& DrawObject(Object3D obj) {
			SetColor(obj.GetColor());
			_DrawObject(obj, GL_LINE_LOOP);

			if (obj.GetBorderColor().IsValid()) {
				SetColor(obj.GetColor());
				_DrawObject(obj, GL_LINES);
			}

			return *this;
		}

		OpenGL& DrawCilinder(Point3D point, double radius, double height, int precision = 64) {
			double x, y, angle = 0.0;

			/** Draw the tube */
			glBegin(GL_QUAD_STRIP);
			angle = 0.0;
			while (angle < 2 * PI) {
				x = radius * cos(angle);
				y = radius * sin(angle);
				glVertex3f(x, y, height);
				glVertex3f(x, y, 0.0);
				angle = angle + double(2 * PI / precision);
			}
			glVertex3f(radius, 0.0, height);
			glVertex3f(radius, 0.0, 0.0);
			glEnd();

			/** Draw the circle on top of cylinder */
			glBegin(GL_POLYGON);
			angle = 0.0;
			while (angle < 2 * PI) {
				x = radius * cos(angle);
				y = radius * sin(angle);
				glVertex3f(x, y, height);
				angle = angle + double(2 * PI / precision);
			}
			glVertex3f(radius, 0.0, height);
			glEnd();

			return *this;
		}
	};
}

#endif OPENGL_H