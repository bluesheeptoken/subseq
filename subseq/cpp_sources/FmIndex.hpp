#pragma once

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cstdint>
#include <unordered_set>
#include <utility>
#include <vector>

#include "WaveletTree.hpp"
#include "types.hpp"

class FmIndex {
   public:
    FmIndex();
    FmIndex(Letters& text, std::size_t alphabet_size);
    const std::pair<int, int> backward_search(const Letters& query);
    const std::unordered_set<int> next_candidates(const Letters& query);
    const Letters get_subsequent_sequence(
        int index);  // Should get 0 to 2 elements
    const int get_index_next_element(int index);

    const std::size_t get_text_size() const { return m_text_size; }
    const WaveletTree& get_tree() { return m_tree; }
    const std::vector<int>& get_occurrences() const { return m_occurrences; }
    template <class Archive>
    void serialize(Archive& archive) {
        archive(m_text_size, m_tree, m_occurrences);
    }

   private:
    std::size_t m_text_size;
    WaveletTree m_tree;
    std::vector<int> m_occurrences;
};
