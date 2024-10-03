/*
Comandos útiles:
Compilar código:    g++ -o name_output 3_OMP_reduction.cpp -fopenmp
Correr código:      ./name_output
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
 
int main() {

    // Qué pasa si hacemos una reducción con OpenMP?
    int x1 = 0;

    // Notar que agregamos "for" al pragma
    // Esto para repartir las iteraciones entre los threads
    #pragma omp parallel for num_threads(24)
    for (int i = 0; i < 100000000; i++) {
        int id = omp_get_thread_num();
        x1 += 1;
        //printf("Proceso %d sumó 1\n", id);  
    }

    printf("\nSuma Final 1 = %d\n", x1);

    // Ahora, veamos algo que sí funciona:

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

    // Por último, OpenMP también tiene la siguiente forma de hacerlo:
    int x3 = 0;

    // Agregamos el parámetro reduction al pragma
    #pragma omp parallel for num_threads(24) reduction(+:x3)
    for (int i = 0; i < 100000000; i++) {
        int id = omp_get_thread_num();
        x3 += 1;
        //printf("Proceso %d sumó 1\n", id);  
    }

    printf("\nSuma Final 3 = %d\n", x3);


    // Nunca olviden de liberar memoria si es que la reservan :D
    free(array);

    return 0;
}
