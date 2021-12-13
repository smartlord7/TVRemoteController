#ifndef TVREMOTECONTROLLER_TELEVISION_H
#define TVREMOTECONTROLLER_TELEVISION_H

#include <vector>
#include <Windows.h>
#include <mmsystem.h>
#include "Material.h"
#include <thread>
#include <thread>

using namespace std;

class Television {
private:
	bool on;
	int channel;
	int numChannels;
	int volume;
	double brightness;
	vector<Color> colorChannels;
	vector<string> audioChannelsFileNames;
	Color offColor;
	Material offMaterial;
	Material onMaterial;

	void _UpdateAudioVolume() {
		string cmd = "setaudio snd volume to " + volume;

		mciSendStringA(cmd.c_str(), nullptr, 0, nullptr);
	}

	void _UpdateAudio(int prevChannel) {

		string cmd = "stop " + audioChannelsFileNames[prevChannel];
		mciSendString(cmd.c_str(), nullptr, 0, nullptr);

		cmd = "open " + audioChannelsFileNames[channel] + ".wav alias " + audioChannelsFileNames[channel];
		mciSendString(cmd.c_str(), nullptr, 0, nullptr);

		_UpdateAudioVolume();
		cmd = "play " + audioChannelsFileNames[channel];
		mciSendString(cmd.c_str(), nullptr, 0, nullptr);
	}
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

	Color GetColorChannel() {
		if (on) {
			return colorChannels[channel];
		} else {
			return offColor;
		}
	}

	int GetChannel() {
		return channel;
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

	vector<string> GetAudioChannelsFileNames() {
		return audioChannelsFileNames;
	}

	Television& TurnOnOff() {
		on = !on;

		if (on) {
			_UpdateAudio(0);
			brightness = 0.5;

		} else {
			string cmd = "stop " + audioChannelsFileNames[channel];
			mciSendString(cmd.c_str(), nullptr, 0, nullptr);
			brightness = 0.0;
		}

		return *this;
	}

	Television& SetChannel(int channel) {
		int tmp = this->channel;

		if (on) {
			this->channel = channel % numChannels;
			_UpdateAudio(tmp);
		}

		return *this;
	}

	Television& IncChannel() {
		int tmp = this->channel;
		if (on) {
			this->channel = (channel + 1) % numChannels;
			_UpdateAudio(tmp);
		}

		return *this;
	}

	Television& DecChannel() {
		int tmp = this->channel;
		if (on) {
			this->channel = channel - 1 >= 0 ? channel -1 : numChannels - 1;
			_UpdateAudio(tmp);
		}

		return *this;
	}

	Television& IncVolume() {
		if (on) {
			this->volume++;
			_UpdateAudioVolume();
		}

		return *this;
	}

	Television& DecVolume() {
		if (on) {
			this->volume--;
			_UpdateAudioVolume();
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

	Television& SetOnMaterial(Material onMaterial) {
		this->onMaterial = onMaterial;

		return *this;
	}

	Television& SetBrightness(double brightness) {
		if (on && 0.0 < brightness && brightness <= 1.0) {
			this->brightness = brightness;
			this->onMaterial.SetSpecularLight(Color(onMaterial.GetSpecularLight().GetRed() * brightness, onMaterial.GetSpecularLight().GetGreen() * brightness, onMaterial.GetSpecularLight().GetBlue() * brightness));
		}

		return *this;
	}

	Television& SetAudioChannelsFileNames(vector<string> audioChannelsFileNames) {
		this->audioChannelsFileNames = audioChannelsFileNames;

		return *this;
	}
};

#endif //TVREMOTECONTROLLER_TELEVISION_H
