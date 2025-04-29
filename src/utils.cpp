#include <utils.hpp>

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