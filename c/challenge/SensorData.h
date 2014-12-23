#if !defined SENSORDATA_H
#define SENSORDATA_H

struct SensorData 
{
   float time;
   int enc; // encoder counts
   int pot; // potentiometer counts
};
typedef struct SensorData SensorData_t;

#endif  //!defined SENSORDATA_H
