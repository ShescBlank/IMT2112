#include <stdio.h> // "librería" del printf

#include <iostream> // Estos dos son para el cout
using namespace std;

int main() { // El main es obligatirio en c++

    printf("Hello World\n"); // printf no tiene salto de línea

    cout << "Hello " << "World";
    cout << " 2" << endl; // endl agrega el salto de línea

    return 0; // Tiene un return porque le dijimos que la función retorna un int
}