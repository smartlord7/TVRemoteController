#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <vector>
#include <stdexcept>
#include "Point3D.h"
#include "Color.h"
#include <GL/glut.h>

using namespace std;
using namespace ColorTexture;

namespace Geometry {
	class Primitive3D {
	private:
		GLenum type;
		Point3D position = Point3D(0, 0, 0);
		Color color, borderColor = Color(-1, -1, -1, -1);
	protected:
		vector<Point3D> vertexes;
	public:
		Primitive3D() {
		}

		Primitive3D(GLenum type) {
			this->type = type;
		}

		Primitive3D(vector<Point3D> vertexes) {
			this->vertexes = vertexes;
		}

		Primitive3D(vector<double> vertexesCoords) {
			SetVertexes(vertexesCoords);
		}

		GLenum GetType() {
			return type;
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

		Primitive3D& SetType(GLenum type) {
			this->type = type;

			return *this;
		}

		Primitive3D& SetVertexes(vector<double> vertexesCoords) {
			if (vertexesCoords.size() % 3 != 0) {
				throw invalid_argument("Number of vertexes coordinates must be a multiple of 3! (3 dimensions)");
			}

			for (size_t i = 0; i < vertexesCoords.size(); i += 3) {
				vertexes.push_back(Point3D(vertexesCoords[0], vertexesCoords[1], vertexesCoords[2]));
			}
		}

		Primitive3D& SetPosition(Point3D position) {
			this->position = position;

			return *this;
		}

		Primitive3D& SetColor(Color color) {
			this->color = color;

			return *this;
		}

		Primitive3D& SetBorderColor(Color borderColor) {
			this->borderColor = color;

			return *this;
		}

		Primitive3D& AddVertex(Point3D vertex) {
			vertexes.push_back(vertex);

			return *this;
		}
	};
}

#endif
