#ifndef EASY_GL_H
#define EASY_GL_H

namespace EasyGL {
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
	};
}

#endif EASY_GL_H