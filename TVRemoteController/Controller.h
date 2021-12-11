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
	set<int> pressedButtons;
	int latestPressedButton;
	int rows;
	int cols;

public:
	Controller() {
	}

	~Controller() {
	}

	vector<Button> GetButtons() {
		return buttons;
	}

	int GetSelectedButton() {
		return selectedButton;
	}

	set<int> GetPressedButtons() {
		return pressedButtons;
	}

	int GetRows() {
		return rows;
	}

	int GetCols() {
		return cols;
	}

	Controller& InitButtons(int rows, int cols) {
		this->rows = rows;
		this->cols = cols;
		for (int i = 0; i < rows * cols; i++) {
			buttons.push_back(Button());
		}

		return *this;
	}

	Controller& PressSelectedButton() {
		buttons[selectedButton].Press();
		pressedButtons.insert(selectedButton);
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
			if (!buttons[i].Update(time) && pressedButtons.count(i)) {
				pressedButtons.erase(i);
				break;
			}
		}

		return *this;
	}
};
#endif
