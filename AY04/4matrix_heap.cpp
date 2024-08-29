/*
Correr código (en consola):
- Compilar: g++ 4matrix_heap -o name_output
- Correr: ./name_output
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctime>

void print_matrix(int N, int** matrix)
{
    // Notar que es importante guardar siempre el largo de un array, para poder recorrerlo.
    // No tenemos una función directa como "len" para obtener su largo.
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
  
    // Para hacer una matriz simplemente debemos hacer array de arrays (punteros de punteros)
    int N = 10;
    int** matrix = (int**)malloc(N * sizeof(int*)); // Reservamos un bloque de memoria que va a almacenar punteros de int
    for (int i = 0; i < N; i++)
    {
        matrix[i] = (int*)calloc(N, sizeof(int)); // Y ahora le damos valor a cada uno de esos punteros con un nuevo bloque
                                                  // de memoria que busca almacenar ints.
    }

    // Rellenemos sus valores con números random
    srand((int) time(0));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            matrix[i][j] = rand()%101; // Qué hace esto?
        }
    }

    // Imprimamos nuestra matriz con la función definida
    print_matrix(N, matrix);
    
    // Finalmente, como usamos calloc y malloc, debemos liberar la memoria reservada
    // antes de acabar nuestro programa:
    for (int i = 0; i < N; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    // Recordar que siempre hay que liberar desde adentro hacia afuera para no perder las referencias.

    // Qué pasa si no liberamos la memoria o si liberamos matrix antes que cada bloque matrix[i]?

    return 0;
}