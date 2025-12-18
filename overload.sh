#!/bin/bash
#SBATCH -J overload
#SBATCH -N 1
#SBATCH -n 8
#SBATCH -t 00:02:00
#SBATCH -o overload_%j.out

echo "Job ID: $SLURM_JOB_ID"
echo "Requested: 8 CPUs"
echo "Running stress on 8 cores"
echo "Started at $(date)"

stress --cpu 8 --timeout 60s

echo "Finished at $(date)"