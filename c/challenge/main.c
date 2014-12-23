// a programming challenge
// copyright (C) Bradley K. Selbrede, May 2011 
// All rights reserved.
// No use without prior written permission

#include <stdio.h>

#include "Parameters.h"
#include "SensorData.h"
#include "SensorDataStream.h"
#include "Model.h"

void showHelp(const char*);

int main(int argc, char** argv)
{
   int ec = 0; // an error code
   Parameters_t params;
   FILE* datasrc = 0;

   if ( 0 != initialize(&params) ) {
   } 
   else if ( 0 != applyCmdLineArgs(&params, argc, argv) ) {
   }
   else if ( params.showHelp ) {
      showHelp(params.exename); // and be done. 
   }
   else if ( 0 == (datasrc = fopen(params.filename, "r")) ) {
      // an error. errno is set. 
      perror("error while attempting to open sensor data file");
   }
   else {
      int ec = 0;
      SensorData_t obs; // one observed point.
      Model_t model; 
      initModel(&model, &params);
      //showModel(&model);

      // use the initialization period to calibrate the model
      // mainly, just estimate the inital position.
      // it would be cleaner if this were factored out.
      obs.time =0.0;
      while ( obs.time < params.initPeriod ) {
         ec = getSensorData(datasrc, &obs);
         if ( ec ) {
            // error or out of data - fatal either way.
            fprintf(stderr, "fail during initial startup time.\n");
            break; // out of while loop.
         }
         else {
            addInitialDataPoint(&model, obs);
         }
      } // while t < 0.5 seconds


      if ( !ec ) {
         calibrateModel(&model);
         // look at the data stream 
         while ( 0 == getSensorData(datasrc, &obs) ) {
            ec = checkObservedAgainstModel(&model, obs);
            if ( 0 != ec ) {
               printf("error at time = %f\n", obs.time);
               break;
            }
         } // while we have data
      }
   }

   return 0;
}




void showHelp(const char* exename)
{
   printf("%s <filespec> [<options>]\n", exename);
   printf("where:\n");
   printf("filespec specifies the full path to a datafile.\n");
   printf("the data file name is not optional and must be the\n");
   printf("the first command line argument.\n");
   printf("options can be one or more of the following:\n");
   printf("  -h   produces this help message.\n");
}

