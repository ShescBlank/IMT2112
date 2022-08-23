#include <stdio.h>

int main() {
  int a; // int
  int* b; // puntero

  a = 1;
  b = &a; // dirección de memoria de a
  
  a += 1;
  *b += 3; // le sumamos 3 a lo que esté guardado en la dirección de memoria de b

  // entonces a = 5

  printf("a = %i \n", a);
  printf("La direccion donde esta guardado a es: %p \n", &a);
  printf("b = %p \n", b); // printear variable de tipo puntero
  printf("El numero guardado en la direccion apuntada por b es: %i \n", *b);
   
  return 0;
}