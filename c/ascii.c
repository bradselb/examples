#include <stdio.h>

int main(int argc, char* argv[])
{
    int i;

    // print a header row
    printf("   |");
    for (i=0; i<0x10; ++i) {
        printf("%1x ", i);
    }
    printf("\n-----------------------------------\n");

    // print the body of the table
    for (i=0x20; i<0x80; ++i) {
        if (0 == i%16) {
            printf("%02x |", i);
        }

        printf("%c ", i);

        if (15 == i%16) {
            printf("\n");
        }

    }
    return 0;
}
