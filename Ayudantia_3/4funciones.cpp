#include <stdio.h>

int suma(int x1, int x2) { // recibe dos ints
  x1 += 1;
  x2 += 2;
  return x1 + x2;
}

void actualizar(int* x) { // no retorna nada
  *x = 1; // modifico la variable desde dentro de una función mediante su puntero
}

int main() {
  
  int a = 5;
  int b = 10;
  int c;

  actualizar(&a);

  c = suma(a,b); // no modifica a y b


  printf("a = %i\n", a);
  printf("b = %i\n", b);
  printf("c = %i\n", c);

  return 0;
}















