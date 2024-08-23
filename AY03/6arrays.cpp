/*
Correr código (en consola):
- Compilar: g++ 6arrays.cpp -o name_output
- Correr: ./name_output
*/

#include <stdio.h>
#include <stdlib.h> 
#include <ctime>

int main() {
  
    // las listas no vienen nativas, existe array

    // Primera manera de hacerlo: dame un array de tamaño n de ints
    int n = 10;
    int array1[n];
    
    // Segunda manera: puntero de int. calloc es resérvame 10 casilleros 
    // de memoria del tamaño de un int. El (int*) es un casting de int a puntero de int
    int* array2 = (int*) calloc(10, sizeof(int)); // inicializa valores a 0

    // Tercera forma: en malloc solo le damos el tamaño total de lo que quiero reservar
    int* array3 = (int*) malloc(10*sizeof(int)); // no inicializa valores

    for (int i=0; i<10; i++) {
        // printf("%i ", array1[i]);
        // printf("%i ", array2[i]);
        // printf("%i ", array3[i]);
        // printf("\n");
    }
    

    // Números random
    // srand((int) time(0)); // seteamos una semilla con el tiempo actual
                          // esto significa que cambiará bastante seguido
                          // y así obtendremos comportamientos distintos 
                          // al correr de nuevo el código.
    //srand(1);
    
    for (int i=0;i<10;++i) {
        // array2[i] = rand(); // genera números random
        // array2[i] = rand()%10; // para generar números en algún rango (0 y 9)
        //array2[i] = rand()%201 - 100; // entre -100 y 100
        // printf("%i ", array2[i]);
    }

    printf("\n");
    
    // Es necesario liberar las memorias que fueron reservadas con calloc o malloc (HEAP)
    free(array2);
    free(array3);
    // No es necesario al array1 porque este no reserva memoria

    return 0;
}