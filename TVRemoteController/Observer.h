#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include "Vector3D.h"
#include "OpenGL.h"
#include "Point3D.h"
#include "ObserverEnum.h"

#define DEBUG 0

using namespace std;

namespace EasyGL {
	class Observer {
	private:
		OpenGL gl;
		double fieldOfVision;
		double	aspect;
		double	minRenderDist;
		double	maxRenderDist;
		double minX;
		double maxX;
		double minY;
		double maxY;
		double minZ;
		double maxZ;
		int moveTargetFactorsIndex;
		int movePositionFactorsIndex;
		ObserverEnum targetState;
		ObserverEnum positionState;
		Point3D position, target;
		Vector3D upAxis;
		static constexpr double OBS_INIT_FOV = 45.0,
			OBS_INIT_MIN_RENDER_DIST = 0.1,
			OBS_INIT_MAX_RENDER_DIST = 40.0,
			OBS_WALK_STEP = 1.0,
			OBS_CAMERA_STEP = 1.0,
			OBS_FLY_STEP = 1.0,
			OBS_DEFAULT_MIN_X = -10 + 1,
			OBS_DEFAULT_MAX_X = 10 - 1,
			OBS_DEFAULT_MIN_Y = 2,
			OBS_DEFAULT_MAX_Y = 10,
			OBS_DEFAULT_MIN_Z = -10 - 1,
			OBS_DEFAULT_MAX_Z = 15;
		vector<double> MOVE_TARGET_FACTORS;
		vector<double> MOVE_POSITION_FACTORS;

		void _Init() {
			positionState = OBSERVER_STATIC;
			targetState = CAMERA_STATIC;
			movePositionFactorsIndex = 0;
			moveTargetFactorsIndex = 0;
			_GeneratePositionTargetFactors();
			_GenerateMoveTargetFactors();
		}

		void _GenerateMoveTargetFactors() {
			int max = 1 / 0.05;
			int i = 0;

			while (i < max) {
				MOVE_TARGET_FACTORS.push_back(0.05);

				i++;
			}
		}

		void _GeneratePositionTargetFactors() {
			int max = 1 / 0.05;
			int i = 0;

			while (i < max) {
				MOVE_POSITION_FACTORS.push_back(0.05);

				i++;
			}
		}
	public:
        Point3D ORIGIN = Point3D(0.0, 0.0, 0.0),
                OBS_INIT_POS = Point3D(0.0, 3.0, 8),
                OBS_INIT_TARGET = Point3D(0.0, 1.0, 0.0);
        Vector3D OBS_INIT_UP_AXIS = Vector3D(0.0, 1.0, 0.0),
                X_AXIS = Vector3D(1.0, 0.0, 0.0),
                Y_AXIS = Vector3D(0.0, 1.0, 0.0),
                Z_AXIS = Vector3D(1.0, 0.0, 1.0);

		Observer() {
			_Init();
		}

		Observer(double aspect) {
			_Init();
			this->fieldOfVision = OBS_INIT_FOV;
			this->aspect = aspect;
			this->minRenderDist = OBS_INIT_MIN_RENDER_DIST;
			this->maxRenderDist = OBS_INIT_MAX_RENDER_DIST;
			this->position = OBS_INIT_POS;
			this->target = OBS_INIT_TARGET;
			this->upAxis = OBS_INIT_UP_AXIS;
			this->minX = OBS_DEFAULT_MIN_X;
			this->maxX = OBS_DEFAULT_MAX_X;
			this->minY = OBS_DEFAULT_MIN_Y;
			this->maxY = OBS_DEFAULT_MAX_Y;
			this->minZ = OBS_DEFAULT_MIN_Z;
			this->maxZ = OBS_DEFAULT_MAX_Z;
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

		Observer& UpdateObsLookAt() {
			Point3D pos = this->position,
				tgt = this->target;
			Vector3D up = this->upAxis;

			gl.SetMatrixMode(GL_MODELVIEW)
				.ResetMatrix()
				.LookAt(pos.GetX(), pos.GetY(), pos.GetZ(), tgt.GetX(), tgt.GetY(), tgt.GetZ(), up.GetX(), up.GetY(), up.GetZ());

			return *this;
		}

		Observer& UpdateObsPerspective() {
			gl.SetMatrixMode(GL_PROJECTION)
				.ResetMatrix()
				.SetPerspective(fieldOfVision, aspect, minRenderDist, maxRenderDist);

			return *this;
		}

		bool _PointViolatesConstraints(Point3D point) {
			double x, y, z;

			x = point.GetX();
			y = point.GetY();
			z = point.GetZ();

			return !(minX <= x && x <= maxX && minY <= y && y <= maxY && minZ <= z && z <= maxZ);
		}

		Observer& Move(ObserverEnum positionState) {
			this->positionState = positionState;

			return *this;
		}

		Observer& UpdatePosition() {
			double factor;

			if (positionState != OBSERVER_STATIC) {
				factor = MOVE_TARGET_FACTORS[movePositionFactorsIndex++];

				if (positionState == FLY_UP || positionState == FLY_DOWN) {
					double y;
					double dist;

					dist = OBS_FLY_STEP * factor;

					y = positionState == FLY_UP ? position.GetY() + dist : position.GetY() - dist;

					if (minY <= y && y <= maxY) {
						position.SetY(positionState == FLY_UP ? position.GetY() + dist : position.GetY() - dist);
						target.SetY(positionState == FLY_UP ? target.GetY() + dist : target.GetY() - dist);
					}
				} else {
					Vector3D eyeVector, walkVector, sideAxis;
					Point3D newPos;
					double lengthEyeVector, lengthWalkVector;
					eyeVector = target - position;

					if (positionState == WALK_FRONT || positionState == WALK_BACK) {
						lengthEyeVector = eyeVector.GetLength();

						if (positionState == WALK_FRONT && lengthEyeVector < OBS_WALK_STEP) {
							lengthWalkVector = lengthEyeVector;
						} else {
							lengthWalkVector = OBS_WALK_STEP;
						}

						walkVector = eyeVector * (lengthWalkVector / lengthEyeVector) * factor;
						newPos = positionState == WALK_FRONT ? position + walkVector : position + (-walkVector);

						if (!_PointViolatesConstraints(newPos)) {
							SetPosition(newPos);
							SetTarget(positionState == WALK_FRONT ? target + walkVector : target + (-walkVector));
						}
					} else if (positionState == WALK_LEFT || positionState == WALK_RIGHT) {
						sideAxis = positionState == WALK_LEFT ? -eyeVector.CrossProduct(upAxis) : eyeVector.CrossProduct(upAxis);
						sideAxis.Normalize();

						walkVector = sideAxis * OBS_WALK_STEP * factor;
						newPos = position + walkVector;

						if (!_PointViolatesConstraints(newPos)) {
							SetPosition(newPos)
								.SetTarget(target + walkVector);
						}
					}

#if DEBUG
					cout << position.GetX() << ", " << position.GetY() << ", " << position.GetZ() << "\n";
					cout << target.GetX() << ", " << target.GetY() << ", " << target.GetZ() << "\n\n";
#endif
				}

				UpdateObsLookAt();

				if (movePositionFactorsIndex == MOVE_POSITION_FACTORS.size()) {
					movePositionFactorsIndex = 0;
					positionState = OBSERVER_STATIC;
				}
			}

		    return *this;
		}

		Observer& RotateCamera(ObserverEnum targetState) {
			this->targetState = targetState;

            return *this;
        }

		Observer& UpdateCamera() {
			if (targetState != CAMERA_STATIC) {
				Point3D	nextTgt = this->target;
				Point3D pos = this->position;
				Point3D	tgt = this->target;
				Vector3D up = this->upAxis;
				Vector3D tgtVector;
				double factor;

				gl.SetMatrixMode(GL_MODELVIEW)
				  .ResetMatrix();

				factor = MOVE_TARGET_FACTORS[moveTargetFactorsIndex++];

				switch (targetState) {
					case CAMERA_LEFT:
						target.SetX(tgt.GetX() - OBS_CAMERA_STEP * factor);
						break;
					case CAMERA_RIGHT:
						target.SetX(tgt.GetX() + OBS_CAMERA_STEP * factor);
						break;
					case CAMERA_DOWN:
						target.SetY(tgt.GetY() - OBS_CAMERA_STEP * factor);
						break;
					case CAMERA_UP:
						target.SetY(tgt.GetY() + OBS_CAMERA_STEP * factor);
						break;
					default:
						break;
				}

				UpdateObsLookAt();

				if (moveTargetFactorsIndex == MOVE_TARGET_FACTORS.size()) {
					moveTargetFactorsIndex = 0;
					targetState = CAMERA_STATIC;
				}

			}
				return *this;
		}
	};
}

#endif