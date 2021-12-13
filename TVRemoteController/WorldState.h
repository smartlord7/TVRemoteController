#ifndef WORLD_STATE_H
#define WORLD_STATE_H

#include "Observer.h"
#include "Spinner.h"
#include "Button.h"
#include "Controller.h"
#include "Television.h"
#include "Grid.h"

using namespace EasyGL;

class WorldState {
private:
	OpenGL openGL = OpenGL();
	Observer observer;
	Spinner ACfan;
	Controller ctrl;
	Television tel;
	Grid grid;

public:
	static constexpr double DEFAULT_GRID_SIDE = 1.0;

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

	Grid& GetGrid() {
		return grid;
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
