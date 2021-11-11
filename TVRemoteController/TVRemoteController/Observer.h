#ifndef OBSERVER_H
#define OBSERVER_H

#include "Vector3D.h"
#include "OpenGL.h"

namespace EasyGL {
	class Observer {
	private:
		OpenGL openGL;
		double fieldOfVision,
			aspect,
			minRenderDist,
			maxRenderDist;
		Point3D position, target;
		Vector3D upAxis;
	public:
		Observer() {
		}

		Observer(double fieldOfVision, double aspect, double minRenderDist, double maxRenderDist, Point3D position, Point3D target, Vector3D upAxis) {
			this->fieldOfVision = fieldOfVision;
			this->aspect = aspect;
			this->minRenderDist = minRenderDist;
			this->maxRenderDist = maxRenderDist;
			this->position = position;
			this->target = target;
			this->upAxis = upAxis;
		}

		double GetFieldOfVision() {
			return fieldOfVision;
		}

		double GetAspect() {
			return aspect;
		}

		double GetMinRenderDist() {
			return minRenderDist;
		}

		double GetMaxRenderDist() {
			return maxRenderDist;
		}

		Point3D GetPosition() {
			return position;
		}

		Point3D GetTarget() {
			return target;
		}

		Vector3D GetUpAxis() {
			return upAxis;
		}

		Observer& SetFieldOfVision(double fieldOfVision) {
			this->fieldOfVision = fieldOfVision;

			UpdateObsPerspective();
		}

		Observer& SetAspect(double aspect) {
			this->aspect = aspect;

			UpdateObsPerspective();
		}

		Observer& SetMinRenderDist(double minRenderDist) {
			this->minRenderDist = minRenderDist;

			UpdateObsPerspective();
		}

		Observer& SetMaxRenderDist(double maxRenderDist) {
			this->maxRenderDist = maxRenderDist;

			UpdateObsPerspective();
		}

		Observer& SetPosition(Point3D position) {
			this->position = position;

			UpdateObsLookAt();
		}

		Observer& SetTarget(Point3D target) {
			this->target = target;

			UpdateObsLookAt();
		}

		Observer& SetUpAxis(Vector3D SetUpAxis) {
			this->upAxis = SetUpAxis;

			UpdateObsLookAt();
		}

		Observer& UpdateObsPerspective() {
			openGL.SetMatrixMode(GL_PROJECTION)
				.ResetMatrix()
				.SetPerspective(this->fieldOfVision, this->aspect, this->minRenderDist, this->maxRenderDist);

			return *this;
		}

		Observer& UpdateObsLookAt() {
			Point3D pos = this->position,
				target = this->target;
			Vector3D up = this->upAxis;

			openGL.SetMatrixMode(GL_MODELVIEW)
				.ResetMatrix()
				.LookAt(pos.GetX(), pos.GetY(), pos.GetZ(), target.GetX(), target.GetY(), target.GetZ(), up.GetX(), up.GetY(), up.GetZ());

			return *this;
		}
	};
}

#endif OBSERVER_H