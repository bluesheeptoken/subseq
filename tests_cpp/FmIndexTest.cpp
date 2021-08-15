#include "gtest/gtest.h"
#include "FmIndex.hpp"

class FmIndexTest : public ::testing::Test {
 protected:
    Letters letters = {2, 1, 3, 1, 3, 1, 0};  // banana$
    std::size_t alphabet_size = 4;
    FmIndex fmIndex = FmIndex(letters, alphabet_size);
};

TEST_F(FmIndexTest, constructor) {
    // bnn$aaa, reversed BWT transform
    Letters sorted_letters = {2, 3, 3, 0, 1, 1, 1};
    WaveletTree tree = fmIndex.get_tree();
    for (int i = 0; i < sorted_letters.size(); i++)
        ASSERT_EQ(tree[i], sorted_letters[i]);

    std::vector<int> expected_occurrences = {0, 1, 4, 5};
    std::vector<int> occurrences = fmIndex.get_occurrences();
    for (int i = 0; i < alphabet_size; i++)
        ASSERT_EQ(occurrences[i], expected_occurrences[i]);
}

TEST_F(FmIndexTest, backward_search) {
    Letters query;
    std::pair<int, int> range;

    query = {1, 3, 1};  // ana
    range = fmIndex.backward_search(query);
    ASSERT_EQ(range.first, 2);
    ASSERT_EQ(range.second, 4);

    query = {0, 0};  // $$, should not be find
    range = fmIndex.backward_search(query);
    ASSERT_EQ(range.first, range.second);
}

TEST_F(FmIndexTest, next_candidates) {
    Letters query;
    std::unordered_set<int> actual;

    query = {1, 3};  // an
    actual = fmIndex.next_candidates(query);
    std::unordered_set<int> expected = {1};
    for (auto candidate : actual)
        ASSERT_NE(
            expected.find(candidate),
            expected.end()
        );
}

TEST_F(FmIndexTest, get_index_next_element) {
    std::vector<int> next_indexes = {4, 5, 6, 0, 1, 2, 3};
    for (int i = 0; i < next_indexes.size(); i++)
        ASSERT_EQ(
            fmIndex.get_index_next_element(i),
            next_indexes[i]
        );
}

TEST_F(FmIndexTest, get_subsequent_sequence) {
    ASSERT_EQ(
        fmIndex.get_subsequent_sequence(3).size(),
        0
    );

    Letters expected_subsequent_sequence;
    Letters actual_subsequent_sequence;

    expected_subsequent_sequence = {3, 1};
    actual_subsequent_sequence = fmIndex.get_subsequent_sequence(2);

    for (int i = 0; i < expected_subsequent_sequence.size(); i++)
        ASSERT_EQ(
            actual_subsequent_sequence[i],
            expected_subsequent_sequence[i]
        );


    expected_subsequent_sequence = {1};
    actual_subsequent_sequence = fmIndex.get_subsequent_sequence(6);

    for (int i = 0; i < expected_subsequent_sequence.size(); i++)
        ASSERT_EQ(
            actual_subsequent_sequence[i],
            expected_subsequent_sequence[i]
        );
}
