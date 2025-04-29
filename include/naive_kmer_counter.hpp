#pragma once
#include <string>
#include <unordered_map>

std::unordered_map<std::string, int> count_kmers(const std::string& sequence, int k);