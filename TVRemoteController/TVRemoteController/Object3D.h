#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <vector>
#include <stdexcept>
#include "Point3D.h"
#include "Color.h"

using namespace std;

namespace EasyGL {
	class Object3D {
	private:
		vector<Point3D> vertexes;
		Point3D position = Point3D(0, 0, 0);
		Color color, borderColor = Color(-1, -1, -1, -1);
	public:
		Object3D() {
		}

		Object3D(vector<Point3D> vertexes) {
			this->vertexes = vertexes;
		}

		Object3D(vector<double> vertexesCoords) {
			SetVertexes(vertexesCoords);
		}

		vector<Point3D> GetVertexes() {
			return vertexes;
		}

		Point3D GetPosition() {
			return position;
		}

		Color GetColor() {
			return color;
		}

		Color GetBorderColor() {
			return borderColor;
		}

		int GetNumVertexes() {
			return vertexes.size();
		}

		Object3D& SetVertexes(vector<double> vertexesCoords) {
			if (vertexesCoords.size() % 3 != 0) {
				throw invalid_argument("Number of vertexes coordinates must be a multiple of 3! (3 dimensions)");
			}

			for (size_t i = 0; i < vertexesCoords.size(); i += 3) {
				vertexes.push_back(Point3D(vertexesCoords[0], vertexesCoords[1], vertexesCoords[2]));
			}
		}

		Object3D& SetPosition(Point3D position) {
			this->position = position;
		}

		Object3D& SetColor(Color color) {
			this->color = color;
		}

		Object3D& SetBorderColor(Color borderColor) {
			this->borderColor = color;
		}

		Object3D& AddVertex(Point3D vertex) {
			vertexes.push_back(vertex);
		}

	};
}

#endif OBJECT3D_H