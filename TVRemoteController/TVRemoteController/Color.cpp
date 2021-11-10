#include "Color.h"

namespace EasyGL {
	class Color {
	private:
		float r, g, b, a;
	public:
		Color() {
		}

		Color(float r, float g, float b, float a) {
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		~Color() {
		}

		float GetRed() {
			return r;
		}

		float GetGreen() {
			return g;
		}

		float GetBlue() {
			return b;
		}

		float GetAlpha() {
			return a;
		}

		Color& SetRed(float r) {
			this->r = r;

			return *this;
		}

		Color& SetGreen(float g) {
			this->g = g;

			return *this;
		}

		Color& SetBlue(float b) {
			this->b = b;

			return *this;
		}

		Color& SetAlpha(float A) {
			this->a = a;

			return *this;
		}
	};
}