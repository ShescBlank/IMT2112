/*
Correr código (en consola):
- Compilar: mpic++ 1MPI_hello_world.cpp -std=c++11
- Correr (con 2 procesos): mpirun -np 2 ./a.out
Se puede cambiar el número de procesos con el que se corre
*/

#include <mpi.h> // Nuevo include!
#include <stdio.h>

int main(int argc, char** argv) {
    // int a = 10;
    // printf("Valor de a: %d\n", a);

    // Initialize the MPI environment (Message Passing Interface)
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // El MPI_COMM_WORLD es el comunicador de nuestro grupo de procesos

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Print off a hello world message from each process
    printf("Hello world from processor %s, rank %d out of %d processors\n", processor_name, world_rank, world_size);

    // Finalize the MPI environment.
    MPI_Finalize();
}