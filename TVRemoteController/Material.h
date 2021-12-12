#ifndef TVREMOTECONTROLLER_MATERIAL_H
#define TVREMOTECONTROLLER_MATERIAL_H

#include "Color.h"
#include "GL/glut.h"

class Material {
private:
	Color ambientLight;
	Color diffuseLight;
	Color specularLight;
	double coef;
public:
	Material() {
	}

	Material(Color ambientLight, Color diffuseLight, Color specularLight, double coef) {
		this->ambientLight = ambientLight;
		this->diffuseLight = diffuseLight;
		this->specularLight = specularLight;
		this->coef = coef;
	}

	~Material() {
	}

	Color GetAmbientLight() {
		return ambientLight;
	}

	Color GetDiffuseLight() {
		return ambientLight;
	}

	Color GetSpecularLight() {
		return ambientLight;
	}

	double GetCoef() {
		return coef;
	}

	Material& SetAmbientLight(Color ambientLight) {
		this->ambientLight = ambientLight;

		return *this;
	}

	Material& SetDiffuseLight(Color diffuseLight) {
		this->diffuseLight = diffuseLight;

		return *this;
	}

	Material& SetSpecularLight(Color specularLight) {
		this->specularLight = specularLight;

		return *this;
	}

	Material& SetCoef(double coef) {
		this->coef = coef;

		return *this;
	}

	static void BindMaterial(Material mat, unsigned int face = GL_FRONT) {
		Color amb, diff, spec;

		amb = mat.GetAmbientLight();
		diff = mat.GetDiffuseLight();
		spec = mat.GetSpecularLight();

		float ambV[3] = { (float) amb.GetRed(), (float) amb.GetGreen(), (float)amb.GetBlue() };
		float diffV[3] = { (float) diff.GetRed(),  (float) diff.GetGreen(), (float) diff.GetBlue() };
		float specV[3] = { (float)spec.GetRed(),  (float) spec.GetGreen(), (float) spec.GetBlue() };

		glMaterialfv(face, GL_AMBIENT, ambV);
		glMaterialfv(face, GL_DIFFUSE, diffV);
		glMaterialfv(face, GL_SPECULAR, specV);
		glMaterialf(face, GL_SHININESS, mat.GetCoef());
	}
};

#endif //TVREMOTECONTROLLER_MATERIAL_H
