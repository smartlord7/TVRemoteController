#include "WorldState.h"
#include "Observer.cpp"

using namespace EasyGL;

class WorldState {
private:
	OpenGL openGL = OpenGL();
	Observer observer;

public:
	WorldState() {
	}

	~WorldState() {
	}

	Observer GetObserver() {
		return observer;
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
