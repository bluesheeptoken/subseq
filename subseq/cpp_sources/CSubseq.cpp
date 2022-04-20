#include "CSubseq.hpp"

#include <algorithm>
#include <cereal/archives/binary.hpp>
#include <sstream>
#include <utility>

#include "SubqueryGenerator.hpp"

CSubseq::CSubseq(const std::vector<int>& text, const std::size_t alphabet_size,
                 const std::size_t threshold_query)
    : m_threshold_query(threshold_query), m_alphabet_size(alphabet_size) {
    Letters letters = Letters(text.begin(), text.end());
    m_fm_index = FmIndex(letters, alphabet_size);
}

CSubseq::CSubseq(const std::string& state) {
    std::istringstream stream(state);
    cereal::BinaryInputArchive archive(stream);
    archive(m_fm_index, m_threshold_query, m_alphabet_size);
}

const std::vector<Letters> CSubseq::generate_subqueries(const Letters& query) {
    Letters mutable_query(query);
    std::vector<Letters> subqueries;
    subqueries.push_back(mutable_query);

    for (int number_deletions = 0; number_deletions < 3; number_deletions++) {
        if (mutable_query.size() == 1 + (number_deletions == 0)) break;
        if (number_deletions != 0) {
            mutable_query.erase(mutable_query.begin());
            subqueries.push_back(mutable_query);
        }
        for (std::size_t index = 0; index < mutable_query.size() - 1; index++) {
            auto query_until_replacement =
                Letters(query.begin() + number_deletions,
                        query.begin() + number_deletions + index);
            auto candidates =
                m_fm_index.next_candidates(query_until_replacement);
            for (auto candidate : candidates) {
                if (candidate != query[index + number_deletions]) {
                    mutable_query[index] = candidate;
                    subqueries.push_back(mutable_query);
                    mutable_query[index] = query[index];
                }
            }
        }
    }
    return subqueries;
}

const int CSubseq::predict_subquery(const Letters& query,
                                    const std::size_t initial_query_size,
                                    const std::size_t number_of_substitutions,
                                    Bitset& bitset,
                                    FrequencyArray& frequencyArray) {
    int counter_queries = 0;
    std::pair<int, int> range = m_fm_index.backward_search(query);
    Letters subsequent_sequence;
    for (int i = range.first; i < range.second; ++i) {
        if (!bitset[i]) {
            bitset.add(i);
            counter_queries += 1;
            subsequent_sequence = m_fm_index.get_subsequent_sequence(i);
            for (std::size_t j = 0; j < subsequent_sequence.size(); ++j)
                frequencyArray.update(subsequent_sequence[j],
                                      initial_query_size, query.size(), j,
                                      number_of_substitutions);
        }
    }
    return counter_queries;
}

const int CSubseq::predict(const std::vector<int>& query) {
    FrequencyArray frequency_array = compute_frequency_array(query);
    return frequency_array.get_best_letter();
}

const std::vector<int> CSubseq::predict_k(const std::vector<int>& query,
                                          std::size_t k) {
    FrequencyArray frequency_array = compute_frequency_array(query);
    return frequency_array.get_k_best_letter(k);
}

const FrequencyArray CSubseq::compute_frequency_array(
    const std::vector<int>& query) {
    FrequencyArray frequency_array(m_alphabet_size);
    Bitset bitset(m_fm_index.get_text_size());
    int query_used_counter = 0;
    SubqueryGenerator generator =
        SubqueryGenerator(Letters(query.begin(), query.end()));
    while (true) {
        Subquery subquery = generator.next(m_fm_index);
        if (subquery.query.empty()) break;
        query_used_counter += predict_subquery(subquery.query, query.size(),
                                               subquery.number_substitutions,
                                               bitset, frequency_array);
        if (m_threshold_query > 0 && query_used_counter >= m_threshold_query)
            break;
    }
    return frequency_array;
}

const std::string CSubseq::get_state() const {
    std::stringstream stream;
    {
        cereal::BinaryOutputArchive archive(stream);
        archive(m_fm_index, m_threshold_query, m_alphabet_size);
    }
    return stream.str();
};
