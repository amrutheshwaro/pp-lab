#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define SEED 12345678
#define N 100000

void main() {
    int rank, i;
    double x, y, z, count, val;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    srand(SEED + rank);
    for (i = 0; i < N; i++) {
        x = (double)rand()/RAND_MAX;
        y = (double)rand()/RAND_MAX;
        z = x*x + y*y;
        if (z <= 1)
            count++;
    }
    MPI_Reduce(&count, &val, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
        printf("PI = %lf\n", val/N);
    MPI_Finalize();
}