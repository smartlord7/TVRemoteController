#ifndef TVREMOTECONTROLLER_SPINNER
#define TVREMOTECONTROLLER_SPINNER

class Spinner {
private:
	double velocity;
	double angle;
	bool spinning;


public:
	static constexpr double SPINNER_INIT_VELOCITY = 10.0;
	static constexpr double	SPINNER_INIT_ANGLE = 0.0;

	Spinner() {
		velocity = SPINNER_INIT_VELOCITY;
		angle = SPINNER_INIT_ANGLE;
	}

	double GetVelocity() {
		return velocity;
	}

	double GetAngle() {
		return angle;
	}

	double IsSpinning() {
		return spinning;
	}

	Spinner& SetVelocity(double velocity) {
		this->velocity = velocity;

		return *this;
	}

	void Start() {
		this->spinning = true;
	}

	void Spin(double time) {
		if (spinning) {
			this->angle += (double)((int)((time * velocity)) % 360);
		}
	}

	void Stop() {
		this->spinning = false;
	}

};


#endif //TVREMOTECONTROLLER_SPINNER
