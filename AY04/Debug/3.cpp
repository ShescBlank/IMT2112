#include <stdio.h>
#include <stdlib.h> 

int main() {

    int length1 = 10;
    int length2 = 5;
    int** arrays = (int**)calloc(length1, sizeof(int*));

    for (int i = 0; i < length1; ++i)
    {
        arrays[i] = (int*)malloc(length2 * sizeof(int));

        for (int j = 0; j < length2; j++)
        {
            arrays[i][j] = j*i;
        }
    }

    free(arrays);

    return 0;
}