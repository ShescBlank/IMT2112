/*
Correr código (en consola):
- Compilar: g++ 5funciones.cpp -o name_output
- Correr: ./name_output
*/

#include <stdio.h>

int suma(int x1, int x2)
{ 
  x1 += 1;
  x2 += 2;
  return x1 + x2;
}

void actualizar(int* x) // no retorna nada
{ 
  *x = 1; // modifico la variable desde dentro de una función mediante su puntero
}

float promedio(float x, float y, float z)
{
  return (x + y + z) / 3;
}

int main() {
  
  int a = 5;
  int b = 10;

  printf("a = %d (antes de actualizar())\n", a);

  actualizar(&a);

  printf("a = %d (después de actualizar())\n\n", a);

  int c = suma(a, b); // no modifica a y b ya que crea una copia de ellas en la función

  printf("Valores finales:\n");
  printf("a = %d\n", a); // Notar que a y b no se modifican en la función suma
  printf("b = %d\n", b);
  printf("c = %d\n", c);
  printf("Promedio = %f\n", promedio(1.1, 5.7, 13.59));

  return 0;
}















