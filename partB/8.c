#include<stdio.h>
#include<mpi.h>

void main() {
    int rank, size, i;
    double a[100], b[100], mysum = 0, allsum;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
        printf("Exection of process dot product starting with %d tasks.\n", size);
    for (i = 0; i < 100; i++)
        a[i] = b[i] = 1.0;
    for (i = 0; i < 100; i++)
        mysum += a[i] * b[i];
    printf("The partial sum of task %d is %f.\n", rank, mysum);
    MPI_Reduce(&mysum, &allsum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
        printf("Process completed: Global sum = %f.\n", allsum);
    MPI_Finalize();
}