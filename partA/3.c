#include<stdio.h>
#include<math.h>
#include<omp.h>

void primeTable(int *primes, int n) {
    int i = 0, j = 3, k;
    primes[0] = 2;
    while (i < n) {
        int flag = 0;
        for (k = 2; k <= j/2; k++)
            if (j % k == 0) {
                flag = 1;
                break;
            }
        if (flag == 0)
            primes[++i] = j;
        j++;
    }
}

void sineTable(float *sines, int n) {
    int i;
    for (i = 0; i < n; i++)
        sines[i] =  (double)i*M_PI/180;
}

void main() {
    int n, i;
    printf("Enter the number of primes and sine values to be generated.\n");
    scanf("%d", &n);
    int primes[n];
    float sines[n];
    printf("The prime values are\n");
    primeTable(primes, n);
    for (i = 0; i < n; i++)
        printf("%d\t", primes[i]);
    printf("\n");
    printf("The sine values are\n");
    sineTable(sines, n);
    for (i = 0; i < n; i++)
        printf("%lf\t", sines[i]);
    printf("\n");
}