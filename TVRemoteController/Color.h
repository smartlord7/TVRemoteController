#ifndef COLOR_H
#define COLOR_H

namespace ColorTexture {
	class Color {
	private:
		double r, g, b, a;
	public:
		Color() {
		}

		Color(double r, double g, double b, double a) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		~Color() {
		}

		double GetRed() {
			return r;
		}

		double GetGreen() {
			return g;
		}

		double GetBlue() {
			return b;
		}

		double GetAlpha() {
			return a;
		}

		Color& SetRed(double r) {
			this->r = r;

			return *this;
		}

		Color& SetGreen(double g) {
			this->g = g;

			return *this;
		}

		Color& SetBlue(double b) {
			this->b = b;

			return *this;
		}

		Color& SetAlpha(float A) {
			this->a = a;

			return *this;
		}

		bool IsValid() {
			return r >= 0 && g >= 0 && b >= 0 && a >= 0;
		}
	};
}

#endif