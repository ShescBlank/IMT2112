/*
Correr código (en consola):
- Compilar: g++ 3flujos.cpp -o name_output
- Correr: ./name_output
*/

#include <stdio.h>
#include <iostream>
using namespace std;

int main() {

    int a, b, c;
    a = 10;
    b = 2;
    c = 5;


    // IF, ELSE IF, ELSE
    printf("\nIF, ELSE IF, ELSE:\n");
    if (a > c)
    {
        printf("a > c\n");
    }
    else if (a == c) {
        printf("a = c\n");
    }
    else { printf("a < c\n"); }


    // FOR
    printf("\nFOR: i++\n");
    for (int i = 0; i < 10; i++)
    {
        cout << i << endl;
    }

    printf("\nFOR: i*=2\n");
    for (int i = 1; i < 10; i*=2)
    {
        cout << i << endl;
    }

    printf("\nFOR: continue\n");
    for (int i = 0; i < 5; i++)
    {
       for (int j = 0; j < 5; j++)
       {
        if (i == j) 
        {
            continue;
        }
        printf("(%d, %d)\n", i, j);
       }
    }

    // WHILE
    printf("\nWHILE:\n");
    while (c < 8) 
    {
        cout << c++ << endl; // Ojo que acá se le está sumando 1 al valor de la variable c en cada llamado
        // cout << ++c << endl; // Qué diferencia hay con esta forma?
    }
    cout << "Valor de c fuera del while: "<< c << endl;

    printf("\nWHILE: true y break\n");
    while (true) 
    {
        b -= 1;
        if (b == -10)
        {
            printf("Rompemos el while\n");
            break;
        }
        printf("Siguiente iteración...\n");
    }

    
    // SWITCH STATEMENT
    printf("\nSWITCH:\n");
    int variable = 2;

    switch (variable)
    {
        case 0:
            cout << "Falso" << endl;
            break;
    
        case 1:
            cout << "Verdadero" << endl;
            break;
    
        default:
            cout << "Inválido" << endl;
            break;
    }

    printf("\nSWITCH: sin break\n");
    variable = 0;

    switch (variable)
    {
        case 0:
            cout << "Falso" << endl;
        
        case 1:
            cout << "Verdadero" << endl;
        
        default:
            cout << "Inválido" << endl;
    }
    
    return 0;
}