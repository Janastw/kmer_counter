#include <string>
#include <unordered_map>
#include <gtest/gtest.h>
#include <mpi_openmp_kmer_counter.hpp>


static std::string simple_sequence = "ABCDEFG";
static std::unordered_map<std::string, int> simple_onemer_map = {
    {"A", 1},
    {"B", 1},
    {"C", 1},
    {"D", 1},
    {"E", 1},
    {"F", 1},
    {"G", 1}
};
static std::unordered_map<std::string, int> simple_threemer_map = {
    {"ABC", 1},
    {"BCD", 1},
    {"CDE", 1},
    {"DEF", 1},
    {"EFG", 1}
};
static std::unordered_map<std::string, int> simple_fivemer_map = {
    {"ABCDE", 1},
    {"BCDEF", 1},
    {"CDEFG", 1}
};

static std::string repeated_sequence = "ABCDABCDAB";
static std::unordered_map<std::string, int> repeated_onemer_map = {
    {"A", 3},
    {"B", 3},
    {"C", 2},
    {"D", 2},
};
static std::unordered_map<std::string, int> repeated_threemer_map = {
    {"ABC", 2},
    {"BCD", 2},
    {"CDA", 2},
    {"DAB", 2},
};
static std::unordered_map<std::string, int> repeated_fivemer_map = {
    {"ABCDA", 2},
    {"BCDAB", 2},
    {"CDABC", 1},
    {"DABCD", 1},
};

/**** MPI/OpenMP Kmer Counter Tests ****/

TEST(MPI_OPENMP_TESTS, MPI_OpenMP_ShortOnemerTest) {
    EXPECT_EQ(count_kmers(simple_sequence, 1), simple_onemer_map);
}
TEST(MPI_OPENMP_TESTS, MPI_OpenMP_ShortThreemerTest) {
    EXPECT_EQ(count_kmers(simple_sequence, 3), simple_threemer_map);
}
TEST(MPI_OPENMP_TESTS, MPI_OpenMP_ShortFivemerTest) {
    EXPECT_EQ(count_kmers(simple_sequence, 5), simple_fivemer_map);
}
TEST(MPI_OPENMP_TESTS, MPI_OpenMP_RepeatedOnemerTest) {
    EXPECT_EQ(count_kmers(repeated_sequence, 1), repeated_onemer_map);
}
TEST(MPI_OPENMP_TESTS, MPI_OpenMP_RepeatedThreemerTest) {
    EXPECT_EQ(count_kmers(repeated_sequence, 3), repeated_threemer_map);
}
TEST(MPI_OPENMP_TESTS, MPI_OpenMP_RepeatedFivemerTest) {
    EXPECT_EQ(count_kmers(repeated_sequence, 5), repeated_fivemer_map);
}

TEST(MPI_OPENMP_TESTS, NegativeMPI_OpenMP_ShortOnemerTest) {
    EXPECT_NE(count_kmers(simple_sequence, 1), simple_threemer_map);
}
TEST(MPI_OPENMP_TESTS, NegativeMPI_OpenMP_RepeatedOnemerTest) {
    EXPECT_NE(count_kmers(repeated_sequence, 1), repeated_threemer_map);
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    ::testing::InitGoogleTest(&argc, argv);
    // Silence output from non-root ranks
    if (world_rank != 0) {
        ::testing::GTEST_FLAG(output) = "";
        ::testing::GTEST_FLAG(also_run_disabled_tests) = false;
        // Redirect stdout/stderr
        freopen("/dev/null", "w", stdout);
        freopen("/dev/null", "w", stderr);
    }
    int result = RUN_ALL_TESTS();

    MPI_Finalize();

    if (world_rank == 0) {
        return result;
    } else {
        return 0;
    }
}