#include<stdio.h>
#include<omp.h>

void main() {
    int fact1 = 1, fact2 = 1, n, i;
    printf("Enter the number to calculate factorial.\n");
    scanf("%d", &n);
    printf("When private is not used.\n");
    #pragma omp parallel for firstprivate(n)
        for (i = 2; i < n; i++)
            fact1 *= i;
    printf("The factorial of %d is %d.\n", n, fact1);
    printf("When private is used.\n");
    #pragma omp parallel for firstprivate(fact2, n)
        for (i = 2; i < n; i++)
            fact2 *= i;
    printf("The factorial of %d is %d.\n", n, fact2);
}