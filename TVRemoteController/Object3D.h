#include <vector>

using namespace std;

namespace Geometry {
	class Object3D {
	private:
		vector<Primitive3D> primitives;
	protected:
		Color color, borderColor = Color(-1, -1, -1, -1);
	public:
		Object3D() {
		}

		~Object3D() {
		}

		Color GetColor() {
			return color;
		}

		Color GetBorderColor() {
			return borderColor;
		}

		Object3D& SetColor(Color color) {
			this->color = color;

			return *this;
		}

		Object3D& SetBorderColor(Color borderColor) {
			this->borderColor = color;

			return *this;
		}

		vector<Primitive3D> GetPrimitives() {
			return primitives;
		}

		Object3D& AddPrimitive(Primitive3D primitive) {
			primitives.push_back(primitive);

			return *this;
		}
	};
}
