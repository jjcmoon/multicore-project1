#!/bin/bash
#SBATCH --workdir /scratch/ajreynau
#SBATCH --nodes 1
#SBATCH --ntasks 1
#SBATCH --cpus-per-task 1
#SBATCH --mem 1G

echo STARTING AT `date`

./integral 1 100000000 0 1

echo FINISHED at `date`
