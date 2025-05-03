#ifndef NAIVE_KMER_COUNTER_HPP
#define NAIVE_KMER_COUNTER_HPP

#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> count_kmers(const std::string& sequence, const int& k);

#endif