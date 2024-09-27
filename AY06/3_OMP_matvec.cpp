/*
Comandos útiles:
Compilar código:    g++ -o name_output 3_OMP_matvec.cpp -fopenmp
Correr código:      ./name_output
*/

#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <omp.h>

// Función que genera un vector de largo n con valores entre -rango y +rango
float* vector_generator(int n, int range)
{
    float* vector = (float*) calloc(n, sizeof(float));
    
    for (int i=0; i<n; i++)
    {
        vector[i] = (2*range * ((float)rand() / (float)RAND_MAX)) - range;
    }

    return vector;
}

// Función que imprime en consola un vector
void print_vector(float* vector, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%f\t", vector[i]);
    }
    printf("\n\n");
}

// Función que genera una matriz cuadrada de dim n y valores entre -rango y rango
float** matrix_generator(int n, int range)
{
    float** matrix = (float**) calloc(n, sizeof(float*));

    for (int i = 0; i < n; i++)
    {
        matrix[i] = (float*) calloc(n, sizeof(float));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = (2*range * ((float)rand() / (float)RAND_MAX)) - range;

        }
    }

    return matrix;
}

// Función que imprime en consola una matriz
void print_matrix(float** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f\t", matrix[i][j]); 
        }
        printf("\n");
    }
    printf("\n");
}

// Función que libera la memoria reservada de una matriz de nxn
void free_matrix(float** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

// Función que implementa una operación matriz x vector de dim n
float* mat_vec(float** matrix, float* vector, int n)
{
    float* result = (float*)calloc(n, sizeof(float));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }
    return result;
}

// Versión paralela de una función que implementa una operación matriz x vector de dim n
float* mat_vec_par(float **matrix, float *vector, int n)
{
    float *result = (float*)calloc(n, sizeof(float));

    #pragma omp parallel for //num_threads(4)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            result[i] += matrix[i][j] * vector[j];
        }
    }
  return result;
}


int main()
{
    // Definimos una semilla
    srand((int)time(0));

    // Decidimos que opción correr del código
    int opcion_a_correr = 1;

    // Hagamos un switch para hacer distintos ejemplos
    // PORQUE PUEDO
    switch (opcion_a_correr)
    {
        case 0: // Veamos un ejemplo sencillo de MATVEC:
        {
            int n = 5; // Dimensión
            int range = 10; // Rango de números (-range a +range)

            // Creamos un vector y una matriz:
            float* vec = vector_generator(n, range);
            float** mat = matrix_generator(n, range);

            // Imprimamos cada estructura:
            printf("Vector de dim %d:\n", n);
            print_vector(vec, n);

            printf("Matriz de dim %d:\n", n);
            print_matrix(mat, n);

            // Calculemos su matvec:
            float* result = mat_vec(mat, vec, n);

            // Imprimamos el resultado:
            printf("Resultado de dim %d:\n", n);
            print_vector(result, n);

            // Y ahora lo mismo pero paralelo:
            float* result2 = mat_vec_par(mat, vec, n);
            printf("Resultado de dim %d:\n", n);
            print_vector(result2, n);

            // No olvidemos liberar la memoria :D
            free(vec);
            free_matrix(mat, n);
            free(result);
            free(result2);

            break;
        }

        case 1: // Hagamos un matvec más pesado
        {
            int n = 10000; // Dimensión
            int range = 100; // Rango de números (-range a +range)

            // Creamos un vector y una matriz:
            float* vec = vector_generator(n, range);
            float** mat = matrix_generator(n, range);

            // Calculemos su matvec y obtengamos el tiempo que tardó en computar:
            auto start = std::chrono::high_resolution_clock::now();
            float* result = mat_vec(mat, vec, n);
            auto end = std::chrono::high_resolution_clock::now();
            auto execution = std::chrono::duration_cast<std::chrono::nanoseconds>( end - start ); 

            // Vemos cuánto se tardó en calcular el resultado
            printf("Tiempo MATVEC normal: %.9f seconds\n", execution.count() * 1e-9);

            // Repitamos el cálculo anterior pero ahora con OpenMP
            start = std::chrono::high_resolution_clock::now();
            float* result2 = mat_vec_par(mat, vec, n);
            end = std::chrono::high_resolution_clock::now();
            execution = std::chrono::duration_cast<std::chrono::nanoseconds>( end - start ); 

            // Vemos cuánto se tardó en calcular el resultado
            printf("Tiempo MATVEC paralelo: %.9f seconds\n", execution.count() * 1e-9);

            // No olvidemos liberar la memoria :D
            free(vec);
            free_matrix(mat, n);
            free(result);
            free(result2);

            break;
        }

        default:
            printf("default");
            break;
    }

    return 0;
}