/*
Correr código (en consola):
- Compilar: g++ 3arrays.cpp -o name_output
- Correr: ./name_output
*/

#include <stdio.h>
#include <stdlib.h> 
#include <ctime>

int main() {
  
    // las listas no vienen nativas, existe el concepto de array

    // Primera manera de hacerlo: dame un array de tamaño n de ints
    int n = 10;
    int array1[n];
    for (int i=0; i<10; i++) {
        printf("%d ", array1[i]);
    }
    printf("\n");
    
    // Segunda manera: puntero de int. calloc es resérvame 10 casilleros 
    // de memoria del tamaño de un int. El (int*) es un casting de int a puntero de int
    int* array2 = (int*) calloc(10, sizeof(int)); // inicializa valores a 0
    for (int i=0; i<10; i++) {
        printf("%d ", array2[i]);
    }
    printf("\n");

    // Tercera forma: en malloc solo le damos el tamaño total de lo que quiero reservar
    int* array3 = (int*) malloc(10 * sizeof(int)); // no inicializa valores
    for (int i=0; i<10; i++) {
        printf("%d ", array3[i]);
    }
    printf("\n");
    

    // Generación de números aleatorios
    // srand((int) time(0)); // seteamos una semilla con el tiempo actual
                             // esto significa que cambiará bastante seguido
    //srand(1);
    
    for (int i=0;i<10;++i) {
        // array2[i] = rand(); // genera números random
        //array2[i] = rand()%10; // para generar números en algún rango (0 y 9)
        //array2[i] = rand()%201 - 100; // entre -100 y 100
        // printf("%i ", array2[i]);
    }
    printf("\n");



    // Algunos datos extras:
    // ======================================
    // Veamos el puntero del array:
    printf("\nPunteros al array1:\n");
    printf("%p\n", array1);
    printf("%p\n", &array1);
    printf("%p\n\n", &array1[0]);

    printf("Punteros al array2:\n");
    printf("%p\n", array2);
    printf("%p\n", &array2);
    printf("%p\n\n", &array2[0]);

    // Aritmética de punteros:
    printf("array[2] = %d\n", array2[2]);
    printf("2[array] = %d\n\n", 2[array2]);
    // ======================================

    // Es necesario liberar las memorias que fueron reservadas con calloc o malloc
    free(array2);
    free(array3);
    // No es necesario al array1 porque este no reserva memoria

    // La diferencia entre el primer arreglo y los dos siguientes es que:
    // - El primer arreglo vive en el Stack, que es básicamente la memoria asignada por mi 
    // sistema operativo para mi programa. Es muy útil, aunque tiene algunas limitaciones.
    // - Los otros dos viven en el Heap, el cual es memoria extra pedida por mi programa.
    // Este último espacio de memoria tiene la ventaja de que siempre que se le pida, va a crecer, y, si se 
    // libera algún bloque ocupado, entonces se reduce. Luego podemos tener control de cuánta memoria 
    // le pedimos.

    return 0;
}