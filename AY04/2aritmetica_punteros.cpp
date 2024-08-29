/*
Correr código (en consola):
- Compilar: g++ 2aritmetica_punteros.cpp -o name_output
- Correr: ./name_output
*/

#include <stdio.h>
#include <stdint.h>

int main() {
    // Creemos dos variables int
    int a = 1;
    int b = 2;
    printf("a = %d\n", a);
    printf("b = %d\n\n", b);
    
    // Veamos su puntero
    printf("Puntero de a: %p\n", &a); // Se puede observar que los punteros están en formato hexadecimal
    printf("Puntero de b: %p\n", &b);

    // La distancia de ambos punteros es 4, cuál es el tamaño en bytes de un int?
    printf("Tamaño en bytes de un int: %zu\n", sizeof(int));

    // Qué ocurre si le sumamos 1 al puntero de a, llegamos a b?
    printf("\nPuntero + 1 de a: %p\n", &a + 1);

    // Efectivamente llegamos, entonces podemos acceder al valor de b
    printf("Valor de b mediante el puntero de a: %d\n", *(&a + 1));

    // Probemos con otros tipos de datos
    char c = 'c';
    char d = 'd';
    printf("\nCHAR\n");
    printf("Puntero de c: %p\n", &c);
    printf("Puntero de d: %p\n", &d);
    printf("Tamaño en bytes de un char: %zu\n", sizeof(char));


    double e = 0.1;
    double f = 0.123;
    printf("\nDOUBLE\n");
    printf("Puntero de e: %p\n", &e);
    printf("Puntero de f: %p\n", &f);
    printf("Tamaño en bytes de un double: %zu\n", sizeof(double));

    return 0;
}