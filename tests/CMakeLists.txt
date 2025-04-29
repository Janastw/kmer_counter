find_package(MPI)
find_package(OpenMP)

add_executable(kmer_tests test_naive.cpp ${PROJECT_SOURCE_DIR}/src/naive_kmer_counter.cpp)
target_include_directories(kmer_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(kmer_tests PRIVATE gtest gtest_main)
add_test(NAME kmer_tests COMMAND kmer_tests)

add_executable(kmer_openmp_tests test_mpi.cpp ${PROJECT_SOURCE_DIR}/src/openmp_kmer_counter.cpp)
target_include_directories(kmer_openmp_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(kmer_openmp_tests PRIVATE gtest gtest_main OpenMP::OpenMP_CXX)
add_test(NAME kmer_openmp_tests COMMAND kmer_openmp_tests)

add_executable(kmer_mpi_tests test_mpi.cpp ${PROJECT_SOURCE_DIR}/src/mpi_openmp_kmer_counter.cpp)
target_include_directories(kmer_mpi_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(kmer_mpi_tests PRIVATE gtest gtest_main OpenMP::OpenMP_CXX MPI::MPI_CXX)
add_test(NAME kmer_mpi_tests COMMAND ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} 4 ./kmer_mpi_tests)