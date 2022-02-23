#include<stdio.h>
#include<mpi.h>

#define BUFFER_SIZE 8

void main() {
    int rank, i, j, k;
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{1, 0}, {0, 1}};
    int c[2][2];
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    if (rank == 0) {
        for (i = 0; i < 2; i++)
            for (j = 0; j < 2; j++) {
                c[i][j] = 0;
                for (k = 0; k < 2; k++)
                    c[i][j] += a[i][k] * b[k][j];
            }
        MPI_Send(&c, BUFFER_SIZE, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else if (rank == 1) {
        MPI_Recv(&c, BUFFER_SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        for (i = 0; i < 2; i++) {
            for (j = 0; j < 2; j++)
                printf("%d\t", c[i][j]);
            printf("\n");
        }
    }
    MPI_Finalize();
}