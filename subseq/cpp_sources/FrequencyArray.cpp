#include "FrequencyArray.hpp"

#include <algorithm>

namespace {
struct CountingIterator {
    typedef int value_type;
    typedef int difference_type;
    typedef const int& reference;
    typedef const int* pointer;
    typedef std::input_iterator_tag iterator_category;

    CountingIterator() = default;
    explicit CountingIterator(int value) : value(value) {}

    reference operator*() const { return value; }

    CountingIterator& operator++() {
        ++value;
        return *this;
    }
    CountingIterator operator++(int) { return CountingIterator(value++); }

    bool operator==(const CountingIterator& rhs) const {
        return value == rhs.value;
    }
    bool operator!=(const CountingIterator& rhs) const {
        return value != rhs.value;
    }

   private:
    int value;
};
}  // namespace

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

const std::vector<int> FrequencyArray::get_k_best_letter(std::size_t k) {
    std::vector<int> best_predictions(std::min(k, m_weights.size()));

    std::partial_sort_copy(
        CountingIterator(0), CountingIterator(m_weights.size()),
        best_predictions.begin(), best_predictions.end(),
        [this](int x, int y) { return m_weights[x] > m_weights[y]; });

    return best_predictions;
}
