#include<stdio.h>
#include<string.h>
#include<mpi.h>

#define BUFFER_SIZE 32

void main() {
    int rank, size, root = 3, temp;
    char msg[BUFFER_SIZE];
    MPI_Init(NULL, NULL);
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 3) {
        strcpy(msg, "Hello");
        for (temp = 0; temp < size; temp++)
            if (temp != 3)
                MPI_Send(msg, BUFFER_SIZE, MPI_CHAR, temp, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(msg, BUFFER_SIZE, MPI_CHAR, root, 0, MPI_COMM_WORLD, &status);
        printf("%s is in process with %d from process with rank %d.\n", msg, rank, root);
    }
    MPI_Finalize();
}