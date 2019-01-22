#include "extractSequence.h"

//#define _POSIX_C_SOURCE

#include <stdlib.h> // strtol()
#include <string.h> // strtok_r()
//#include <stdio.h>  // printf()


int extractSequencefromString(char* str, int* sequence, int max_len)
{
    int len = 0;
    const char* delims = "{([ ])},;\t\n";
    char* token;
    char* p = str; // give strtok() a "cursor"
    char* ps = 0; // the re-entrant version of strtok() saves it's place


    while (0 != (token = strtok_r(p, delims, &ps))) {
        p = 0; // read the man page for strtok() 

        char* endp;
        int k = strtol(token, &endp, 0);
        int isValid = ((0 != k) || (0 == k && '0' == *token));
        if (isValid && 0 != sequence && len < max_len) {
            sequence[len] = k;
            ++len;
        }
        //printf("k = %3ld, isValid: %d, endp is: '%s'\n", k, isValid, endp);
    }

    return len;
}



