#pragma once

#include <vector>

class FrequencyArray {
   public:
    explicit FrequencyArray(std::size_t alphabet_size);
    float update(std::size_t letter, int initial_query_length,
                 int subquery_length, int item_index,
                 int number_of_substitutions);

    const float compute_weight(int initial_query_length, int subquery_length,
                               int item_index, int number_of_substitutions);

    const int get_best_letter();

   private:
    std::vector<float> m_weights;
};
