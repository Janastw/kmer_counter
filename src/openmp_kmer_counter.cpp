#include <openmp_kmer_counter.hpp>

std::unordered_map<std::string, int> count_kmers(const std::string& sequence, int k) {
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