#include "gtest/gtest.h"
#include "CSubseq.hpp"

class CSubseqTest : public ::testing::Test {
 protected:
    Letters text = {2, 1, 3, 1, 3, 1, 0};  // banana$
    std::size_t alphabet_size = 4;
    CSubseq subseq = CSubseq(text, alphabet_size, 100);
};

TEST_F(CSubseqTest, predict) {
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
