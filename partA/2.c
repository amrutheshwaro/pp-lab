#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void main() {
    int n, m, p, i, j;
    printf("Enter the order of the matrix.\n");
    scanf("%d%d", &m, &n);
    printf("Enter the number of rows in the vector.\n");
    scanf("%d", &p);
    if (m <= 0 || n <= 0 || p <= 0)  {
        printf("Order of the matrix and the number of rows in the vector can't be zero.\n");
        exit(0);
    }
    if (n != p) {
        printf("The number of columns of the matrix and the number of rows of the vector must be same.\n");
        exit(0);
    }
    int mat[m][n], vect[n], res[m];
    printf("The randomly generated matrix is \n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            mat[i][j] = rand() % 100;
            printf("%d\t", mat[i][j]);
        }
        res[i] = 0;
        printf("\n");
    }
    printf("The randomly generated vector is \n");
    for (i = 0; i < n; i++) {
        vect[i] = rand() % 100;
        printf("%d\n", vect[i]);
    }
    printf("The result of the vector by matrix multiplication is\n");
    #pragma omp parallel for private(j)
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++)
                res[i] += mat[i][j] * vect[j];
            printf("%d\n", res[i]);
        }
}