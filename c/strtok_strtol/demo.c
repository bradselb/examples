// try this...
//   gcc -o demo demo.c
//   ./demo sequences

#include <stdio.h> // printf(), fgets(), fopen(), fclose()
#include <string.h> // strtok(), strtol()
#include <stdlib.h> // malloc() and free()

// idea:
// read lines from a file stream and interpret each line as a comma delimited
// list of integers possibly polluted by meaningless syntactic sugar or comments.
// There is relatively little syntax here. Sequences (or sets) of integers
// are delimited by the newline character (fgets) and elements of the set 
// (or sequence) are nominally delimited by comma, semi-colon or whitespace.


int extractSequencefromString(char* str, int* seqence, int max_len);



int main(int argc, char* argv[])
{
    FILE* input_stream = 0;
    char* buf = 0;
    int bufsize = 4096;
    int sequence[32];
    const int max_seq_length = sizeof sequence / sizeof sequence[0];

    buf = malloc(bufsize);
    if (!buf) goto EXIT;
    memset(buf, 0, bufsize);

    input_stream = fopen(argv[1], "r");
    if (!input_stream) goto EXIT;

    while (0 != fgets(buf, bufsize, input_stream)) {
        printf("input string is: %s", buf);
        int len = extractSequencefromString(buf, &sequence[0], max_seq_length);
        if (len > 0) {
            printf("[ ");
            for (int i=0; i<len; ++i) {
                printf("%d ", sequence[i]);
            }
            printf("]\n");
        }
        memset(buf, 0, bufsize);
    }


EXIT:
    if (input_stream) fclose(input_stream);
    if (buf) free(buf);

    return 0;
}



int extractSequencefromString(char* str, int* sequence, int max_len)
{
    int len = 0;
    const char* delims = "{([ ])},;\t\n";
    char* token;
    char* p = str;

    while (0 != (token = strtok(p, delims))) {
        p = 0; // this is how strtok() works. 

        char* endp;
        long int k = strtol(token, &endp, 0);
        int isValid = ((0 != k) || (0 == k && '0' == *token));
        if (isValid && 0 != sequence && len < max_len) {
            sequence[len] = k;
            ++len;
        }
        //printf("k = %3ld, isValid: %d, endp is: '%s'\n", k, isValid, endp);
    }

    return len;
}



