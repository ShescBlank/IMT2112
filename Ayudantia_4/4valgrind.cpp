/*
Correr código (en consola):
- Compilar: g++ 4valgrind.cpp -o name_output
- Correr con Valgrind: valgrind ./name_output 
Valgrind se encargará de revisar nuestros errores
*/

#include <stdio.h>
#include <stdlib.h> 
#include <ctime>

int main() {
    // Este código contiene errores!
  
    int N, begin, end;
    begin = 10
    end = 20;

    // Creemos un array
    int* array = (int*)calloc(end-begin, sizeof(int));

    // rellenemos sus valores
    for (int i = begin; i < end+1; i++)
    {
        array[i] = i;
    }

    // Imprimimamos sus resultados
    for (int i = begin; i < end+1; i++)
    {
        printf("%d ", array[i]);
    }

    // Y cambiemos un valor
    array[N] = 100;

    // Volvamos a imprimir
    for (int i = begin; i < end; i++)
    {
        printf("%d ", array[i]);
    }

    // No olviden liberar la memoria reservada
    free(array);

    return 0;
}