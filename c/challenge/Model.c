#include "Model.h"
#include <stdio.h> //printf()
#include <math.h> // atan()

// -------------------------------------------------------------------------
int initModel(Model_t* model, Parameters_t const* params)
{
   int rc =0;
   if ( !model || !params ) {
      rc = -1;
   }
   else {
      double pi = 4.0 * atan(1.0);
      // idea is that one could adjust the program parameters 
      // on the cms line to affect the model of the system
      // I'm just going to hardcode this stuff for now.
      model->gearReductionRatio = params->gearRatio;
      model->potRadiansPerCount = (2.0 * pi) / 255.0;
      model->encRadiansPerCount =  (2.0 * pi) / 2048.0;
      model->initialPosition = 0.0;
      model->errorTolerance = 0.1; // radians - completely arbitrary would need to be defined. 

      model->sum =0;
      model->sum2 = 0;
      model->n = 0;
   }

   return rc;
}

// -------------------------------------------------------------------------
int addInitialDataPoint(Model_t* model, SensorData_t data)
{
   int rc = 0;
   if ( !model ) {
      rc = -1;
   }
   else { 
      model->sum += data.pot;
      model->sum2 += data.pot * data.pot;
      model->n += 1;
   }
   return rc;
}

// -------------------------------------------------------------------------
int calibrateModel(Model_t* model)
{
    int rc = 0;
    if ( !model ) {
       rc = -1;
    } else {
       // let the initial position be the average of the initial positions
       model->initialPosition = model->sum * model->potRadiansPerCount / (double) model->n;
       //printf("the intial position is: %f (radians)\n", model->initialPosition);
    }
    return rc;
}

// -------------------------------------------------------------------------
int showModel(Model_t const* model)
{
   int rc = 0;
   if ( !model ) {
      rc = -1;
   } 
   else {
      printf("Gear reduction ratio: %f\n", model->gearReductionRatio);
      printf("potentiometer factor %f\n", model->potRadiansPerCount);
      printf("encoder factor: %f\n", model->encRadiansPerCount);
      printf("initial position %f\n", model->initialPosition);
   }
   return rc;
}

// -------------------------------------------------------------------------
int checkObservedAgainstModel(Model_t* model, SensorData_t obs)
{
   int rc = 0;
   double pi = 4.0 * atan(1.0);

   double motorPosition; // in radians according to the encoder
   double motorRevs; // full revolutions
   double motorPartial; // partial revolutions
   double observed; // the observed output shaft position as reported by potentiometer
   double expected; // what we expect the output shaft position to be based upon the encoder.
   double error; // the difference between observed and expected. 

   if ( !model ) {
      rc = -1;
   }
   else {
      motorPosition = (obs.enc * model->encRadiansPerCount);
      motorRevs = floor(motorPosition / (2.0 * pi));
      motorPartial = (motorPosition / (2.0 * pi))  -  motorRevs;

      expected = model->initialPosition 
               + (2.0 * pi) * motorRevs * model->gearReductionRatio
               + (2.0 * pi) * motorPartial * model->gearReductionRatio;


      observed = obs.pot * model->potRadiansPerCount;

      error = observed - expected;


      if ( model->errorTolerance <  fabs(error) )  {
         rc = 1;
      }

      //printf("time: %f, motor: %f, revolutions: %f, partial: %f, observed: %f, expected: %f, error: %f\n", 
      //       obs.time, motorPosition, motorRevs, motorPartial, observed, expected, error);

   }
   return rc;
}

