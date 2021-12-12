#ifndef TVREMOTECONTROLLER_TELEVISION_H
#define TVREMOTECONTROLLER_TELEVISION_H

#include <vector>
#include "Material.h"

using namespace std;

class Television {
private:
	bool on;
	int channel;
	int numChannels;
	int volume;
	double brightness;
	vector<Color> colorChannels;
	Color offColor;
	Material offMaterial;
	Material onMaterial;
public:
	Television() {
	}

	Television(Material offMaterial, Material onMaterial) {
		brightness = 0.0;
		this->offMaterial = offMaterial;
		this->onMaterial = onMaterial;
	}

	~Television() {
	}

	bool IsOn() {
		return on;
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

	double GetBrightness() {
		return brightness;
	}

	Material GetOffMaterial() {
		return offMaterial;
	}

	Material GetOnMaterial() {
		return onMaterial;
	}

	Television& TurnOnOff() {
		on = !on;

		if (on) {
			brightness = 1.0;
		} else {
			brightness = 0.0;
		}

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

	Television& SetOffMaterial(Material offMaterial) {
		this->offMaterial = offMaterial;

		return *this;
	}

	Television& SetonMaterialr(Material onMaterial) {
		this->onMaterial = onMaterial;

		return *this;
	}

	Television& SetBrightness(double brightness) {
		if (on && 0.0 < brightness && brightness <= 1.0) {
			this->brightness = brightness;
		}

		return *this;
	}
};

#endif //TVREMOTECONTROLLER_TELEVISION_H
