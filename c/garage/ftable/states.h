#ifndef STATES_H
#define STATES_H


enum States {Unknown, Closed, Open, MovingUp, MovingDown, Stopped, StateCount};

int unknown(void);
int closed(void);
int open(void);
int movingUp(void);
int movingDown(void);
int stopped(void);

#endif // STATES_H

