cmake_minimum_required(VERSION 3.10)
project(kmer_counter_project)

find_package(MPI REQUIRED)
find_package(OpenMP REQUIRED)

add_executable(naive_kmer_counter src/naive_kmer_counter.cpp)
add_executable(openmp_kmer_counter src/openmp_kmer_counter.cpp)
add_executable(mpi_openmp_kmer_counter src/mpi_openmp_kmer_counter.cpp)

target_link_libraries(openmp_kmer_counter PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(mpi_openmp_kmer_counter PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(mpi_openmp_kmer_counter PUBLIC MPI::MPI_CXX)

# Will enable later
# enable_testing()
# add_executable(kmer_tests tests/test_count_kmers.cpp tests/test_kmer_utils.cpp)
# target_link_libraries(kmer_tests PUBLIC gtest gtest_main)
# add_test(NAME kmer_tests COMMAND kmer_tests)