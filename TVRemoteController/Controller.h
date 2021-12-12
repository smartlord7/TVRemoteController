#ifndef TVREMOTECONTROLLER_CONTROLLER
#define TVREMOTECONTROLLER_CONTROLLER

#include "Button.h"
#include <vector>
#include <set>

using namespace std;

class Controller {
private:
	vector<Button> buttons;
	int selectedButton;
	int latestPressedButton;
	int rows;
	int cols;
	double spinnerAngle;

public:
	const double DEFAULT_CONTROLLER_SPIN_ANGLE_STEP = 3.0;

	Controller() {
	}

	~Controller() {
	}

	vector<Button>& GetButtons() {
		return buttons;
	}

	int GetSelectedButton() {
		return selectedButton;
	}

	int GetRows() {
		return rows;
	}

	int GetCols() {
		return cols;
	}

	double GetSpinnerAngle() {
		return spinnerAngle;
	}

	Controller& InitButtons(int rows, int cols, vector<string> labels) {
		this->rows = rows;
		this->cols = cols;
		for (int i = 0; i < rows * cols; i++) {
			buttons.push_back(Button(i, labels[i]));
		}

		return *this;
	}

	Controller& PressSelectedButton() {
		buttons[selectedButton].Press();
		buttons[selectedButton].SetHandled(false);
		latestPressedButton = selectedButton;

		return *this;
	}

	Controller& SetSelectedButton(int selectedButton) {
		this->selectedButton = selectedButton;

		return *this;
	}

	Controller& UpdateController(double time) {
		int i = 0;

		for (; i < buttons.size(); i++) {
			buttons[i].Update(time);
		}

		return *this;
	}

	Controller& IncSpinnerAngle() {
		double nextAngle = spinnerAngle + DEFAULT_CONTROLLER_SPIN_ANGLE_STEP;

		if (nextAngle <= 360.0) {
			spinnerAngle = nextAngle;
		}

		return *this;
	}

	Controller& DecSpinnerAngle() {
		double nextAngle = spinnerAngle - DEFAULT_CONTROLLER_SPIN_ANGLE_STEP;

		if (nextAngle >= 0) {
			spinnerAngle = nextAngle;
		}

		return *this;
	}
};
#endif
