#ifndef OPENGL_H
#define OPENGL_H

#include "Math.h"
#include "GL/glut.h"
#include "Color.h"
#include "Math.h"

using namespace Geometry;

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
			glViewport(x, y, width, height);

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

		OpenGL& AddVertex(Point3D point) {
			glVertex3d(point.GetX(), point.GetY(), point.GetZ());

			return *this;
		}

		OpenGL& AddNormal(Vector3D normal) {
			glNormal3d(normal.GetX(), normal.GetY(), normal.GetZ());

			return *this;
		}

		OpenGL& DrawCube() {
			glBegin(GL_QUADS);
			// top
			glNormal3f(0.0f, 1.0f, 0.0f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);

			glEnd();

			glBegin(GL_QUADS);
			// front
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);

			glEnd();

			glBegin(GL_QUADS);
			// right
			glNormal3f(1.0f, 0.0f, 0.0f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);

			glEnd();

			glBegin(GL_QUADS);
			// left
			glNormal3f(-1.0f, 0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);

			glEnd();

			glBegin(GL_QUADS);
			// bottom
			glNormal3f(0.0f, -1.0f, 0.0f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);

			glEnd();

			glBegin(GL_QUADS);
			// back
			glNormal3f(0.0f, 0.0f, -1.0f);
			glVertex3f(0.5f, 0.5f, -0.5f);
			glVertex3f(0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, -0.5f, -0.5f);
			glVertex3f(-0.5f, 0.5f, -0.5f);

			glEnd();

			return *this;
		}

        OpenGL& DrawCylinder(double radius, double height, Point3D center = Point3D(0, 0, 0), int res = 64) {
            double x, z, angle = 0.0;
			Point3D v1, v2;

            /** Draw the tube */
            glBegin(GL_QUAD_STRIP);
            angle = 0.0;
            while( angle < 2 * PI ) {
                x = radius * cos(angle);
                z = radius * sin(angle);
				v1 = Point3D(center.GetX() + x, center.GetY() + height, center.GetZ() + z);
				v2 = Point3D(center.GetX() + x, center.GetY(), center.GetZ() + z);
				AddVertex(v1);
				AddNormal(v1 - center);
				AddVertex(v2);
				AddNormal(v2 - center);

                angle = angle + 2 * PI / res;
            }
			v1 = Point3D(center.GetX() + x, center.GetY() + height, center.GetZ() + z);
			v2 = Point3D(center.GetX() + x, center.GetY(), center.GetZ() + z);
			AddVertex(v1);
			AddNormal(v1 - center);
			AddVertex(v2);
			AddNormal(v2 - center);
            glEnd();

            /** Draw the circle on top of cylinder */
            glBegin(GL_POLYGON);
            angle = 0.0;
            while( angle < 2 * PI ) {
                x = radius * cos(angle);
                z = radius * sin(angle);
				glNormal3d(0.0, 0.0, 1.0);
                glVertex3d(x, height, z);
                angle = angle + 2 * PI / res;
            }
            glVertex3d(center.GetX() + radius, center.GetY() + height, center.GetZ());
            glEnd();

			/** Draw the circle on bottom of cylinder */
			glBegin(GL_POLYGON);
			angle = 0.0;
			while (angle < 2 * PI) {
				x = radius * cos(angle);
				z = radius * sin(angle);
				glNormal3d(0.0, 0.0, -1.0);
				glVertex3d(x, 0.0, z);
				angle = angle + 2 * PI / res;
			}
			glVertex3d(center.GetX() + radius, center.GetY() + height, center.GetZ());
			glEnd();

            return *this;
        }

		OpenGL& DrawSquare() {
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 0.0f, 1.0f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, 0.5f, 0.5f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glEnd();

			return *this;
		}
    };
}

#endif
