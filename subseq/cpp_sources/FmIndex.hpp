#pragma once

#include <cstdint>
#include <unordered_set>
#include <utility>
#include <vector>

#include "WaveletTree.hpp"
#include "types.hpp"

class FmIndex {
   public:
    struct State {
        Letters permuted_text;
        std::size_t alphabet_size;
    };
    FmIndex();
    FmIndex(Letters& text, std::size_t alphabet_size);
    const std::pair<int, int> backward_search(const Letters& query);
    const std::unordered_set<int> next_candidates(const Letters& query);
    const Letters get_subsequent_sequence(
        int index);  // Should get 0 to 2 elements
    const int get_index_next_element(int index);
    Letters get_permuted_text();
    static FmIndex create_from_state(const State& state);
    State get_state();

    const std::size_t get_text_size() const { return m_text_size; }
    const WaveletTree& get_tree() { return m_tree; }
    const std::vector<int>& get_occurrences() const { return m_occurrences; }

   private:
    struct permuted_constructor {};
    FmIndex(const Letters& permuted_text, std::size_t alphabet_size,
            permuted_constructor);
    std::size_t m_text_size;
    WaveletTree m_tree;
    std::vector<int> m_occurrences;
};
