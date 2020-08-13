#include "WaveletTree.hpp"

#include <algorithm>
#include <utility>

WaveletTree::WaveletTree() {}

WaveletTree::WaveletTree(Letters values, int alphabet_size) {
    int node_numbers = alphabet_size * 2 - 1;
    m_children.resize(node_numbers);
    m_bitsets.resize(node_numbers);
    m_values.resize(node_numbers);
    fill(m_values.begin(), m_values.end(), -1);
    m_pivots.resize(node_numbers);
    m_alphabet_size = alphabet_size;

    if (!values.empty()) build(values.begin(), values.end(), 0);
}

int WaveletTree::build(iterator begin, iterator end, int node_number) {
    iterator min, max;
    std::tie(min, max) = std::minmax_element(begin, end);

    if (*min == *max) {
        m_values[node_number] = *max;
        return node_number + 1;
    } else {
        int pivot = (*min + *max) / 2;
        auto predicate = [pivot](int n) { return n <= pivot; };

        Bitset bitset = Bitset(std::distance(begin, end));
        for (iterator i = begin; i < end; ++i)
            if (!predicate(*i)) bitset.add(std::distance(begin, i));
        m_bitsets[node_number] = bitset;

        iterator it = std::stable_partition(begin, end, predicate);
        int left_node = node_number + 1;
        int right_node = build(begin, it, left_node);
        int next_node = build(it, end, right_node);

        m_children[node_number] = std::make_pair(left_node, right_node);
        m_pivots[node_number] = pivot;
        return next_node;
    }
}

const int WaveletTree::rank(int character, int l) {
    return rank(character, l, 0);
}

const int WaveletTree::rank(int character, int l, int node_number) {
    if (is_leaf(node_number)) {
        if (m_values[node_number] == character) return l;
        return -1;
    }
    int new_l = m_bitsets[node_number].count_among_first_k_bits(l);
    if (character <= m_pivots[node_number])
        return rank(character, l - new_l, m_children[node_number].first);
    return rank(character, new_l, m_children[node_number].second);
}

const int WaveletTree::operator[](int index) { return get(index, 0); }

const int WaveletTree::get(int index, int node_number) {
    if (is_leaf(node_number)) return m_values[node_number];

    Bitset bitset = m_bitsets[node_number];

    int nb_positive_bits = bitset.count_among_first_k_bits(index);

    if (bitset[index])
        return get(nb_positive_bits, m_children[node_number].second);
    return get(index - nb_positive_bits, m_children[node_number].first);
}

const bool WaveletTree::is_leaf(int node_number) {
    return m_values[node_number] != -1;
}
