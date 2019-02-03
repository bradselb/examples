
#include "states.h"

int main(int argc, char* argv[])
{
    int rc = 0;
    enum States current_state, next_state;
    int (*stateFuncs[])(void) = {unknown, closed, open, movingUp, movingDown, stopped};

    current_state = Unknown;
    while (1) {
        next_state = (stateFuncs[current_state])();
        current_state = next_state;
    }

    return rc;
}

