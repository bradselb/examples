#if !defined SENSORDATASTREAM_H
#define SENSORDATASTREAM_H

#include <stdio.h> // FILE

// some functions to represent a stream of sensor data 
// reads from a plain text file but, the interface could (hopefully)
// also represent polling real hardware.

// returns:
//    0 on success
//   non-zero otherwise
int getSensorData(FILE* stream, SensorData_t* sensorData);


#endif //!defined SENSORDATASTREAM_H

