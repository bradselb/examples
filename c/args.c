#include <stdlib.h>
#include <stdio.h>
#include <string.h>



// a short program to investigate the way that arguments are passed to main()

int main(int argc, char* argv[])
{
    int i;
    size_t size;
    size_t totsize = 0;

    // iterate over all the cmd line args, printing each one to stdout. 
    for (i=0; i<argc; ++i) {
        size = strlen(argv[i]) + 1;
        totsize += size;
        printf("argv[%d] is: %p -- > '%s'\t", i, argv[i], argv[i]);
        printf ("\t%p + %lu is: %p\n", argv[i], size, (argv[i] + size));
    }


    // another way...
    i = 0;
    while (argv[i]) {
        printf("argv[%d] is: %p -- > '%s'\n", i, argv[i], argv[i]);
        ++i;
    }

    // still another method of iterating over the cmd line args. 
    // this again makes use of the fact that the last string in argv is 
    // a zero byte.
    char** argp = argv;
    while (*argp) {
        puts(*argp);
        ++argp;
    }



    // demonstrate that all of the striings in argv are in one buffer...
    // as if the shell used strtok() to parse the cmd line args. 
    // this does assume that which it is trying to show.
    // walk through the whole buffer replacing null bytes with a colon
    // and printing each character to stdout. 
    char* p = argv[0];
    char c;
    for (i=0; i<totsize; ++i) {
        c = *p;
        if (0 == c) c = ':';
        putchar(c);
        ++p;
    }
    putchar('\n');

    return 0;
}
