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

