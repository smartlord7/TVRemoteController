#ifndef OPENGL_H
#define OPENGL_H

#include "Math.h"
#include "GL/glut.h"
#include "Color.h"
#include "Primitive3D.h"
#include "Math.h"
#include "Object3D.h"

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
			for (Primitive3D primitive : obj.GetPrimitives()) {
				SetColor(primitive.GetColor());
				glBegin(primitive.GetType());

				for (Point3D vertex : primitive.GetVertexes()) {
					glVertex3d(vertex.GetX(), vertex.GetY(), vertex.GetZ());
				}
				glEnd();

				if (primitive.GetBorderColor().IsValid()) {
					SetColor(primitive.GetBorderColor());
					glBegin(GL_LINES);

					for (Point3D vertex : primitive.GetVertexes()) {
						glVertex3d(vertex.GetX(), vertex.GetY(), vertex.GetZ());
					}
					glEnd();
				}
			}
			return *this;
		}

        OpenGL& DrawCylinder(double radius, double height, Point3D pos = Point3D(0, 0, 0), int res = 64) {
            double x, z, angle = 0.0;

            /** Draw the tube */
            glBegin(GL_QUAD_STRIP);
            angle = 0.0;
            while( angle < 2 * PI ) {
                x = radius * cos(angle);
                z = radius * sin(angle);
                glVertex3d(pos.GetX() + x, pos.GetY() + height, pos.GetZ() + z);
                glVertex3d(pos.GetX() + x, pos.GetY() , pos.GetZ() + z);
                angle = angle + 2 * PI / res;
            }
            glVertex3d(pos.GetX() + radius, pos.GetY() + height, pos.GetZ());
            glVertex3d(pos.GetX() + radius, pos.GetY(), pos.GetZ());
            glEnd();

            /** Draw the circle on top of cylinder */
            glBegin(GL_POLYGON);
            angle = 0.0;
            while( angle < 2 * PI ) {
                x = radius * cos(angle);
                z = radius * sin(angle);
                glVertex3d(x, height, z);
                angle = angle + 2 * PI / res;
            }
            glVertex3d(pos.GetX() + radius, pos.GetY() + height, pos.GetZ());
            glEnd();

            return *this;
        }
    };
}

#endif
