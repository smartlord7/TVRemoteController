#ifndef TVREMOTECONTROLLER_TELEVISION_H
#define TVREMOTECONTROLLER_TELEVISION_H
#include "Color.h"
#include <vector>

using namespace std;

class Television {
private:
	bool on;
	int channel;
	int numChannels;
	int volume;
	vector<Color> colorChannels;
	Color offColor;
public:
	Television() {

	}

	~Television() {
	}

	Color GetChannel() {
		if (on) {
			return colorChannels[channel];
		} else {
			return offColor;
		}
	}

	int GetVolume() {
		return volume;
	}

	Television& TurnOnOff() {
		on = !on;

		return *this;
	}

	Television& SetChannel(int channel) {
		if (on) {
			this->channel = channel % numChannels;
		}

		return *this;
	}

	Television& IncChannel() {
		if (on) {
			this->channel = (channel + 1) % numChannels;
		}

		return *this;
	}

	Television& DecChannel() {
		if (on) {
			this->channel = channel - 1 >= 0 ? channel -1 : numChannels - 1;
		}

		return *this;
	}

	Television& IncVolume() {
		if (on) {
			this->volume++;
		}

		return *this;
	}

	Television& DecVolume() {
		if (on) {
			this->volume--;
		}

		return *this;
	}

	Television& SetColorChannels(vector<Color> colorChannels) {
		this->colorChannels = colorChannels;
		this->numChannels = colorChannels.size();

		return *this;
	}

	Television& SetOffColor(Color offColor) {
		this->offColor = offColor;

		return *this;
	}
};

#endif //TVREMOTECONTROLLER_TELEVISION_H
