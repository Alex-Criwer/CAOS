#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int bool;

const size_t BASE = 27;
const size_t DEC = 10;

unsigned int myPow(const unsigned int a, const unsigned int b) {
    if (b == 0) {
        return 1;
    }
    if (b % 2 == 0) {
        return myPow(a * a, b / 2);
    }
    return a * myPow(a, b - 1);
}

int anotherSystemToDec(const int base, const char *str) {
    size_t size = strlen(str);
    bool isPositive = 1;
    int result = 0;
    const char *pointer = str;
    int i = 0;

    if (str[0] == '-') {
        ++pointer;
        isPositive = 0;
        --size;
    }
    int *arrayOfNumbers = (int *) calloc(size, sizeof(int));
    for (i = 0; i < size; ++i) {
        arrayOfNumbers[i] = size - i - 1;
    }
    for (i = 0; i < size; ++i) {
        if (*pointer >= '0' && *pointer <= '9') {
            result += (*pointer - '0') * myPow(base, arrayOfNumbers[i]);
        } else if (*pointer >= 'A' && *pointer <= 'Q') {
            result += (*pointer - 'A' + DEC) * myPow(base, arrayOfNumbers[i]);
        }
        ++pointer;
    }
    free(arrayOfNumbers);
    if (isPositive) {
        return result;
    }
    return -result;
}


int main(int agrc, const char **argv) {
    float firstNumber = 0.0;
    int secondNumber = 0;
    int thirdNumber = 0;
    float sum = 0.0;
    scanf("%f %x", &firstNumber, &secondNumber);
    thirdNumber = anotherSystemToDec(BASE, argv[1]);
    sum = firstNumber + secondNumber + thirdNumber;
    printf("%.3f", sum);
    return 0;
}

