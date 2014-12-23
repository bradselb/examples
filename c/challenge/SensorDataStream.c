#include "SensorData.h"
#include "SensorDataStream.h"


#include <stdio.h>
#include <string.h>

static const int s_bufsize = 64;

int getSensorData(FILE* stream, SensorData_t* sensorData)
{
   int rc = 0;

   char* p = 0;
   float time;
   int enc;
   int pot;
   char buf[s_bufsize];

   memset(buf, 0, s_bufsize);

   if ( !(stream && sensorData) ) {
      rc = -1;
   }
   else if ( !(p = fgets(buf, s_bufsize, stream)) ) {
      rc = -1;
   }
   else if ( 3 != sscanf(p, "%f %d %d", &time, &enc, &pot) ) {
      rc = -1;
   }
   else {
      sensorData->time = time;
      sensorData->enc = enc;
      sensorData->pot = pot; 
   }
   
   return rc;
}
