#ifndef EASY_GL_H
#define EASY_GL_H

#include <string>
#include "Vector3D.h"
using namespace std;

namespace Geometry {
	class Point3D {
	private:
		double x, y, z;
	public:
		Point3D() {
		}

		Point3D(double x, double y, double z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		~Point3D() {
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

		Point3D& SetX(double x) {
			this->x = x;

			return *this;
		}

		Point3D& SetY(double y) {
			this->y = y;

			return *this;
		}

		Point3D& SetZ(double z) {
			this->z = z;

			return *this;
		}

		Vector3D operator-(Point3D pos) {
		    return Vector3D(x - pos.GetX(), y - pos.GetY(), z - pos.GetZ());
		}

        Point3D operator+(Vector3D vector) {
            return Point3D(x + vector.GetX(), y + vector.GetY(), z + vector.GetZ());
        }

        Point3D& operator=(Point3D other) {
		    this->x = other.GetX();
		    this->y = other.GetY();
		    this->z = other.GetZ();

		    return *this;
		}
	};
}

#endif