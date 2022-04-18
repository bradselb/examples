#include <stdio.h>
#include <math.h>

int main(int argc, char** argv)
{
    double phi = (1.0 + sqrt(5)) / 2.0;
    printf("the golden ratio is: %10.8f\n", phi);

    int x1, x2;
    x1 = 1.0;
    x2 = 0.0;
    for (int i=0; i<20; ++i) {
        int x0 = x1 + x2;
        double phi_hat = (double) x0 / x1;

        printf("% 8d, %10.7f, %10.7f\n", x0, phi_hat, fabs(phi - phi_hat));

        x2 = x1;
        x1 = x0;
    }

    return 0;
}
