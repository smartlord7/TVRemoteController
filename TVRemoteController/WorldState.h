#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include "Observer.h"
#include "Spinner.h"
#include "Button.h"
#include "Controller.h"
#include "Television.h"

using namespace EasyGL;

class WorldState {
private:
	OpenGL openGL = OpenGL();
	Observer observer;
	Spinner ACfan;
	Controller ctrl;
	Television tel;

public:
	WorldState() {
	}

	~WorldState() {
	}

	Observer& GetObserver() {
		return observer;
	}

	Spinner& GetFan() {
		return ACfan;
	}

	Controller& GetController() {
		return ctrl;
	}

	Television& GetTelevision() {
		return tel;
	}

	OpenGL GetOpenGL() {
		return openGL;
	}

	WorldState& SetObserver(Observer observer) {
		this->observer = observer;

		observer.UpdateObsPerspective()
			.UpdateObsLookAt();

		return *this;
	}
};

#endif
