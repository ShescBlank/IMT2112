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

    // Primera manera de hacerlo (stack): dame un array de tamaño n de ints
    int n = 10;
    int array1[n];
    for (int i=0; i<10; i++) {
        printf("%d ", array1[i]); // no inicializa valores (toma lo que hay directamente)
    }
    printf("\n");
    
    // Segunda manera (heap): puntero de int. calloc es resérvame 10 casilleros 
    // de memoria del tamaño de un int y dales valor 0. El (int*) es un casting de int a puntero de int.
    int* array2 = (int*) calloc(10, sizeof(int)); // inicializa valores a 0
    for (int i=0; i<10; i++) {
        printf("%d ", array2[i]);
    }
    printf("\n");

    // Tercera forma (heap): en malloc solo le damos el tamaño total de lo que quiero reservar.
    // También es necesario hacer el casting a puntero de int!
    int* array3 = (int*) malloc(10 * sizeof(int)); // no inicializa valores (toma lo que hay directamente)
    for (int i=0; i<10; i++) {
        printf("%d ", array3[i]);
    }
    printf("\n");
    

    // Generación de números aleatorios
    // srand((int) time(0)); // seteamos una semilla con el tiempo actual
                             // para obtener resultados distintos en cada ejecución
    //srand(1);
    
    for (int i=0;i<10;++i) {
        // array2[i] = rand(); // genera números random
        // array2[i] = rand()%10; // para generar números en algún rango (0 y 9)
        // array2[i] = rand()%201 - 100; // entre -100 y 100
        // printf("%i ", array2[i]);
    }
    printf("\n");



    // Algunos datos extras:
    // ======================================
    // // Veamos los punteros de cada array:
    // printf("\nPunteros al array1:\n");
    // printf("array1\t\t %p\n", array1);
    // printf("&array1\t\t %p\n", &array1);
    // printf("&array1[0]\t %p\n\n", &array1[0]);

    // printf("Punteros al array2:\n");
    // printf("array2\t\t %p\n", array2);
    // printf("&array2\t\t %p\n", &array2);
    // printf("&array2[0]\t %p\n\n", &array2[0]);

    // printf("Punteros al array3:\n");
    // printf("array3\t\t %p\n", array3);
    // printf("&array3\t\t %p\n", &array3);
    // printf("&array3[0]\t %p\n\n", &array3[0]);

    // // Acceso al elemento de un array:
    // array2[2] = 10;
    // printf("Le damos un valor a array[2] y accedemos a él:\n");
    // printf("array[2] = %d\n", array2[2]);
    // printf("2[array] = %d\n\n", 2[array2]);
    // ======================================

    // Es necesario liberar las memorias que fueron reservadas con calloc o malloc (heap)
    free(array2);
    free(array3);
    // No es necesario al array1 porque este no reserva memoria en el heap

    // La diferencia entre el primer arreglo y los dos siguientes es que:
    // - El primer arreglo vive en el Stack, que es básicamente la memoria asignada por mi 
    // sistema operativo para mi programa. Es muy útil, aunque tiene algunas limitaciones.
    // - Los otros dos viven en el Heap, el que es memoria extra pedida por mi programa.
    // Este último espacio de memoria tiene la ventaja de que siempre que se le pida, va a crecer, y, si se 
    // libera algún bloque ocupado, entonces se reduce. Luego podemos tener control de cuánta memoria 
    // le pedimos.

    return 0;
}