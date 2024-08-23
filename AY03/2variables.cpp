/*
Correr código (en consola):
- Compilar: g++ 2variables.cpp -o name_output
- Correr: ./name_output
*/

#include <stdio.h>
#include <iostream>
using namespace std;

int main() {
    
    // Para utilizar variables debemos definir su tipo
    
    // INT:
    printf("INT:\n");
    int a = 9;
    int b;
    b = 10;
    printf("La suma de %i y %d es: %d\n", a, b, a+b);
    cout << "La multiplicación de " << a << " y " << b << " es: " << a*b << endl;

    // FLOAT:
    printf("\nFLOAT:\n");
    float c = 10.2, d = 3.1;
    printf("c*d=%f\n", c*d);

    // CASTING:
    printf("\nCASTING:\n");
    printf("División sin casting: %d/%d=%f\n", a, b, a/b);
    float result = (float)a/b;
    printf("División con casting: %d/%d=%f\n", a, b, result);

    // DOUBLE:
    printf("\nDOUBLE:\n");
    float pi2 = 3.14159265358979323846;
    printf("%f\n", pi2);
    double pi = 3.14159265358979323846;
    printf("%lf\n", pi);

    // BOOLEANS:
    printf("\nBOOLEANS:\n");
    bool e = true;
    bool f = false;
    bool g = !(e || f);
    bool h = g && f;
    printf("True: %d\n", e);
    printf("False: %d\n", f);
    printf("!(T || F)=%d\nF && F=%d\n", g, h);

    return 0;
}