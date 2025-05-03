#ifndef OPENMP_KMER_COUNTER_HPP
#define OPENMP_KMER_COUNTER_HPP

#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <omp.h>
#include <vector>

std::unordered_map<std::string, int> count_kmers(const std::string& sequence, const int& k);

#endif