#include <string>
#include <unordered_map>
#include <gtest/gtest.h>
#include <openmp_kmer_counter.hpp>

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

/**** OpenMP Kmer Counter Tests ****/

TEST(OPENMP_TESTS, OpenMP_ShortOnemerTest) {
    EXPECT_EQ(count_kmers(simple_sequence, 1), simple_onemer_map);
}
TEST(OPENMP_TESTS, OpenMP_ShortThreemerTest) {
    EXPECT_EQ(count_kmers(simple_sequence, 3), simple_threemer_map);
}
TEST(OPENMP_TESTS, OpenMP_ShortFivemerTest) {
    EXPECT_EQ(count_kmers(simple_sequence, 5), simple_fivemer_map);
}
TEST(OPENMP_TESTS, OpenMP_RepeatedOnemerTest) {
    EXPECT_EQ(count_kmers(repeated_sequence, 1), repeated_onemer_map);
}
TEST(OPENMP_TESTS, OpenMP_RepeatedThreemerTest) {
    EXPECT_EQ(count_kmers(repeated_sequence, 3), repeated_threemer_map);
}
TEST(OPENMP_TESTS, OpenMP_RepeatedFivemerTest) {
    EXPECT_EQ(count_kmers(repeated_sequence, 5), repeated_fivemer_map);
}

TEST(OPENMP_TESTS, tiveMPI_OpenMP_ShortOnemerTest) {
    EXPECT_NE(count_kmers(simple_sequence, 1), simple_threemer_map);
}
TEST(OPENMP_TESTS, tiveMPI_OpenMP_RepeatedOnemerTest) {
    EXPECT_NE(count_kmers(repeated_sequence, 1), repeated_threemer_map);
}