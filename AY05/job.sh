#!/bin/bash

#SBATCH --partition=full

#SBATCH --job-name=IMT2112
#SBATCH --output=log.out

### Notar que la línea siguiente define la cantidad de procesos que queremos utilizar (no agregamos -np en el mpirun):
#SBATCH --ntasks=4
#SBATCH --cpus-per-task=1

mpic++ 1MPI_hello_world.cpp -std=c++11
mpirun ./a.out