#include <mpi_openmp_kmer_counter.hpp>

bool run_mpi_init() {
    bool i_initialized_mpi = false;

    int initialized = 0;
    MPI_Initialized(&initialized);
    if (!initialized) {
        MPI_Init(nullptr, nullptr);
        i_initialized_mpi = true;
    }

    return i_initialized_mpi;
}

void run_mpi_finalize(bool mpi_init_ran) {
    if (mpi_init_ran) {
        MPI_Finalize();
    }
}

// Openmp portion inside of each rank
std::unordered_map<std::string, int> omp_count_kmers(const std::string& sequence, int k) {
    int num_threads = omp_get_max_threads();
    std::vector<std::unordered_map<std::string, int> > thread_maps(num_threads);
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();

        #pragma omp for
        for (int i = 0; i <= sequence.length() - k; i++) {
            std::string kmer = sequence.substr(i, k);
            thread_maps[tid][kmer] += 1;
        }
    }

    std::unordered_map<std::string, int> merged_maps;

    for (auto& map : thread_maps) {
        for (auto& kmer : map) {
            merged_maps[kmer.first] += kmer.second;
        }
    }
    return merged_maps;
}

void merge_maps(std::unordered_map<std::string, int>& target, const std::unordered_map<std::string, int>& source) {
    for (const auto& p: source) {
        target[p.first] += p.second;
    }
}

std::pair<std::vector<char>, std::vector<int> > serialize_map(const std::unordered_map<std::string, int>& map) {
    std::vector<char> flattened_kmers;
    std::vector<int> kmer_counts;

    for (const auto& p : map) {
        flattened_kmers.insert(flattened_kmers.end(), p.first.begin(), p.first.end());
        kmer_counts.emplace_back(p.second);
    }

    return std::make_pair(flattened_kmers, kmer_counts);

}

std::unordered_map<std::string, int> deserialize_map(const std::vector<char>& flattened_kmers, const std::vector<int> kmer_counts, const int& k) {
    int num_threads = omp_get_max_threads();
    std::vector<std::unordered_map<std::string, int> > thread_maps(num_threads);
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        for (int i = 0; i < kmer_counts.size(); i++) {
            std::string kmer(flattened_kmers.begin() + i * k, flattened_kmers.begin() + (i + 1) * k);
            thread_maps[tid][kmer] += kmer_counts.at(i);
        }
    }

    std::unordered_map<std::string, int> merged_map;

    for (auto& map : thread_maps) {
        for (auto& kmer : map) {
            merged_map[kmer.first] += kmer.second;
        }
    }

    return merged_map;
}

std::unordered_map<std::string, int> count_kmers(const std::string& sequence, const int& k) {
    bool check_mpi_init = run_mpi_init();

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int sequence_size = sequence.size();

    int base_chunk_size = sequence.size() / size;
    int starting_index = base_chunk_size * rank;
    int ending_index = base_chunk_size * (rank + 1) - 1;

    int ghost_left = (rank == 0) ? 0 : (k - 1);
    int ghost_right = (rank == size - 1) ? 0 : (k - 1);

    int local_start = std::max(0, starting_index - ghost_left);
    int local_end = std::min(sequence_size ,ending_index + ghost_right);

    std::string local_sequence = sequence.substr(local_start, local_end - local_start);

    // Each rank has their own local map
    std::unordered_map<std::string, int> local_map = omp_count_kmers(local_sequence, k);
    // Each local map must be flattened before being sent to rank 0
    // THIS IS WHAT WE NEED TO SEND TO RANK 0. 
    auto [local_flattened_kmers, local_kmer_counts] = serialize_map(local_map);

    // Now we have the sizes of what we are going to send
    int local_flattened_kmers_size = local_flattened_kmers.size();
    int local_kmer_counts_size = local_kmer_counts.size();

    // Counts for rank 0 to receive
    std::vector<int> recv_counts(size);
    std::vector<int> recv_flattened_kmers_sizes(size);
    MPI_Gather(&local_kmer_counts_size, 1, MPI_INT, recv_counts.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gather(&local_flattened_kmers_size, 1, MPI_INT, recv_flattened_kmers_sizes.data(), 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Build displacements for incoming flattened_kmers to be received
    std::vector<int> flattened_displacements(size);
    std::vector<int> count_displacements(size);
    int total_flattened_size = 0;
    int total_counts_size = 0;
    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            flattened_displacements[i] = total_flattened_size;
            total_flattened_size += recv_flattened_kmers_sizes[i];

            count_displacements[i] = total_counts_size;
            total_counts_size += recv_counts[i];
        }
    }

    std::vector<char> global_flattened_kmers;
    std::vector<int> global_kmer_counts;
    if (rank == 0){
        global_flattened_kmers.resize(total_flattened_size);
        global_kmer_counts.resize(total_counts_size);
    }
    MPI_Gatherv(local_kmer_counts.data(), local_kmer_counts_size, MPI_INT, global_kmer_counts.data(), recv_counts.data(), count_displacements.data(), MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gatherv(local_flattened_kmers.data(), local_flattened_kmers_size, MPI_CHAR, global_flattened_kmers.data(), recv_flattened_kmers_sizes.data(), flattened_displacements.data(), MPI_CHAR, 0, MPI_COMM_WORLD);

    std::unordered_map<std::string, int> global_kmer_map;
    if (rank == 0) {
        global_kmer_map = deserialize_map(global_flattened_kmers, global_kmer_counts, k);
    }

    run_mpi_finalize(check_mpi_init);

    return global_kmer_map;
}