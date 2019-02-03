#include "states.h"
#include "motion.h"
#include "inputs.h"

int unknown(void)
{
    int next_state = Unknown;

    if (isButtonPush()) {
        setMotionUp();
        next_state = MovingUp;
    }

    return next_state;
}


int closed(void)
{
    int next_state = Closed;

    if (isButtonPush()) {
        setMotionUp();
        next_state = MovingUp;
    }

    return next_state;
}


int movingUp(void)
{
    int next_state = MovingUp;

    if (isButtonPush()) {
        stopMotion();
        next_state = Stopped;
    }

    else if (isTorqueMagnitudeAboveThreshold()) {
        stopMotion();
        next_state = Open;
    }

    return next_state;
}


int stopped(void)
{
    int next_state = Stopped;

    if (isButtonPush()) {
        setMotionDown();
        next_state = MovingDown;
    }

    return next_state;
}


int open(void)
{
    int next_state = Open;

    if (isButtonPush()) {
        setMotionDown();
        next_state = MovingDown;
    }

    return next_state;
}


int movingDown(void)
{
    int next_state = MovingDown;

    if (isSafetySensorActivated() || isButtonPush()) {
        setMotionUp();
        next_state = MovingUp;
    }

    else if (isTorqueMagnitudeAboveThreshold()) {
        stopMotion();
        next_state = Closed;
    }

    return next_state;
}

