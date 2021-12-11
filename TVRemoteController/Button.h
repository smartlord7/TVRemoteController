#include "ButtonState.h"
#ifndef TVREMOTECONTROLLER_BUTTON_H
#define TVREMOTECONTROLLER_BUTTON_H

class Button {
private:
	ButtonState state;
	double amplitude;
	double maxAmplitude;
    double velocity;
    bool handled;
public:
    static double constexpr BUTTON_DEFAULT_MAX_AMPLITUDE = 0.05;
    static double constexpr BUTTON_DEFAULT_VELOCITY = 0.01;

    Button() {
        handled = false;
        state = ButtonState::BUTTON_STATE_NORMAL;
        amplitude = 0;
        maxAmplitude = BUTTON_DEFAULT_MAX_AMPLITUDE;
        velocity = BUTTON_DEFAULT_VELOCITY;
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

    Button& SetMaxAmplitude(double maxAmplitude) {
        this->maxAmplitude = maxAmplitude;

        return *this;
    }

    Button& SetHandled(bool handled) {
        this->handled = handled;

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
            } else if (amplitude >= 0 && state == ButtonState::BUTTON_STATE_BACK) {
                amplitude -= time * velocity;
            } else if (amplitude < 0 && state == ButtonState::BUTTON_STATE_BACK) {
                state = ButtonState::BUTTON_STATE_NORMAL;

                return false;
            }

            return true;
        }
        else {
            return false;
        }
    }
};

#endif //TVREMOTECONTROLLER_BUTTON_H
