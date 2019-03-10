#include "motion.h"
#include "inputs.h"


int main(int argc, char* argv[])
{
    enum States {Unknown, Closed, Open, MovingUp, MovingDown, Stopped, StateCount};
    enum States state;

    state = Unknown;
    while (1) {
        switch (state)
        {
            case Unknown:
                if (isButtonPush()) {
                    setMotionUp();
                    state = MovingUp;
                }
                break;

            case Closed:
                if (isButtonPush()) {
                    setMotionUp();
                    state = MovingUp;
                }
                break;

            case Open:
                if (isButtonPush()) {
                    setMotionDown();
                    state = MovingDown;
                }
                break;

            case MovingUp:
                if (isButtonPush()) {
                    stopMotion();
                    state = Stopped;
                }

                else if (isTorqueMagnitudeAboveThreshold()) {
                    stopMotion();
                    state = Open;
                }
                break;

            case MovingDown:
                if (isSafetySensorActivated() || isButtonPush()) {
                    setMotionUp();
                    state = MovingUp;
                }
                else if (isTorqueMagnitudeAboveThreshold()) {
                    stopMotion();
                    state = Closed;
                }
                break;

            case Stopped:
                break;

            default:
                state = Unknown;
                break;
        }

    }

    return 0;
}

