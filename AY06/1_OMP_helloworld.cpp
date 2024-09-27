/*
Comandos útiles:
Compilar código:    g++ -o name_output 1_OMP_helloworld.cpp -fopenmp
Correr código:      ./name_output
*/

#include <stdio.h>
#include <omp.h>
 
int main() {

    // Trabajaremos con thread y usaremos OpenMP

    // Con la siguiente línea, generamos un bloque de código que será ejecutado por múltiple threads:
    #pragma omp parallel // en mi computador se utilizan 8 threads por defecto
    {
        printf("Hello World\n");
        int id = omp_get_thread_num();
        int total = omp_get_num_threads();
        printf("Greetings from process %d out of %d \n", id, total);   
    }

    printf("\n=================================================================\n");

    // Pero también podemos decirle cuántos threads queremos
    #pragma omp parallel num_threads(1)
    {
        printf("Hello World\n");
        int id = omp_get_thread_num();
        int total = omp_get_num_threads();
        printf("Greetings from process %d out of %d \n", id, total);   
    }

    return 0;
}

