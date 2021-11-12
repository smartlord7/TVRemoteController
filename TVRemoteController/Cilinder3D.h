#include "Point3D.h"
#include "Circle3D.h"
#include "Math.h"
#include "GL/glut.h"
#include "Primitive3D.h"

#ifndef CILINDER3D_H
#define CILINDER3D_H

namespace Geometry {
	class Cilinder3D : public Object3D {
	private:
		double radius, height;
		int precision;

		void _CalcVertexes() {
			double x, y, angle = 0.0;
			Primitive3D primitive = Primitive3D();
			primitive.SetType(GL_QUAD_STRIP);
			primitive.SetColor(color);
			angle = 0.0;
			while (angle < 2 * PI) {
				x = radius * cos(angle);
				y = radius * sin(angle);
				primitive.AddVertex(Point3D(x, y, height));
				primitive.AddVertex(Point3D(x, y, 0.0));
				angle = angle + double(2 * PI / precision);
			}

			primitive.AddVertex(Point3D(radius, 0.0, height));
			primitive.AddVertex(Point3D(radius, 0.0, 0.0));
			AddPrimitive(primitive);

			primitive = Primitive3D();
			primitive.SetType(GL_POLYGON);
			primitive.SetColor(color);
			primitive.SetBorderColor(borderColor);
            AddPrimitive(Circle3D(radius, precision));
		}
	public:
		Cilinder3D() {
		}

		Cilinder3D(double radius, double height, int precision) {
            this->radius = radius;
            this->height = height;
            this->precision = precision;

            _CalcVertexes();
        }

		~Cilinder3D() {
		}

		double GetHeight() {
			return height;
		}

		Cilinder3D& SetHeight(double height) {
			this->height = height;

			return *this;
		}

        double GetRadius() {
            return radius;
        }

        Cilinder3D& SetRadius(double radius) {
            this->height = radius;

            return *this;
        }
	};
}

#endif
