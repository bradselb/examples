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
int tokenize(char* buf, const char* delims)
{
    int token_count; // how many tokens were found
    char* begin; // points to first char in token
    char* end; // points to the first byte after token
    char* dest; // where this token is placed in result
    size_t token_bytes; 
    size_t delim_bytes;

    token_count = 0;
    begin = buf;
    end = buf;
    dest = buf;

    while (begin && end && *end){
	delim_bytes = strspn(end, delims);
	begin = end + delim_bytes;
	token_bytes = strcspn(begin, delims);
	end = begin + token_bytes;
	memmove(dest, begin, token_bytes);
	dest = dest + token_bytes;
	*dest = 0;
	++dest;
	if (token_bytes != 0) {
	    ++token_count;
	}
    }

    size_t garbage_bytes = dest - buf;
    if (garbage_bytes) {
	memset(dest, 0, garbage_bytes);
    }

    return token_count;
}


int main(int argc, char* argv[])
{
    char buf[] = " this test : =   string,has six   tokens;\n";
    char delims[] = ";, \t:=\n";
    int bufsize = 1 + strlen(buf);
    int tokens = 0;

    printf("delimiters: '%s'\n", delims);

    printf("original string: '%s'\n", buf);

    tokens = tokenize(buf, delims);
    printf("tokenized string: '");
    for (int i = 0; i <bufsize; ++i) {
	char c;
	c = buf[i];
	if (c == 0) c = '0';
	putchar(c);
    }
    printf("' contains %d tokens.\n", tokens);

    return 0;
}
