/*
Correr código (en consola):
- Compilar: mpic++ 2MPI_sum.cpp -std=c++11
- Correr (con 2 procesos): mpirun -np 2 ./a.out
Se puede cambiar el número de procesos con el que se corre
*/

#include <iostream>
using namespace std;
#include <mpi.h>

int main() {

    // Iniciamos el entorno de MPI
	MPI_Init(NULL,NULL);

    // Obtenemos el número de procesos y el rango de cada uno:
	int world_size, world_rank;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    // Estos datos son importantes porque los utilizaremos para dividir bien el trabajo y manejar las comunicaciones.

    // Vamos a hacer una suma de 10 (sumlength) números
	int firstIndex, localSize;
    int sumlength = 10;

    // Obtenemos cuántos números sumará cada proceso y desde qué posición parte:
    localSize = sumlength / world_size;
    firstIndex = world_rank * (sumlength/world_size);

    // Notar que la división puede no ser exacta, por lo que hay que sumarle el resto al último proceso
    // (Puede ser otro proceso el encargado del resto, pero elegimos al último por comodidad).
    if (world_rank == world_size-1){
        localSize += sumlength % world_size;
    }
    
    // Imprimimos la información que tenemos hasta ahora:
	cout << "Rank: " << world_rank << ", first index: " << firstIndex << ", local size: " << localSize << endl;

    // Cada proceso crea su vector local que tendrá los valores a sumar:
	int localVector[localSize];
	for (int n=0; n<localSize; n++){
		localVector[n] = firstIndex + n;
		cout << "Rank: " << world_rank << ", localVector[" << n << "] = " << localVector[n] << endl;
	}

    // Cada proceso obtiene su suma local:
	int localSum = 0;
	for (int n=0; n<localSize; n++){
		localSum += localVector[n];
	}
	cout << "Rank: " << world_rank << ", local sum: " << localSum << endl;
    
    // Hasta el momento, cada proceso tiene su suma local.
    // Ahora, debemos encargarnos de juntar todos estos resultados en un proceso y retornar el resultado:
    int globalSum;
    globalSum = 0; // Variable que tendrá el valor final de la suma

    // El proceso de rango 0 se encargará de recibir las sumas locales de todos los otros procesos:
    if (world_rank == 0){
        int receiveBuffer;
        globalSum = localSum;
        for (int p=1; p<world_size; p++){
            MPI_Recv(&receiveBuffer, 1, MPI_INT, p, p, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // int MPI_Recv ( void* buffer, int contador, MPI_Datatype tipo, int origen, int etiqueta, MPI_Comm comunicador, MPI_Status *estado)
            globalSum += receiveBuffer;
        }
    }

    // En cambio, el resto de procesos debe enviar su resultado al proceso 0:
    else {
        MPI_Send(&localSum, 1, MPI_INT, 0, world_rank, MPI_COMM_WORLD);
        // int MPI_Send ( void* data, int contador, MPI_Datatype tipo, int destino, int etiqueta, MPI_Comm comunicador)
    }
    cout << "Rank: " << world_rank << ", global sum from send and receive: " << globalSum << endl;

    // =================================================================================================
    // Logramos recibir todos los cálculos en el root definiendo la comunicación específica de cada proceso. 
    // Veamos otras formas de hacer lo mismo:

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