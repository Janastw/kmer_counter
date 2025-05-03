#include "utils.hpp"

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

void check_edge_cases(const std::string& sequence, const int& k) {
    if (k <= 0) {
        throw std::runtime_error("K cannot be less than or equal to 0. Please provide a positive integer for k");
    }
    if (sequence.empty()) {
        throw std::runtime_error("Sequence is empty! Ensure Fasta is populated and formatted correctly!");
    }
    if (sequence.size() < k) {
        throw std::runtime_error("Sequence is smaller than k. \nPlease provide a smaller k, check the Fasta formatting, or provide a separate Fasta");
    }
}