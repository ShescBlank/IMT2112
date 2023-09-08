/*
Correr código (en consola):
- Compilar: g++ 1punteros.cpp -o name_output
- Correr: ./name_output
*/

#include <stdio.h>

int suma1(int x)
{ 
  x += 1;
  return x;
}

void actualizar(int* x) // no retorna nada
{ 
  *x += 1; // modifico la variable desde dentro de una función mediante su puntero
  // Notar que se usa * por la izquierda para acceder al valor apuntado
}

int main() {
  
  int a = 5;

  // Al crear la variable anterior, podemos acceder a su puntero:
  int* b = &a;

  // Recordar que para acceder al puntero se usa &
  // Y se debe declarar el tipo de puntero que estamos guardando, en este caso, puntero a int

  // Gracias al puntero, tenemos otra forma de modificar el valor de una variable
  // Esto será útil en arrays
  printf("Valor de a antes de actualizar: %d\n", a);
  actualizar(b);
  printf("Valor de a después de actualizar: %d\n\n", a);

  // Notar que si usamos la función suma, el valor de a no se modifica
  printf("Valor de a antes de suma1: %d\n", a);
  suma1(a);
  printf("Valor de a después de suma1: %d\n\n", a);

  // Ahora, si podemos retornarlo y actualizar el valor
  printf("Valor de a antes de suma1 con retorno: %d\n", a);
  a = suma1(a);
  printf("Valor de a después de suma1 con retorno: %d\n", a);

  return 0;
}















