#include "gtest/gtest.h"
#include "Bitset.hpp"

class BitsetTest : public ::testing::Test {
 protected:
    std::vector<std::uint8_t> data = {7, 8, 9};
    std::size_t size = 10;
    Bitset bitset = Bitset(size);
    void SetUp() override {
        for (auto i : data)
            bitset.add(i);
    }
};

TEST_F(BitsetTest, at) {
    for (int i = 0; i < size; i++)
        ASSERT_EQ(
            bitset[i],
            std::find(data.begin(), data.end(), i) != data.end()
        );
}

TEST_F(BitsetTest, count_among_first_k_bits) {
    ASSERT_EQ(bitset.count_among_first_k_bits(9), 2);
}
