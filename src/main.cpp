#include <string>
#include <chrono>
#include <iostream>
#include <exception>
#include "naive_kmer_counter.hpp"
#include "utils.hpp"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        throw std::runtime_error("Filepath must be provided");
    }
    std::string filepath = argv[2];
    int k = std::stoi(argv[1]);

    auto start = std::chrono::high_resolution_clock::now();

    std::string sequence = read_fasta(filepath);
    check_edge_cases(sequence, k);
    auto kmer_counts = count_kmers(sequence, k);

    auto end = std::chrono::high_resolution_clock::now();

    for (const auto& pair : kmer_counts) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}