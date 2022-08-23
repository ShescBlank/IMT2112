#include <stdio.h>

int main() {
  
    int a = 1; // Debemos declarar el tipo de variable
    int b; 
    b = 3;
    float c = 8;
    bool terminado = false;

    if (a+b > 2  && a%2 == 1) {
        printf("a+b = %i\n", a+b); // Inyectar un int
    }
    else if (a+b == 2 || c == 8) { // Este de acá es un or
        printf("c = %f, %f\n", c, c); // Inyectar dos floats
    }
    else {
        // el else vacío no importa
    }

    for (int i=0; i<10; i++) { // el i++ es sumarle 1 al final de cada iteración
        a += 1;
    }
    printf("a = %i\n", a);


    while (!terminado) { // not terminado
        b += 1;
        if (b % 4 == 0) {
            terminado = true;
        }
    }
    
    return 0;
}