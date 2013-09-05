#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// tokenize the string in place. 
// iterate over string and separate it in to tokens
// where tokens are delimited by chars from the set 'delims'
// remove all delimiters and terminate each token with a null char.
// pack the tokens in the string. 
// returns the number of tokens in the string.
// assumes that s is a null terminated string. 
int tokenize(char* buf, size_t bufsize, const char* delims)
{
    int token_count; // how many tokens were found
    char* begin; // points to first char in token
    char* end; // points to the first byte after token
    char* dest; // where this token is placed in result
    size_t total_token_bytes; 
    size_t token_bytes; 
    size_t delim_bytes;

    total_token_bytes = 0;
    token_count = 0;
    begin = buf;
    end = buf;
    dest = buf;

    printf("count: %d, begin: %p, end: %p, dest: %p\n", token_count, begin, end, dest);
    delim_bytes = strspn(end, delims);
    while (end - buf < bufsize) {
        printf("delim_bytes: %lu, ", delim_bytes);
        begin = end + delim_bytes;
        if (0 == *begin) break;
        token_bytes = strcspn(begin, delims);
        printf("token_bytes: %lu\n", token_bytes);
        end = begin + token_bytes;
        delim_bytes = strspn(end, delims);
        memmove(dest, begin, token_bytes);
        dest = dest + token_bytes;
        *dest = 0;
        ++dest;
        if (token_bytes != 0) {
            ++token_count;
        }
        total_token_bytes += token_bytes;
        printf("count: %d, begin: %p, end: %p, dest: %p\n", token_count, begin, end, dest);
    }

    size_t garbage_bytes = bufsize - (total_token_bytes + token_count);
    printf ("garbage byte count: %lu\n", garbage_bytes);
    if (garbage_bytes) {
        memset(dest, 0, garbage_bytes);
    }

    return token_count;
}

int init_argv(char** argv, int argc, const char* buf, size_t bufsize)
{
    int i;
    size_t offset;

    i = 0;
    offset = 0;

    while (i < argc && offset < bufsize && buf[offset]) {
        argv[i] = (char*)(buf + offset);
        offset = offset + strlen(argv[i]) + 1;
        ++i;
    }
    argv[i] = 0;

    return i;
}


int main(int argc, char* argv[])
{
    char delims[] = ";, \t:=\n";
    //char buf[] = "this;test=string,has six:tokens";
    char buf[] = " this test : =   string,has six   tokens;\n";
    //char buf[] = "token";
    int bufsize = 1 + strlen(buf);
    int token_count = 0;

    char* token_vec[10];
    size_t max_token_count = (sizeof token_vec / sizeof token_vec[0]) - 1;
    memset(token_vec, 0, sizeof token_vec);

    printf("delimiters: '%s'\n", delims);

    printf("original string: '%s'\n", buf);

    token_count = tokenize(buf, sizeof(buf), delims);
    printf("tokenized string: '");
    for (int i = 0; i <bufsize; ++i) {
        char c;
        c = buf[i];
        if (c == 0) c = '0';
        putchar(c);
    }
    printf("' contains %d tokens.\n", token_count);

    token_count = init_argv(token_vec, max_token_count, buf, bufsize);

    for(int i = 0; i < token_count; ++i) {
        printf("argv[%d] = %p \t'%s'\n", i, token_vec[i], token_vec[i]);
    }


    return 0;
}
