#!/bin/bash

docker run -it --rm \
    --name kmer_counter_dev \
    -v "$(pwd)":/workspace \
    -w /workspace \
    kmer-counter /bin/bash