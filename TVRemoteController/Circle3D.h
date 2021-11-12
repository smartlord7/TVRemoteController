#ifndef CIRCLE3D_H
#define CIRCLE3D_H

#include "Primitive3D.h"
#include "Math.h"

namespace Geometry {
	class Circle3D : public Primitive3D {
	private:
		void _CalcVertexes() {
			Point3D pos = this->GetPosition();

			for (int i = 0; i < precision; i++) {
				double ang = 2.0 * PI * double(i) / double(precision),
					z = radius * cosf(ang),
					x = radius * sinf(ang);
				AddVertex(Point3D(x + pos.GetX(), pos.GetY(), z + pos.GetZ()));
			}
		}
	protected:
		double radius;
		int precision;
	public:
		Circle3D() {
            SetType(GL_POLYGON);
		}

		Circle3D(double radius, int precision) {
            SetType(GL_POLYGON);
			this->radius = radius;
			this->precision = precision;

			_CalcVertexes();
		}

		~Circle3D() {
		}

		double GetRadius() {
			return radius;
		}

		int GetPrecision() {
			return precision;
		}

		Circle3D& SetRadius(double radius) {
			this->radius = radius;

			return *this;
		}

		Circle3D& SetPrecision(int precision) {
			this->precision = precision;

			return *this;
		}
	};
}

#endif
