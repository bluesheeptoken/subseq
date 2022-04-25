#pragma once

#include <cereal/archives/binary.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/vector.hpp>
#include <iostream>
#include <utility>
#include <vector>

#include "Bitset.hpp"
#include "types.hpp"

class WaveletTree {
   public:
    using iterator = std::vector<int>::iterator;
    WaveletTree();
    WaveletTree(Letters values, int alphabet_size);
    const int rank(int character, int l);
    const int operator[](int index);

    const int get_alphabet_size() const { return m_alphabet_size; }
    const std::size_t size() const { return m_bitsets[0].size(); };
    template <class Archive>
    void serialize(Archive& archive) {
        archive(m_children, m_bitsets, m_values, m_pivots, m_alphabet_size);
    }

   private:
    const int rank(int character, int l, int node_number);
    const int get(int index, int node_number);
    const bool is_leaf(int node_number);
    std::vector<std::pair<int, int>> m_children;
    std::vector<Bitset> m_bitsets;
    std::vector<int> m_values;
    std::vector<int> m_pivots;
    int m_alphabet_size;
    int build(iterator begin, iterator end, int node_number);
};
