/*
Correr código (en consola):
- Compilar: g++ 1hello_world.cpp -o name_output
- Correr: ./name_output
*/

// Incluimos la librería standard I/O
#include <stdio.h> // incluye al printf

// Las dos líneas siguientes son para el cout
#include <iostream>
using namespace std;

// La función main es la que se ejecuta cuando se corre el código
int main() {

    printf("Hello World\n"); // printf no tiene salto de línea

    // "\n" representa un salto de línea
    // "\t" representa un tab (4 espacios)

    cout << "Hello " << "World";
    cout << " 2" << endl; // endl agrega el salto de línea

    // Debemos retornar un número porque así fue definido main
    return 0;
}