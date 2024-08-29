/*
Correr código (en consola):
- Compilar: g++ -g 5valgrind.cpp -o name_output
- Correr con Valgrind: valgrind ./name_output 
Valgrind se encargará de revisar nuestros errores
pero debes compilar con -g para que nos pueda decir nuestros errores
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
    for (int i = 0; i < end-begin; i++)
    {
        array[i] = i;
    }

    // Imprimimamos sus resultados
    for (int i = 0; i < end-begin; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Y cambiemos el valor en la casilla N
    array[N] = 100;

    // Volvamos a imprimir
    for (int i = begin; i < end; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    // No olviden liberar la memoria reservada
    free(array);
    // Si liberaron todo en un código normal, Valgrind debería decir:
    // "All heap blocks were freed -- no leaks are possible"

    return 0;
}