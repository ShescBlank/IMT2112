/*
Comandos útiles:
Compilar código:    g++ -o name_output 2_OMP_loops.cpp -fopenmp
Correr código:      ./name_output
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
int main() {

    // Qué pasa si sumamos en paralelo usando threads?
    int x1 = 0;

    // Notar que agregamos "for" al pragma
    // Esto para repartir las iteraciones entre los threads
    #pragma omp parallel for num_threads(24)
    for (int i = 0; i < 10000; i++) {
        int id = omp_get_thread_num();
        x1 += 1;
        //printf("Proceso %d sumó 1\n", id);  
    }

    printf("\nSuma Final 1 = %d\n", x1);

    // Veamos otra posibilidad

    int x2 = 0;
    int n = 10;
    int* array = (int*) calloc(n, sizeof(int));
    
    #pragma omp parallel for num_threads(n)
    for (int i = 0; i < 100000000; i++) {
        int id = omp_get_thread_num();
        array[id] += 1;
        // printf("Proceso %d sumó 1\n", id);  
    }

    for (int i = 0; i < n; i++) {
        x2 += array[i]; 
    }

    printf("\nSuma Final 2 = %d\n", x2);


    // Nunca olviden de liberar memoria si es que la reservan :D
    free(array);

    return 0;
}
