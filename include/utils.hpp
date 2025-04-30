#include <string>
#include <fstream>

std::string read_fasta(const std::string& fasta_filepath);
void check_edge_cases(const std::string& sequence, const int& k);