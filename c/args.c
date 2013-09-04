#include <stdlib.h>
#include <stdio.h>
#include <string.h>



// a short program to investigate the way that arguments are passed to main()

int main(int argc, char* argv[])
{
    int i;
    size_t size;
    size_t totsize = 0;

    i = 0;
    while (argv[i]) {
	printf("argv[%d] is: %p -- > '%s'\n", i, argv[i], argv[i]);
	++i;
    }

    // another way...
    for (i=0; i<argc; ++i) {
	size = strlen(argv[i]) + 1;
	totsize += size;
	printf("argv[%d] is: %p -- > '%s'\t", i, argv[i], argv[i]);
	printf ("\t%p + %lu is: %p\n", argv[i], size, (argv[i] + size));
    }

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
