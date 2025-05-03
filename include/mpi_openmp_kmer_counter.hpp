#ifndef MPI_OPENMP_KMER_COUNTER_HPP
#define MPI_OPENMP_KMER_COUNTER_HPP

#include <unordered_map>
#include <string>
#include <chrono>
#include <vector>
#include <omp.h>
#include <mpi.h>

bool run_mpi_init();
void run_mpi_finalize(bool mpi_init_ran);
std::unordered_map<std::string, int> omp_count_kmers(const std::string& sequence, int k);
void merge_maps(std::unordered_map<std::string, int>& target, const std::unordered_map<std::string, int>& source);
std::pair<std::vector<char>, std::vector<int> > serialize_map(const std::unordered_map<std::string, int>& map);
std::unordered_map<std::string, int> deserialize_map(const std::vector<char>& flattened_kmers, const std::vector<int> kmer_counts, const int& k);
std::unordered_map<std::string, int> count_kmers(const std::string& fasta_filepath, const int& k);

#endif