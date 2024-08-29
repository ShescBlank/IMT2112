#include <stdio.h>

int main() {

    int count = 0;
    int lim1 = 10;
    int lim2 = 20;

    for (int i = 0; i < lim1; i++)
    {
        for (int j = 0; j < lim2; i++)
        {
            count++;
        }
    }
    
    printf("El resultado de la cuenta es: %d\n", count);

    return 0;
}