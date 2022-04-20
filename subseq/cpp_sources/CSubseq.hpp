#pragma once

#include <cstdint>
#include <string>
#include <tuple>
#include <vector>

#include "Bitset.hpp"
#include "FmIndex.hpp"
#include "FrequencyArray.hpp"
#include "types.hpp"

class CSubseq {
   public:
    CSubseq(const std::vector<int>& text, const std::size_t alphabet_size,
            const std::size_t threshold_query);
    CSubseq() = default;
    CSubseq(const std::string& state);

    const std::vector<Letters> generate_subqueries(const Letters& query);
    const int predict_subquery(
        const Letters& query, const std::size_t initial_query_size,
        const std::size_t number_of_substitutions, Bitset& bitset,
        FrequencyArray& frequencyArray);  // return number of updates

    const int predict(const std::vector<int>& query);
    const std::vector<int> predict_k(const std::vector<int>& query,
                                     std::size_t k);

    const std::string get_state() const;

   private:
    const FrequencyArray compute_frequency_array(const std::vector<int>& query);

    FmIndex m_fm_index;
    int m_threshold_query;
    std::size_t m_alphabet_size;
};
