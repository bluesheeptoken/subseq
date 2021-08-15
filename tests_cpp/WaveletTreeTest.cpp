#include "gtest/gtest.h"
#include "WaveletTree.hpp"

class WaveletTreeTest : public ::testing::Test {
 protected:
    Letters letters = {2, 1, 3, 1, 3, 1, 0};
    WaveletTree wavelet_tree = WaveletTree(letters, 4);
};

TEST_F(WaveletTreeTest, at) {
    for (int i = 0; i < letters.size(); i++)
      ASSERT_EQ(wavelet_tree[i], letters[i]);
}

TEST_F(WaveletTreeTest, rank) {
    ASSERT_EQ(wavelet_tree.rank(2, 3), 1);
    ASSERT_EQ(wavelet_tree.rank(1, 6), 3);
}
