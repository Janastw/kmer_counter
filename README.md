# 🔬 K-mer Counter (Naive, OpenMP, and OpenMP+MPI)

This project explores the design of scalable k-mer counting algorithms for large FASTA datasets using:

- ✅ leveraging shared-memory parallelism (OpenMP)
- ✅ Naive single-threaded C++ implementation
- ✅ OpenMP + MPI (distributed memory parallel implementation )

Each version is now built as a separate **library**, with a unified interface planned for benchmarking and testing.

Focus on :
efficiency.
scalability.
clean reproducibility.

> A **k-mer counter** is important in bioinformatics for tasks such as genome assembly, metagenomic analysis, and sequence alignment. Counting k-mers efficiently enables rapid comparison, error correction, and data compression of sequencing data.

---

## 🚀 Features

- counts k-mers from FASTA files
- Parallel execution with OpenMP
- Distributed execution with MPI
- Easily switch between naive,OpenMp, and MPI versions

## ⚙️ Building Instructions

### Requirements

- C++17 compatible compiler (e.g., g++,clang++)
- OpenMP and MPI (e.g.libomp-dev,openmpi)
- Docker -for containerized builds

### 🧪 compile Example command

(modify as needed for your system):

bash
mpic++ -fopenmp kmer_counter.cpp -o kmer_counter

Or if using Clang on MacOS:

bash
clang++ -Xpreprocessor -fopenmp -lomp kmer_counter.cpp -o kmer_counter

---

## 📈 Usage

## ✅ Naive or OpenMP-only version:

```bash
./kmer_counter_naive <number_for_k> <path_to_fasta_file>
```

```
./kmer_counter_openmp <number_for_k> <path_to_fasta_file>
```

## ✅ MPI + OpenMP version:

```bash
mpiexec -n <num_ranks> ./kmer_counter_openmp_mpi <number_for_k> <path_to_fasta_file>
```

---

### 🧪Example

```bash
mpiexec -n 4 ./kmer_counter geneX.fasta
```

This will output all k-mers and their counts, along with the time taken.

---

## 🌱 Notes

- OpenMP speeds up counting within each rank.
- MPI distributes the sequence and workload across multiple processes.

## This setup allows exploration of scaling behavior from single-core to multi-core to multi-node architectures.

### 📁 Project Structure

---

<pre>
 kmer_counter/
 ├── include/ # Header files
 ├── src/ # Source files
 | ├──naive/
 | ├──openmp/
 | ├──mpi/
 ├── test/ # Google Tests case
 ├── README.md
 ├── Dockerfiles
 ├── CmakeLists.txt
 ├── Makefile
 └── LICENSE
</pre>

---

## Testing

---

- 1. Run the program with known inputs
- 2. Validate expexted outputs manually
  ***

## Docker Implementation

---

You can build and run the project in a clean environment using Docker.

### 🛠️ Dockerfile Summary

The Docker container includes:

- Ubuntu 22.04
- Build tools (`build-essential`, `cmake`)
- MPI support (`openmpi-bin`, `libopenmpi-dev`)
- Google Test (`libgtest-dev`)
- Git

### 🏗️ Build the Docker Image

From the project root:

bash
docker build -t kmer_counter_env .

### 🧪 Run the Container

```bash
docker run -it --rm kmer_counter_env
```

---

## 🤝 Contributing

---

We welcome to contributors . For small changes:

- Fork the repo.
- Create a new branch.
- Submit a pull request.

For large scale contribution,please open an issue first to discuss.

---

## 📜 License

This project is licensed under the MIT License. See the `LICENSE` file for details.
