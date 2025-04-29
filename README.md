# K-mer Counter (Naive, OpenMP, and OpenMP+MPI)

This project explores the design of scalable k-mer counting algorithms for large FASTA datasets, leveraging shared-memory parallelism (OpenMP) and distributed-memory parallelism (MPI). Focus: efficiency, scalability, and clean reproducibility.

This project implements several parallel versions of a k-mer counter for FASTA files:

- Naive single-threaded C++ implementation
- OpenMP parallel multithreaded implementation
- OpenMP + MPI distributed memory parallel implementation

A **k-mer counter** is important in bioinformatics for tasks such as genome assembly, metagenomic analysis, and sequence alignment. Counting k-mers efficiently enables rapid comparison, error correction, and data compression of sequencing data.

---
## Docker Implementation Coming!

## Building

Example compile command (modify as needed for your system):

```bash
mpic++ -fopenmp kmer_counter.cpp -o kmer_counter
```

Or if using Clang on Mac:

```bash
clang++ -Xpreprocessor -fopenmp -lomp kmer_counter.cpp -o kmer_counter
```

---

## Running

Naive or OpenMP-only version:

```bash
./kmer_counter_naive <number_for_k> <path_to_fasta_file>
./kmer_counter_openmp <number_for_k> <path_to_fasta_file>
```

MPI + OpenMP version:

```bash
mpiexec -n <num_ranks> ./kmer_counter_openmp_mpi <number_for_k> <path_to_fasta_file>
```

---

## Example

```bash
mpiexec -n 4 ./kmer_counter geneX.fasta
```

This will output all k-mers and their counts, along with the time taken.

---

## Notes

- OpenMP speeds up counting within each rank.
- MPI distributes the sequence and workload across multiple processes.

This setup allows exploration of scaling behavior from single-core to multi-core to multi-node architectures.

