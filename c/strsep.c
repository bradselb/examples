/* 
  gcc -o strsep -Wall -O2 -std=c89 -D_BSD_SOURCE=1 strsep.c

  ./strsep '$GLGSV,3,1,11,74,42,053,,66,16,296,,82,,,,73,03,019,*5B'
*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* demonstrate the use of the C std library function, strsep() */
/* interpret each string in argv as a string to be parsed into tokens. */
/* strsep() is interesting because it handles empty fields. */


int main(int argc, char* argv[])
{
    const char* delims = ",;:*";
    const char* empty = "<empty>";
    char** argp;
    const char* token;
    char* p;

    argp = &argv[1];
    while (*argp) {
        puts(*argp);

        p = *argp;
        while (0 != (token = strsep(&p, delims))) {
            if (0 == *token) {
                token = empty;
            }
            printf("\t%s\n", token);
        }

        ++argp;
    }
    return 0;
}
