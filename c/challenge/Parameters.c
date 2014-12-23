#include "Parameters.h"

#include <stdio.h> // fprintf for debug messages
#include <string.h>

static const char* s_DefaultExeName = "challenge";

int initialize(Parameters_t* params)
{
   int rc = -1;
   if ( params ) {
      params->exename = s_DefaultExeName;
      params->filename = 0;
      params->gearRatio = (1.0 / 30.0);
      params->showHelp = 1;
      params->initPeriod = 0.5; // seconds

      rc = 0; // success.
   }

   return rc;
}


int applyCmdLineArgs(Parameters_t* params, int argc, char** argv)
{
   int rc = 0;
   const char* arg = 0;
   if ( params ) {
      for ( int i = 0; i<argc; ++i ) {
         arg = argv[i];
         //fprintf(stderr, "argv[%d] is: %s\n", i, arg);
         if ( '-' == arg[0] && 'h' == arg[1] ) {
            params->showHelp = 1;
         }
         else if ( 0 == i ) {
            params->exename = arg;
         }
         else if ( 1 == i ) {
            params->filename = arg;
            params->showHelp = 0; // assume they do not need help
         }
      }
   }
   return rc;
}

int show(Parameters_t* p)
{
   int rc = -1;
   if ( p ) {
      printf("Program parameters\n");
      printf("executable name: '%s'\n", p->exename);
      printf("data file name:  '%s'\n", p->filename);
      printf("gear ratio:  %f\n", p->gearRatio);
      printf("initialization period: %f (seconds)\n", p->initPeriod);
      printf("show help?       '%s'\n", (p->showHelp ? "true" : "false"));

      rc = 0;// success!
   }
   return rc; 
}

