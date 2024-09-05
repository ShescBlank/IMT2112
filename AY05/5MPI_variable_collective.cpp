/*
Correr código (en consola):
- Compilar: mpic++ 5MPI_variable_collective.cpp -std=c++11
- Correr (con 2 procesos): mpirun -np 2 ./a.out
Se puede cambiar el número de procesos con el que se corre
*/

#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <iostream>
#include <mpi.h>
using namespace std;


void print_vector(int* vector, int n, int rank, const char* text) {
    printf("\nRank %i, %s:\n", rank, text);
    for (int i = 0; i < n; i++) {
        printf("%i ", vector[i]);
    }
    printf("\n");
}

/*
A veces podemos querer utilizar alguna operación colectiva para facilitar el envío y recepción de datos, sin embargo, 
puede darse el caso que todos los procesos envían una cantidad distinta de elementos, es decir, no todos los trabajadores 
tienen los mismos tamaños locales. Para esto, existen operaciones colectivas variables que permiten enviar/recibir 
cantidades distintas de datos por cada proceso. Y, para utilizarlas, basta con otorgar un array de tamaños y otro de 
offsets (posiciones), los que representan la información de cada trabajador. 
Página con todas las operaciones colectivas de MPI: https://learn.microsoft.com/en-us/message-passing-interface/mpi-collective-functions 
A continuación, presentamos un ejemplo de Allgatherv:
*/

int main() {
    MPI_Init(NULL,NULL);
    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0) {
        printf("Cantidad de procesos: %i\n\n", world_size);
    }

    int first_index, local_size, err;

    // Vamos a hacer un ejemplo donde cada proceso tiene un vector de tamaño igual a su rango +1
    // Definamos las características de cada uno:
    local_size = world_rank + 1;
    first_index = 0;
    for (int i = 0; i < world_rank; i++)
    {
        first_index += i + 1;
    }
    printf("\nRank %i, local size: %i, first index %i \n", world_rank, local_size, first_index);
    
    // Ahora, creamos el vector local de cada proceso:
    int *local_vec = new int[local_size];

    // Rellenamos el vector:
    for (int i = 0; i < local_size; i++)
    {
        local_vec[i] = i + first_index;
    }
    const char* text = "local vector";
    print_vector(local_vec, local_size, world_rank, text);
    
    // Hasta el momento, cada proceso tiene su propio vector. 
    // Y queremos reunir todas las partes en todos los procesos.
    // Utilicemos operaciones colectivas para realizar esto de manera directa!
    
    // Calculamos el tamaño total del vector completo:
    int total_size = 0; 
    for (int i = 1; i < world_size + 1; i++)
    {
        total_size += i;
    }

    // Necesitamos crear arrays que guarden la cantidad de elementos a recibir de cada proceso y los offsets correspondientes
    int recvcounts[world_size];
    int offsets[world_size];
    for (int i = 0; i < world_size; i++)
    {
        recvcounts[i] = i+1;
        offsets[i] = i;
        if (i > 0)
        {
            offsets[i] += offsets[i-1];
        }
    }
    if (world_rank==0) {
        const char* text2 = "recvcounts vector";
        print_vector(recvcounts, world_size, world_rank, text2);
        const char* text3 = "offsets vector";
        print_vector(offsets, world_size, world_rank, text3);
    }
    

    // Creamos el vector completo
    int *full_vec = new int[total_size];
    
    // Y utilizamos la operación colectiva AllGather pero variable:
    // (ya que no todos los procesos envían la misma cantida de elementos)
    err = MPI_Allgatherv(local_vec, local_size, MPI_INT, full_vec, recvcounts, offsets, MPI_INT, MPI_COMM_WORLD);
    // int MPI_Allgatherv(const void *sendbuf, int sendcount, MPI_Datatype sendtype,
    //                void *recvbuf, const int *recvcounts, const int *displs,
    //                MPI_Datatype recvtype, MPI_Comm comm)

    const char* text4 = "full vector";
    print_vector(full_vec, total_size, world_rank, text4);

    // No olvidemos de liberar la memoria reservada en el heap
    delete[] local_vec;
    delete[] full_vec;


    MPI_Finalize();
}