#if !defined MODEL_H
#define MODEL_H

#include "Parameters.h"
#include "SensorData.h"

struct Model
{
   double gearReductionRatio;
   double potRadiansPerCount;
   double encRadiansPerCount;
   double initialPosition; // radians.
   double errorTolerance; // 

   int sum;
   int sum2;
   int n;
};

typedef struct Model Model_t;

int initModel(Model_t*, Parameters_t const*);

int addInitialDataPoint(Model_t*, SensorData_t);

int calibrateModel(Model_t* model);

int showModel(Model_t const* model);

int checkObservedAgainstModel(Model_t* model, SensorData_t obs);

#endif // !defined MODEL_H

