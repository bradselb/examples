#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CR 0x0d
#define LF 0x0a

int main(int argc, char* argv[])
{
    FILE* file;
    int ch;
    int prev_ch;
    int i;

    /* iterate over all files named on the cmd line. */
    for (i=1; i<argc; ++i) {
        file = fopen(argv[i], "r+");
        if (!file) {
            continue;
        }

        /* iterate over characters in file */
        prev_ch = 0;
        while (EOF != (ch = fgetc(file))) {
            if (ch == CR) {
                ch = LF;
            }

            if (ch != LF || prev_ch != LF) {
                fputc(ch, stdout);
            }
            prev_ch = ch;
        }

        fclose(file);
    }

    return 0;
}

