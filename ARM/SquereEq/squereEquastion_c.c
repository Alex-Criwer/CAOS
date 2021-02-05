#include <stdlib.h>
#include <stdio.h>

extern int f(int A, int B, int C, int x);

int main(const int agrc, const char **argv) {
    int array[4];
    while(scanf("%d%d%d%d", &array[0], &array[1], &array[2], &array[3]) > 0){
        int y = f(array[0], array[1], array[2], array[3]);
        printf("%d\n", y);
    }
    return 0;
}
