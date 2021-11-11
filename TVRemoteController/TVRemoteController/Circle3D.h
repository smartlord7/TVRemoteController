#ifndef CIRCLE3D_H
#define CIRCLE3D_H

#include "Object3D.h"
#include "Math.h"

namespace EasyGL {
	class Circle3D : public Object3D {
	private:
		double radius;
		int precision;

		void _CalcVertexes() {
			Point3D pos = this->GetPosition();

			for (int i = 0; i < precision; i++) {
				double ang = 2.0 * PI * double(i) / double(precision),
					z = radius * cosf(ang),
					x = radius * sinf(ang);
				this->AddVertex(Point3D(x + pos.GetX(), pos.GetY(), z + pos.GetZ()));
			}
		}
	public:
		Circle3D() {
		}

		Circle3D(double radius, int precision) {
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
		}

		Circle3D& SetPrecision(int precision) {
			this->precision = precision;
		}
	};
}

#endif CIRCLE3D_H
