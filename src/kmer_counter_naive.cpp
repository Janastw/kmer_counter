#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include <chrono>

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

std::unordered_map<std::string, int> naive_count_kmers(const std::string& sequence, int k) {
    std::unordered_map<std::string, int> kmer_counts;
    for (int i = 0; i <= static_cast<int>(sequence.size()) - k; i++) {
        std::string kmer = sequence.substr(i, k);
        kmer_counts[kmer]++;
    }
    return kmer_counts;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        throw std::runtime_error("Filepath must be provided");
    }
    std::string filepath = argv[2];
    int k = std::stoi(argv[1]);

    auto start = std::chrono::high_resolution_clock::now();

    std::string sequence = read_fasta(filepath);
    auto kmer_counts = naive_count_kmers(sequence, k);

    auto end = std::chrono::high_resolution_clock::now();

    for (const auto& pair : kmer_counts) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Time taken: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}