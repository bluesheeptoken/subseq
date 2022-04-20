#include "gtest/gtest.h"
#include "CSubseq.hpp"
#include <cereal/archives/binary.hpp>
#include <sstream>
#include <iostream>

TEST(CSubseqTest, predict) {
    Letters text = {2, 1, 3, 1, 3, 1, 0};  // banana$
    std::size_t alphabet_size = 4;
    CSubseq subseq = CSubseq(text, alphabet_size, 100);

    Letters query;
    int expected_prediction;
    int actual_prediction;

    query = {1};
    expected_prediction = 3;
    actual_prediction = subseq.predict(query);
    ASSERT_EQ(
        actual_prediction,
        expected_prediction
    );

    query = {2, 1};
    expected_prediction = 3;
    actual_prediction = subseq.predict(query);
    ASSERT_EQ(
        actual_prediction,
        expected_prediction
    );

    query = {3, 1, 3};
    expected_prediction = 1;
    actual_prediction = subseq.predict(query);
    ASSERT_EQ(
        actual_prediction,
        expected_prediction
    );
}

TEST(CSubseqTest, predict_k) {
    Letters text = {1, 2, 0, 1, 3, 0, 1, 3, 0};
    std::size_t alphabet_size = 4;
    CSubseq subseq = CSubseq(text, alphabet_size, 100);

    Letters query = {1};
    std::vector<int> expected = {3, 2};
    std::vector<int> actual = subseq.predict_k(query, 2);

    ASSERT_EQ(expected.size(), actual.size());

    for (int i = 0; i < expected.size(); i++)
        ASSERT_EQ(
            expected[i],
            actual[i]
        );
}

TEST(CSubseqTest, serialize) {
    Letters text = {1, 2, 0, 1, 3, 0, 1, 3, 0};
    std::size_t alphabet_size = 4;
    CSubseq subseq(text, alphabet_size, 100);
    CSubseq restored_subseq(subseq.get_state());

    Letters query = {1};
    std::vector<int> expected = {3, 2};
    std::vector<int> actual = restored_subseq.predict_k(query, 2);

    ASSERT_EQ(expected.size(), actual.size());

    for (int i = 0; i < expected.size(); i++)
        ASSERT_EQ(
            expected[i],
            actual[i]
        );

}
