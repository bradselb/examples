#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
    time_t t0, t1;
    struct tm tm0, tm1;

    tm0.tm_year = 2015 -1900;
    tm0.tm_mon = 9;
    tm0.tm_mday = 17;
    tm0.tm_hour = 21;
    tm0.tm_min = 32;
    tm0.tm_sec = 17;
    t0 = mktime(&tm0);

    tm1.tm_year = 2015 -1900;
    tm1.tm_mon = 9;
    tm1.tm_mday = 27;
    tm1.tm_hour = 21;
    tm1.tm_min = 32;
    tm1.tm_sec = 42;
    t1 = mktime(&tm1);

    double delta_t;

    delta_t = difftime(t1, t0);

    printf("time difference is: %.1f seconds\n", delta_t);



    return 0;
}
