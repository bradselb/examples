#ifndef EXTRACTSEQUENCE_H
#define EXTRACTSEQUENCE_H

// Extract a sequence of integers from a string and return the length of the 
// resultant sequence. The resultant sequence is written to an array allocated
// by the caller (an output param).
// Sequences of integers may be delimited by comma, semi-colon, space, tab, 
// newline, curly braces, square brackets or parentheses. Other characters on 
// the input, representing, for example, units of measure or comments, is ignored.

// The input string is modified

int extractSequencefromString(char* str, int* sequence, int max_len);

#endif // EXTRACTSEQUENCE_H
