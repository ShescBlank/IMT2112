#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <mpi.h>
using namespace std;

int main() {
    MPI_Init(NULL,NULL);
	int world_size, world_rank;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0) {
        printf("Cantidad de procesos: %i\n\n", world_size);
    }

    int firstIndex, localSize, n, err;
    
    n = 7;

    localSize = n / world_size;
    firstIndex = world_rank*localSize;

    if (world_rank == world_size-1) {
        localSize += n % world_size;
    }

    printf("Rank %i, local size: %i, first index %i \n", world_rank, localSize, firstIndex);

	int localVec1[localSize];
	int localVec2[localSize];

	for (int i=0; i<localSize; i++) {
		localVec1[i] = 1;
        localVec2[i] = firstIndex + i;
        //printf("Rank: %i, locvec1 %i, locvec2 %i\n", world_rank, localVec1[i], localVec2[i]);
	}

	int localSum = 0;
	for (int i=0; i<localSize; i++) {
		localSum += localVec1[i] * localVec2[i];
	}
    // printf("Local Sum: %i\n", localSum);
    
    int globalSum = localSum;
    int receiveBuffer;

    if (world_rank == 0) {
        for (int p=1; p<world_size; p++) {
            err = MPI_Recv(&receiveBuffer, 1, MPI_INT, p, p, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
            globalSum += receiveBuffer;
        }
        printf("El valor del producto punto es: %i\n", globalSum);
    } else {
        err = MPI_Send(&localSum, 1, MPI_INT, 0, world_rank, MPI_COMM_WORLD);
        //MPI_Send(void* data, int count, MPI_Datatype datatype, int destination, int tag, MPI_Comm communicator)
    }

	MPI_Finalize();
}
