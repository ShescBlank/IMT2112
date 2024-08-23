/*
Correr código (en consola):
- Compilar: g++ 4punteros.cpp -o name_output
- Correr: ./name_output
*/

#include <stdio.h>

int main() {
  // Declaremos un int y démosle un valor
  int a = 4;

  // Declaremos un puntero, en este caso es un puntero a un valor int
  int* b;

  // Hagamos que el valor de b sea el puntero de a (anteponer & para acceder al puntero de una variable)
  b = &a;

  printf("Mi valor es %d y mi puntero es %p\n", a, b);

  // Los punteros tienen muchas utilidades ya que podemos utilizarlos para acceder al valor guardado en memoria:
  // (* a la izquierda de la variable para acceder al valor apuntado)
  *b += 1;

  printf("Mi valor es %d y mi puntero es %p\n", a, b);

  // También podemos hacer punteros de punteros
  int** c = &b;

  // Nuevamente podemos utilizarlo para modificar a:
  *(*c) += 1;

  printf("Mi valor es %d y mi puntero es %p y el puntero de mi puntero es %p\n", a, b, c);

  return 0;
}