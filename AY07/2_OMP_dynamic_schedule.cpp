/*
Comandos útiles:
Compilar código:    g++ -o a2.out 2_OMP_dynamic_schedule.cpp -fopenmp
Correr código:      ./a2.out
Podemos correrlo con time (antes del ./a2.out) para ver cuánto se demora en total.
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "iostream"
#include <unistd.h> // Sleep

using namespace std;
 
int main() {

    #pragma omp parallel for num_threads(4) schedule(dynamic)
    for (int i = 1; i < 20; i++) {
        int id = omp_get_thread_num();
        sleep(i);
        cout << "Thread " << id << " durmió " << i << " segundos ZzZ..." << endl;
    }

    return 0;
}
