#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>

namespace Geometry {
	class Vector3D {
	private:
		double x, y, z;
	public:
		Vector3D() {
		}

		Vector3D(double x, double y, double z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		~Vector3D() {
		}

		double GetX() {
			return x;
		}

		double GetY() {
			return y;
		}

		double GetZ() {
			return z;
		}

		Vector3D& SetX(double x) {
			this->x = x;

			return *this;
		}

		Vector3D& SetY(double y) {
			this->y = y;

			return *this;
		}

		Vector3D& SetZ(double z) {
			this->z = z;

			return *this;
		}

		double GetLength() {
			return sqrt(x * x + y * y + z * z);
		}

		Vector3D& Normalize() {
			double length = GetLength();
			this->x = x / length;
			this->y = y / length;
			this->z = z / length;

			return *this;
		}
	};
}

#endif VECTOR3D_H