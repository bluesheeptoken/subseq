#include "FrequencyArray.hpp"

#include <algorithm>

FrequencyArray::FrequencyArray(std::size_t alphabet_size)
    : m_weights(alphabet_size) {}

float FrequencyArray::update(std::size_t letter, int initial_query_length,
                             int subquery_length, int item_index,
                             int number_of_substitutions) {
    m_weights[letter] += compute_weight(initial_query_length, subquery_length,
                                        item_index, number_of_substitutions);
    return m_weights[letter];
}

const float FrequencyArray::compute_weight(int initial_query_length,
                                           int subquery_length, int item_index,
                                           int number_of_substitutions) {
    float r = 1 / ((float)item_index + 1);
    float result = (float)subquery_length / (float)initial_query_length;
    result += (2 - (float)number_of_substitutions) / 2;
    result += 1 + r;
    return result;
}

const int FrequencyArray::get_best_letter() {
    return std::distance(m_weights.begin(),
                         std::max_element(m_weights.begin(), m_weights.end()));
}
