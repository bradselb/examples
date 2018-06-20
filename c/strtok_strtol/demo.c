// try this...
//   gcc -o demo demo.c
//   ./demo sequences

#include <stdio.h> // printf(), fgets(), fopen(), fclose()
#include <string.h> // strtok(), strtol()
#include <stdlib.h> // malloc() and free()

// idea:
// read lines from a file stream
// interpret each line as a delimited list of integers
// possibly polluted by meaningless syntactic sugar or gibberish text


int extractSequencefromString(char* str, int* seqence, int max_len);



int main(int argc, char* argv[])
{
    FILE* input_stream = 0;
    char* buf = 0;
    int bufsize = 4096;

    buf = malloc(bufsize);
    if (!buf) goto EXIT;

    input_stream = fopen(argv[1], "r");
    if (!input_stream) goto EXIT;

    memset(buf, 0, bufsize);

    while (0 != fgets(buf, bufsize, input_stream)) {
        printf("input string is: %s", buf);
        int len = extractSequencefromString(buf, 0, 0);
        printf("sequence length: %d\n\n", len);
        memset(buf, 0, bufsize);
    }


EXIT:
    if (input_stream) fclose(input_stream);
    if (buf) free(buf);

    return 0;
}



int extractSequencefromString(char* str, int* seqence, int max_len)
{
    int len = 0;
    const char* delims = "{([ ])},;\t\n";
    char* token;
    char* p = str;

    while (0 != (token = strtok(p, delims))) {
        p = 0; // this is how strtok() works. 

        char* endp;
        long int k = strtol(token, &endp, 0);
        int isValid = (0 != k || (0 == k && '0' == *token));
        char ch = 'F';
        if (isValid) {
            ++len;
            ch = 'T';
        }
        printf("k = %3ld, isValid: %c, endp is: '%s'\n", k, ch, endp);
    }

    return len;
}



