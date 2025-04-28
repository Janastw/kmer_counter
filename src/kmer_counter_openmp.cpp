#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <omp.h>
#include <vector>

std::string read_fasta(const std::string& fasta_filepath) {
    std::ifstream file(fasta_filepath);
    std::string line, sequence;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '>') continue;
        sequence += line;
    }
    file.close();
    return sequence;
}

std::unordered_map<std::string, int> omp_count_kmers(const std::string& sequence, int k) {
    int num_threads = omp_get_max_threads();
    std::vector<std::unordered_map<std::string, int> > thread_maps(num_threads);

    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        auto& local_map = thread_maps[tid];

        #pragma omp for
        for (int i = 0; i <= static_cast<int>(sequence.size()) - k; i++) {
            std::string kmer = sequence.substr(i, k);
            local_map[kmer]++;
        }
    }

    // Merge thread maps
    std::unordered_map<std::string, int> merged_map;
    for (const auto& thread_map : thread_maps) {
        for (const auto& p : thread_map) {
            merged_map[p.first] += p.second;
        }
    }
    return merged_map;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        throw std::runtime_error("Filepath must be provided");
    }
    std::string filepath = argv[1];
    int k = 3;

    auto start = std::chrono::high_resolution_clock::now();

    std::string sequence = read_fasta(filepath);
    auto kmer_counts = omp_count_kmers(sequence, k);

    auto end = std::chrono::high_resolution_clock::now();

    for (const auto& pair : kmer_counts) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}