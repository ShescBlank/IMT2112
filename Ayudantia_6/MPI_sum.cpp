#include <iostream>
using namespace std;
#include <mpi.h>

int main(){

	MPI_Init(NULL,NULL);

	int world_size, world_rank;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int firstIndex, localSize;
    int sumlenght = 10;
    localSize = sumlength / world_size;
    firstIndex = world_rank * (sumlength/world_size);
    if (world_rank == world_size-1){
        localSize += sumlength % world_size;
    }
    
	cout << "Rank: " << world_rank << ", first index: " << firstIndex << ", local size: " << localSize << endl;

	int localVector[localSize];
	
	for (int n=0; n<localSize; n++){
		localVector[n] = firstIndex + n;
		cout << "Rank: " << world_rank << ", localVector[" << n << "] = " << localVector[n] << endl;
	}

	int localSum = 0;
	for (int n=0; n<localSize; n++){
		localSum += localVector[n];
	}
	cout << "Rank: " << world_rank << ", local sum: " << localSum << endl;
    
    int globalSum;
    
    globalSum = 0;
    if (world_rank == 0){
        int receiveBuffer;
        globalSum = localSum;
        for (int p=1; p<world_size; p++){
            MPI_Recv(&receiveBuffer, 1, MPI_INT, p, p, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // int MPI_Recv ( void* buffer, int contador, MPI_Datatype tipo, int origen, int etiqueta, MPI_Comm comunicador, MPI_Status *estado)
            globalSum += receiveBuffer;
        }
    }
    else {
        MPI_Send(&localSum, 1, MPI_INT, 0, world_rank, MPI_COMM_WORLD);
        // int MPI_Send ( void* data, int contador, MPI_Datatype tipo, int destino, int etiqueta, MPI_Comm comunicador)
    }
    cout << "Rank: " << world_rank << ", global sum from send and receive: " << globalSum << endl;

    // Ya logramos recibir todos los cálculos en el root, veamos otras opciones de hacer lo mismo:

    // Podemos usar Reduce para juntar los datos en un proceso raíz a través de una operación
	globalSum = 0;
	MPI_Reduce(&localSum, &globalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    // MPI_Reduce(void* send_data, void* recv_data, int count, MPI_Datatype datatype, MPI_Op operation, int root, MPI_Comm communicator)
	cout << "Rank: " << world_rank << ", global sum from reduce: " << globalSum << endl;

    // Podemos usar Allreduce para que el resultado reducido esté en todos los procesos:
	globalSum = 0;
	MPI_Allreduce(&localSum, &globalSum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    // MPI_Allreduce(void* send_data, void* recv_data, int count, MPI_Datatype datatype, MPI_Op operation, MPI_Comm communicator)
	cout << "Rank: " << world_rank << ", global sum from allreduce: " << globalSum << endl;

	MPI_Finalize();

}