#include <stdlib.h>
#include <stdio.h>

extern int summ(int x0, int N, int *X);

int main(const int agrc, const char **argv) {
    int x0 = 0;
    int size = 0;
    scanf("%d%d", &x0, &size);
    int* array = (int *) calloc(size, sizeof(int));
    for (int i = 0; i < size; ++i) {
        int temp = 0;
        scanf("%d", &temp);
        array[i] = temp;
    }
    int result = summ(x0, size, array);
    printf("%d\n", result);
    return 0;
}

