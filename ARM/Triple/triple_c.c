#include <stdlib.h>
#include <stdio.h>

extern int solve(int A, int B, int C, int D);

int main(){
    int A = 0;
    int B = 0;
    int C = 0;
    int D = 0;
    int result = 0;
    scanf("%d%d%d%d", &A, &B, &C, &D);
    result = solve(A, B, C, D);
    printf("%d\n", result);
    return 0;
}
