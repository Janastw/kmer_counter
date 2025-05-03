find_package(MPI)
find_package(OpenMP)

add_executable(kmer_naive_tests test_naive.cpp)
target_include_directories(kmer_naive_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(kmer_naive_tests PRIVATE gtest gtest_main naive_kmer_counter)
add_test(NAME kmer_naive_tests COMMAND kmer_naive_tests)

add_executable(kmer_openmp_tests test_openmp.cpp)
target_include_directories(kmer_openmp_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(kmer_openmp_tests PRIVATE gtest gtest_main openmp_kmer_counter OpenMP::OpenMP_CXX )
add_test(NAME kmer_openmp_tests COMMAND kmer_openmp_tests)

add_executable(kmer_mpi_openmp_tests test_mpi.cpp)
target_include_directories(kmer_mpi_openmp_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(kmer_mpi_openmp_tests PRIVATE gtest gtest_main mpi_openmp_kmer_counter OpenMP::OpenMP_CXX MPI::MPI_CXX )
add_test(NAME kmer_mpi_openmp_tests COMMAND ${MPIEXEC_EXECUTABLE} ${MPIEXEC_NUMPROC_FLAG} 2 ./kmer_mpi_openmp_tests)