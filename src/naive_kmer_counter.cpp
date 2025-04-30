#include <naive_kmer_counter.hpp>
#include <utils.hpp>

std::unordered_map<std::string, int> count_kmers(const std::string& sequence, const int& k) {
    check_edge_cases(sequence, k);
    std::unordered_map<std::string, int> kmer_counts;
    for (int i = 0; i <= static_cast<int>(sequence.size()) - k; i++) {
        std::string kmer = sequence.substr(i, k);
        kmer_counts[kmer]++;
    }
    return kmer_counts;
}