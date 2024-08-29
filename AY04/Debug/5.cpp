#include <stdio.h>
#include <stdlib.h> 

int* create_array(int n)
{
    int array[n];
    for (int i = 0; i < n; i++)
    {
        array[i] = i;
    }
    return array;
}

int main() {

    // Creemos un array con la función anterior
    int n = 10;

    // Nos retorna un puntero de int
    int* array1 = create_array(n);

    // Imprimamos sus elementos para ver que todo esté bien
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array1[i]);
    }
    printf("\n");

    // Ahora creemos otro array
    int* array2 = create_array(n);

    // E imprimamos
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array2[i]);
    }
    printf("\n");

    return 0;
}