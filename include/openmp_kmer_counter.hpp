#pragma once
#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <omp.h>
#include <vector>

std::unordered_map<std::string, int> omp_count_kmers(const std::string& sequence, int k);
