#include <stdlib.h>
#include <stdio.h>

int moveSingle(char from, char to)
{
    static int step = 0;
    printf("%d) %c -> %c\n", ++step, from, to);
    return 0;
}

int moveStack(int n, char from, char to, char via)
{
    if ( n == 1 ) {
        moveSingle(from, to);
    } else {
        moveStack(n-1, from, via, to);
        moveSingle(from, to);
        moveStack(n-1, via, to, from);
    }
    return 0;
}



int main(int argc, char** argv)
{
    int n = 8;

    if ( 1 < argc ) {
        n = atoi(argv[1]);
    }

    moveStack(n, 'A', 'B', 'C');

    return 0;
}

