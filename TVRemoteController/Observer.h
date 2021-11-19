#ifndef OBSERVER_H
#define OBSERVER_H

#include "Vector3D.h"
#include "OpenGL.h"
#include "Point3D.h"
#include "ObserverEnum.h"

#define DEBUG

namespace EasyGL {
	class Observer {
	private:
		OpenGL gl;
		double fieldOfVision,
			aspect,
			minRenderDist,
			maxRenderDist;
		Point3D position, target;
		Vector3D upAxis;
	public:
	    static constexpr double OBS_INIT_FOV = 45.0,
                OBS_INIT_MIN_RENDER_DIST = 0.1,
                OBS_INIT_MAX_RENDER_DIST = 40.0,
                OBS_WALK_STEP = 0.05,
                OBS_CAMERA_STEP = 0.2,
                OBS_FLY_STEP = 0.05;
        Point3D ORIGIN = Point3D(0.0, 0.0, 0.0),
                OBS_INIT_POS = Point3D(0.5, 0.85, -4.65),
                OBS_INIT_TARGET = Point3D(0.5, 0.85, 1.05);
        Vector3D OBS_INIT_UP_AXIS = Vector3D(0.0, 1.0, 0.0),
                X_AXIS = Vector3D(1.0, 0.0, 0.0),
                Y_AXIS = Vector3D(0.0, 1.0, 0.0),
                Z_AXIS = Vector3D(1.0, 0.0, 1.0);

		Observer() {
		}

		Observer(double aspect) {
			this->fieldOfVision = OBS_INIT_FOV;
			this->aspect = aspect;
			this->minRenderDist = OBS_INIT_MIN_RENDER_DIST;
			this->maxRenderDist = OBS_INIT_MAX_RENDER_DIST;
			this->position = OBS_INIT_POS;
			this->target = OBS_INIT_TARGET;
			this->upAxis = OBS_INIT_UP_AXIS;
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

			return *this;
		}

		Observer& SetAspect(double aspect) {
			this->aspect = aspect;

			UpdateObsPerspective();

            return *this;
		}

		Observer& SetMinRenderDist(double minRenderDist) {
			this->minRenderDist = minRenderDist;

			UpdateObsPerspective();

            return *this;
		}

		Observer& SetMaxRenderDist(double maxRenderDist) {
			this->maxRenderDist = maxRenderDist;

			UpdateObsPerspective();

            return *this;
		}

		Observer& SetPosition(Point3D position) {
			this->position = position;

            return *this;
		}

		Observer& SetTarget(Point3D target) {
			this->target = target;

            return *this;
		}

		Observer& SetUpAxis(Vector3D SetUpAxis) {
			this->upAxis = SetUpAxis;

			UpdateObsLookAt();

            return *this;
		}

		Observer& UpdateObsPerspective() {
			gl.SetMatrixMode(GL_PROJECTION)
				.ResetMatrix()
				.SetPerspective(fieldOfVision, aspect, minRenderDist, maxRenderDist);

			return *this;
		}

		Observer& UpdateObsLookAt() {
			Point3D pos = this->position,
				tgt = this->target;
			Vector3D up = this->upAxis;

			gl.SetMatrixMode(GL_MODELVIEW)
				.ResetMatrix()
				.LookAt(pos.GetX(), pos.GetY(), pos.GetZ(), tgt.GetX(), tgt.GetY(), tgt.GetZ(), up.GetX(), up.GetY(), up.GetZ());

            return *this;
		}

		Observer& MoveVertically(ObserverEnum flyDirection) {
            position.SetY(flyDirection == FLY_UP ? position.GetY() + OBS_FLY_STEP : position.GetY() - OBS_FLY_STEP);
            target.SetY(flyDirection == FLY_UP ? target.GetY() + OBS_FLY_STEP : target.GetY() - OBS_FLY_STEP);

            UpdateObsLookAt();

		    return *this;
		}

		Observer& MoveHorizontally(ObserverEnum walkDirection) {
            Vector3D eyeVector, walkVector, sideAxis;
            double lengthEyeVector, lengthWalkVector;
            eyeVector = target - position;

            if (walkDirection == WALK_FRONT || walkDirection == WALK_BACK) {
                lengthEyeVector = eyeVector.GetLength();

                if (walkDirection == WALK_FRONT && lengthEyeVector < OBS_WALK_STEP) {
                    lengthWalkVector = lengthEyeVector;
                } else {
                    lengthWalkVector = OBS_WALK_STEP;
                }

                walkVector = eyeVector * (lengthWalkVector / lengthEyeVector);

                SetPosition(walkDirection == WALK_FRONT ? position + walkVector : position + (-walkVector));
                if (walkDirection == WALK_FRONT) {
                    SetTarget(target + walkVector);
                }
            } else if (walkDirection == WALK_LEFT || walkDirection == WALK_RIGHT) {
                sideAxis = walkDirection == WALK_LEFT ? -eyeVector.CrossProduct(upAxis) : eyeVector.CrossProduct(upAxis);
                sideAxis.Normalize();

                walkVector = sideAxis * OBS_WALK_STEP;

                SetPosition(position + walkVector)
                    .SetTarget(target + walkVector);
            }

            UpdateObsLookAt();

            #ifdef DEBUG
            cout << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << "\n";
            cout << target.GetX() << ", " << target.GetY() << ", " << target.GetZ() << "\n\n";
            return *this;
            #endif

		}

		Observer& MoveCamera(ObserverEnum cameraDirection) {
		    /*Point3D newTarget;
            Vector3D eyeVector, rightAxis;
            double lengthEyeVector, currAngle, nextAngle;*/
            switch (cameraDirection) {

                case CAMERA_LEFT:
                    target.SetX(target.GetX() + OBS_CAMERA_STEP);
                    break;
                case CAMERA_RIGHT:
                    target.SetX(target.GetX() - OBS_CAMERA_STEP);
                    break;
                case CAMERA_DOWN:
                    target.SetY(target.GetY() - OBS_CAMERA_STEP);
                    break;
                case CAMERA_UP:
                    target.SetY(target.GetY() + OBS_CAMERA_STEP);
                    break;
            }

            /*if (cameraDirection == CAMERA_LEFT || cameraDirection == CAMERA_RIGHT) {
                eyeVector = target - position;
                lengthEyeVector = eyeVector.GetLength();

                currAngle = acos((eyeVector * X_AXIS) / (lengthEyeVector * X_AXIS.GetLength()));
                nextAngle = cameraDirection == CAMERA_LEFT ? currAngle + OBS_CAMERA_STEP : currAngle - OBS_CAMERA_STEP;
                newTarget = Point3D(position.GetX() + lengthEyeVector * cos(nextAngle),
                                    target.GetY(),
                                    position.GetZ() + lengthEyeVector * sin(nextAngle));
                SetTarget(newTarget);
                UpdateObsLookAt();
            }*/

            UpdateObsLookAt();

            return *this;
        }
	};
}

#endif