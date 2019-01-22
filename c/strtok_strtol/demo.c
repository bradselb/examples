
#include "extractSequence.h"

#include <string.h> // memset(), strncpy(), strlen()
#include <stdio.h> // printf(), fgets(), fopen(), fclose()
#include <stdlib.h> // malloc() and free()

// idea:
// read lines from a file stream and interpret each line as a comma delimited
// list of integers possibly polluted by meaningless syntactic sugar or comments.
// There is relatively little syntax here. Sequences (or sets) of integers
// are delimited by the newline character (fgets) and elements of the set 
// (or sequence) are nominally delimited by comma, semi-colon or whitespace.



int main(int argc, char* argv[])
{
    FILE* input_stream = 0;

    char* inbuf = 0;
    char* scratch_buf = 0;
    int bufsize = 4096;
    
    int sequence[64];
    const int max_seq_length = sizeof sequence / sizeof sequence[0];

    inbuf = malloc(bufsize);
    if (!inbuf) goto EXIT;

    scratch_buf = malloc(bufsize);
    if (!scratch_buf) goto EXIT;

    input_stream = fopen(argv[1], "r");
    if (!input_stream) goto EXIT;

    // read lines from the input file until the end of file.
    memset(inbuf, 0, bufsize);
    while (0 != fgets(inbuf, bufsize, input_stream)) {
        printf("input string is: %s", inbuf);

        // copy the input to the scratch buffer.
        memset(scratch_buf, 0, bufsize);
        strncpy(scratch_buf, inbuf, strlen(inbuf));

        int len = extractSequencefromString(inbuf, &sequence[0], max_seq_length);
        if (len > 0) {
            printf("[ ");
            for (int i=0; i<len; ++i) {
                printf("%d ", sequence[i]);
            }
            printf("]\n");
        }
        memset(inbuf, 0, bufsize);
    }


EXIT:
    if (input_stream) fclose(input_stream);
    if (scratch_buf) free(scratch_buf);
    if (inbuf) free(inbuf);

    return 0;
}

