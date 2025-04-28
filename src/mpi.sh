#!/bin/bash

if [ -z "$1" ]; then
    echo "Provide number for ranks"
    exit 1
fi

if [ -z "$2" ]; then
    echo "Provide fasta filepath"
    exit 1
fi

mpiexec -n $1 ./kmer_counter_mpi_openmp $2