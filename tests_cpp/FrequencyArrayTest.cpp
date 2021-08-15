#include "gtest/gtest.h"
#include "FrequencyArray.hpp"

TEST(FrequencyArrayTest, compute_weight) {
    FrequencyArray frequencyArray = FrequencyArray(0);
        ASSERT_FLOAT_EQ(
            frequencyArray.compute_weight(5, 3, 1, 0),
            3.1
    );
}

TEST(FrequencyArrayTest, get_best_letter) {
    FrequencyArray frequencyArray = FrequencyArray(3);
    int letter = 1;
    frequencyArray.update(letter, 3, 3, 0, 0);
        ASSERT_FLOAT_EQ(
            frequencyArray.get_best_letter(),
            letter
    );
}

TEST(FrequencyArrayTest, get_k_best_letter) {
    FrequencyArray frequencyArray = FrequencyArray(3);
    frequencyArray.update(1, 3, 3, 2, 0); // lowest score
    frequencyArray.update(2, 3, 3, 0, 0); // highest score

    std::vector<int> expected = {2, 1};
    std::vector<int> actual = frequencyArray.get_k_best_letter(2);

    ASSERT_EQ(expected.size(), actual.size());

    for (int i = 0; i < expected.size(); i++)
        ASSERT_EQ(
            expected[i],
            actual[i]
        );
}
