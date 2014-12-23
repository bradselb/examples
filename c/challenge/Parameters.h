#if !defined PARAMETERS_H
#define PARAMETERS_H

// a simple representation of some parameters relavant to 
// coding challenge program. Others could be added.

struct Parameters
{
   const char* exename; // the name issued on the cmd line to call this prog.
   const char* filename; // the name of the datafile
   double gearRatio; // expresessed as a output speed divided by input speed
   float initPeriod; 
   int showHelp;
};

typedef struct Parameters Parameters_t;



// initialize the parameters to default values
int initialize(Parameters_t*);

// read the cms line args and apply them to the parameters 
int applyCmdLineArgs(Parameters_t*, int argc, char** argv);

// write the parameters to stdout
int show(Parameters_t*);

#endif //!defined PARAMETERS_H

