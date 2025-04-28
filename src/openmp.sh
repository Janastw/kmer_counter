#!/bin/bash

if [ -z "$1" ]; then
    echo "Provide fasta filepath"
    exit 1
fi

./kmer_counter_openmp $1