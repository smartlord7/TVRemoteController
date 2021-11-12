#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include "Observer.h"

using namespace EasyGL;

class WorldState {
private:
	OpenGL openGL = OpenGL();
	Observer observer;
	double controllerYAngle, controllerZAngle, buttonYPos;
	int buttonPressIterations, buttonState;

public:
	WorldState() {
	}

	~WorldState() {
	}

	Observer& GetObserver() {
		return observer;
	}

	OpenGL GetOpenGL() {
		return openGL;
	}

	int GetButtonState() {
	    return buttonState;
	}

	WorldState& SetButtonState(int buttonState) {
	    this->buttonState = buttonState;

	    return *this;
	}

	double GetButtonYPos() {
	    return buttonYPos;
	}

	WorldState& SetButtonYPos(double buttonYPos) {
	    this->buttonYPos = buttonYPos;

	    return *this;
	}

	int GetButtonPressIterations() {
	    return buttonPressIterations;
	}

	WorldState& SetButtonPressIterations(int buttonPressIterations) {
	    this->buttonPressIterations = buttonPressIterations;

	    return *this;
	}

	double GetControllerYAngle() {
	    return controllerYAngle;
	}

	WorldState& SetControllerYAngle(double controllerYAngle) {
	    this->controllerYAngle = controllerYAngle;

        return *this;
	}

    double GetControllerZAngle() {
        return controllerZAngle;
    }

    WorldState& SetControllerZAngle(double controllerZAngle) {
        this->controllerZAngle = controllerZAngle;

        return *this;
    }

	WorldState& SetObserver(Observer observer) {
		this->observer = observer;

		observer.UpdateObsPerspective()
			.UpdateObsLookAt();

		return *this;
	}
};

#endif
