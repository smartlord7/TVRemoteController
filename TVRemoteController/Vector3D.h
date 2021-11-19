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

        Vector3D operator- () const{
            return Vector3D(-x, -y, -z);
        }

        Vector3D operator* (double multFac) const {
            return Vector3D(x * multFac, y * multFac, z * multFac);
        }

		Vector3D operator/(double divFac) {
            Vector3D v = * this;
            v = v * (1.0 / divFac);

            return v;
		}

        Vector3D& operator=(Vector3D other) {
            this->x = other.GetX();
            this->y = other.GetY();
            this->z = other.GetZ();

            return *this;
        }

        double operator* (Vector3D other) {
            return x * other.GetX() + y * other.GetY() + z * other.GetZ();
        }

        Vector3D CrossProduct(Vector3D other) {
            return Vector3D(y * other.GetZ() - z * other.GetY(), x * other.GetZ() - z * other.GetX(), x * other.GetY() - y * other.GetX());
        }

		Vector3D& Normalize() {
            *this = *this / GetLength();

			return *this;
		}
    };
}

#endif