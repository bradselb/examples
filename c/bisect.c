#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>



int is_erased(int32_t guess, int32_t answer)
{
    int v = (guess >= answer);
    return v;
}

// upper address is always assumed to be erased whereas
// the lower address is alwasy known to be not erased

int bisect(int32_t lower, int32_t upper, int32_t ans, int32_t* guess)
{
    int32_t span;
    int32_t addr;
    int n;

    // enforce the invariant (that lower is NOT erased)
    if (is_erased(lower, ans)) {
        upper = lower; // this will make while loop get skipped.
        // and we'll fall oout of the function with 
    }

    n = 0;
    while ((span = upper - lower + 1) > 2) {
        ++n;
        addr = lower + (span>>1);
        if (is_erased(addr, ans)) {
            upper = addr;
        } else if (is_erased(addr+1, ans)) {
            upper = addr+1;
            break;
        } else if (is_erased(addr+2, ans)) {
            upper = addr+2;
            break;
        } else if (is_erased(addr+3, ans)) {
            upper = addr+3;
            break;
        } else {
            lower = addr;
        }
    }
    addr = upper;
    if (guess) *guess = addr;
    return n;
}

int cmp(const void* a, const void* b)
{
    int diff = (*(char*)a - *(char*)b);
    int result = 0;
    if (diff < 0) result =-1;
    else if (diff > 0) result = 1;
    return result;
}

void describe(char* data, int begin, int end)
{
    double sum = 0.0;
    int n = 0;
    int min = 255;
    int max = -255;
    int median;
    int* bin;
    int bincount;

    for (int i=begin; i<end; ++i){
        sum += data[i];
        ++n;
        if (data[i] < min) min = data[i];
        if (max < data[i]) max = data[i];
    }
    bincount = max +1;
    bin = malloc(bincount * sizeof *bin);
    memset(bin, 0, bincount * sizeof *bin);
    for (int i=begin; i<end; ++i) {
        bin[data[i]] += 1;
    }
    for (int i=0; i<bincount; ++i) {
        printf("%3d : %d\n", i, bin[i]);
    }

    qsort(data, n, 1, cmp);
    median = data[begin + (n-1)/2];
    printf("n: %d, min: %d, max: %d, median: %d, avg: %f\n", n, min, max, median, sum/n);
}

int main(int argc, char* argv[])
{
    int32_t a;
    int32_t g;
    char* n;
    int bits = 20;
    uint32_t capacity = (1<<bits);
    int32_t last_address = capacity - 1;

    n = malloc(capacity);
    memset(n, 0, capacity);

    int count = 0;
    for (a=0; a<capacity; ++a) {
        n[a] = bisect(0, last_address, a, &g);
        ++count;
        if (a != g) printf("FAIL: answer: %d, guess: %d\n", a, g);
    }

    describe(n, 0, count);

    free(n);
    return 0;
}
