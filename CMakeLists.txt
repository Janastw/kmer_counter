cmake_minimum_required(VERSION 3.10)
project(kmer_counter_project)
set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)
find_package(OpenMP REQUIRED)

add_library(naive_kmer_counter src/naive_kmer_counter.cpp src/utils.cpp)
add_library(openmp_kmer_counter src/openmp_kmer_counter.cpp src/utils.cpp)
add_library(mpi_openmp_kmer_counter src/mpi_openmp_kmer_counter.cpp src/utils.cpp)

target_include_directories(naive_kmer_counter PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(openmp_kmer_counter PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(mpi_openmp_kmer_counter PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(openmp_kmer_counter PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(mpi_openmp_kmer_counter PUBLIC OpenMP::OpenMP_CXX)
target_link_libraries(mpi_openmp_kmer_counter PUBLIC MPI::MPI_CXX)

enable_testing()
add_subdirectory(tests)