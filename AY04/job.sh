#!/bin/bash

#SBATCH --partition=full

#SBATCH --job-name=IMT2112
#SBATCH --output=log.out

#SBATCH --ntasks=1
#SBATCH --cpus-per-task=1

g++ 1punteros.cpp
./a.out