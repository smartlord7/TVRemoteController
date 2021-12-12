#ifndef TVREMOTECONTROLLER_SPINNER
#define TVREMOTECONTROLLER_SPINNER

class Spinner {
private:
	double velocity;
	double maxVelocity;
	double angle;
	bool spinning;


public:
	static constexpr double SPINNER_INIT_VELOCITY = 10.0;
	static constexpr double SPINNER_DEFAULT_VELOCITY_STEP = 1.0;
	static constexpr double SPINNER_DEFAULT_MAX_VELOCITY = 50.0;
	static constexpr double	SPINNER_INIT_ANGLE = 0.0;

	Spinner() {
		velocity = SPINNER_INIT_VELOCITY;
		maxVelocity = SPINNER_DEFAULT_MAX_VELOCITY;
		angle = SPINNER_INIT_ANGLE;
	}

	double GetVelocity() {
		return velocity;
	}

	double GetMaxVelocity() {
		return maxVelocity;
	}

	double GetAngle() {
		return angle;
	}

	double IsSpinning() {
		return spinning;
	}

	Spinner& SetVelocity(double velocity) {
		if (velocity <= maxVelocity && spinning) {
			this->velocity = velocity;
		}

		return *this;
	}

	Spinner& IncVelocity() {
		if (spinning) {
			double nextVel = velocity + SPINNER_DEFAULT_VELOCITY_STEP;

			if (nextVel <= maxVelocity) {
				velocity = nextVel;
			}
		}

		return *this;
	}

	Spinner& DecVelocity() {
		if (spinning) {
			double nextVel = velocity - SPINNER_DEFAULT_VELOCITY_STEP;

			if (nextVel > 0) {
				velocity = nextVel;
			} else {
				velocity = 0;
			}
		}

		return *this;
	}

	Spinner& SetMaxVelocity(double maxVelocity) {
		this->maxVelocity = maxVelocity;

		return *this;
	}

	void StartStop() {
		this->spinning = !spinning;
	}

	void Spin(double time) {
		if (spinning) {
			this->angle += (double)((int)((time * velocity)) % 360);
		}
	}
};


#endif //TVREMOTECONTROLLER_SPINNER
