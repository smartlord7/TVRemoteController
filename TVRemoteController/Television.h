#ifndef TVREMOTECONTROLLER_TELEVISION_H
#define TVREMOTECONTROLLER_TELEVISION_H
#include "Color.h"

class Television {
private:
	Color color;
public:
	Television() {
	}

	~Television() {
	}

	Color GetColor() {
		return color;
	}

	Television& SetColor(Color color) {
		this->color = color;

		return *this;
	}

};

#endif //TVREMOTECONTROLLER_TELEVISION_H
