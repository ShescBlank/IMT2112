/*
Correr código (en consola):
- Compilar: mpic++ 3MPI_dot.cpp -std=c++11
- Correr (con 2 procesos): mpirun -np 2 ./a.out
Se puede cambiar el número de procesos con el que se corre
*/

#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <mpi.h>
using namespace std;

int main() {

    // Iniciamos el entorno de MPI y obtenemos los valores usuales
    MPI_Init(NULL,NULL);
	int world_size, world_rank;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Que solo el proceso raíz imprima la cantidad de procesos totales:
    if (world_rank == 0) {
        printf("Cantidad de procesos: %i\n\n", world_size);
    }

    // Inicializamos algunas variables que utilizaremos
    int firstIndex, localSize, n, err;
    
    // Vamos a trabajar con vectores de largo n
    n = 7;

    // Calculamos el primer índice y el tamaño local de cada proceso
    localSize = n / world_size;
    firstIndex = world_rank*localSize;

    // Recordar que hay que agregar lo que sobra (por si la división no es exacta)
    if (world_rank == world_size-1) {
        localSize += n % world_size;
    }
    printf("Rank %i, local size: %i, first index %i \n", world_rank, localSize, firstIndex);

    // Cada proceso crea la porción del vector que usará:
	int localVec1[localSize];
	int localVec2[localSize];
	for (int i=0; i<localSize; i++) {
		localVec1[i] = 1;               // Vector de 1s
        localVec2[i] = firstIndex + i;  // Vector con valores de posición
        //printf("Rank: %i, locvec1 %i, locvec2 %i\n", world_rank, localVec1[i], localVec2[i]);
	}

    // Cada proceso calcula su producto punto local:
	int localSum = 0;
	for (int i=0; i<localSize; i++) {
		localSum += localVec1[i] * localVec2[i];
	}
    // printf("Local Sum: %i\n", localSum);
    
    // Finalmente, nos encargamos de la comunicación de la información:
    int globalSum = localSum;
    int receiveBuffer;

    if (world_rank == 0) {  // Proceso raíz recibe
        for (int p=1; p<world_size; p++) {
            err = MPI_Recv(&receiveBuffer, 1, MPI_INT, p, p, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
            globalSum += receiveBuffer;
        }
        printf("El valor del producto punto es: %i\n", globalSum);
    } else {                // El resto de procesos envía
        err = MPI_Send(&localSum, 1, MPI_INT, 0, world_rank, MPI_COMM_WORLD);
        //MPI_Send(void* data, int count, MPI_Datatype datatype, int destination, int tag, MPI_Comm communicator)
    }

    // Recordar que también se puede con otras funciones como las de reduce.

	MPI_Finalize();
}

/*
Cabe destacar que, en estos ejemplos, estamos viendo casos en que cada proceso se preocupa de crear y trabajar su parte local.
En general, no vale la pena que cada proceso posea una copia entera de la matriz o vector que se está trabajando, ya que habría mucha 
información repetida, lo que provoca que se utilice más memoria de la necesaria y hay que tener mucho ojo si se quiere actualizar 
alguna entrada de esos objetos (repartir la información a todos los procesos y cuidar que los cálculos se realicen con las últimas versiones de todo).
En resumen, es mejor que cada proceso trabaje solo con lo que le corresponde, creándolo/leyéndolo él mismo desde un inicio.
*/
