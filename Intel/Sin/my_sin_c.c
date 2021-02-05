#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>



extern double my_sin(double x);

int main() {
    double angle = 3.1415926535 * 11/6;
    double answer1 = my_sin(angle);
    double answer2 = -0.5;//sin(angle);

    printf("%f %f %f", angle, answer1, answer2);

    return 0;
}


