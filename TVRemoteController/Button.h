#ifndef TVREMOTECONTROLLER_BUTTON_H
#define TVREMOTECONTROLLER_BUTTON_H

#include "ButtonState.h"

class Button {
private:
	ButtonState state;
	double amplitude;
	double maxAmplitude;
    double velocity;
    bool handled;
    int id;
    string label;

public:
    static const int global_id = 0;
    static double constexpr BUTTON_DEFAULT_MAX_AMPLITUDE = 0.05;
    static double constexpr BUTTON_DEFAULT_VELOCITY = 0.01;

    Button(int id, string label) {
        handled = false;
        state = ButtonState::BUTTON_STATE_NORMAL;
        amplitude = 0;
        maxAmplitude = BUTTON_DEFAULT_MAX_AMPLITUDE;
        velocity = BUTTON_DEFAULT_VELOCITY;
        this->id = id;
        this->label = label;
    }

    ~Button() {
    }

    ButtonState GetState() {
        return state;
    }

    double GetAmplitude() {
        return amplitude;
    }

    double GetMaxAmplitude() {
        return maxAmplitude;
    }

    double GetVelocity() {
        double velocity;
    }

    bool IsHandled() {
        return handled;
    }

    int GetId() {
        return id;
    }

    string GetLabel() {
        return label;
    }

    Button& SetMaxAmplitude(double maxAmplitude) {
        this->maxAmplitude = maxAmplitude;

        return *this;
    }

    Button& SetHandled(bool handled) {
        this->handled = handled;

        return *this;
    }

    Button& SetId(int id) {
        this->id = id;
        
        return *this;
    }

    Button& SetLabel(string label) {
        this->label = label;

        return *this;
    }

    void Press() {
        state = ButtonState::BUTTON_STATE_PRESSED;
    }

    bool Update(double time) {
        if (state != ButtonState::BUTTON_STATE_NORMAL) {
            if (amplitude < 0) {
                amplitude = 0;
            }

            if (amplitude >= 0 && amplitude < maxAmplitude && state == ButtonState::BUTTON_STATE_PRESSED) {
                amplitude += time * velocity;
            } else if (amplitude >= maxAmplitude && state == ButtonState::BUTTON_STATE_PRESSED) {
                state = ButtonState::BUTTON_STATE_BACK;
            } else if (amplitude > 0 && state == ButtonState::BUTTON_STATE_BACK) {
                amplitude -= time * velocity;
            } else if (amplitude <= 0 && state == ButtonState::BUTTON_STATE_BACK) {
                state = ButtonState::BUTTON_STATE_NORMAL;

                return false;
            }

            return true;
        }
        else {
            return false;
        }
    }

    bool IsInAnimation() {
        return state == ButtonState::BUTTON_STATE_PRESSED || state == ButtonState::BUTTON_STATE_BACK;
    }
};

#endif //TVREMOTECONTROLLER_BUTTON_H
