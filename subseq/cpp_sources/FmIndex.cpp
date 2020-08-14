#include "FmIndex.hpp"

#include <algorithm>
#include <bitset>
#include <iterator>

Indexes shift_one(Indexes ints);
Indexes sort_cyclic_shifts(Letters const &text, std::size_t alphabet_size);
std::vector<int> cumulative_sum_occurences(Letters const &text,
                                           std::size_t alphabet_size);

FmIndex::FmIndex() {}

FmIndex::FmIndex(Letters &text, std::size_t alphabet_size) {
    std::reverse(text.begin(), text.end());
    Indexes permutations = sort_cyclic_shifts(text, alphabet_size);
    Indexes shifted_permutations = shift_one(permutations);
    Letters permuted_text;
    std::transform(shifted_permutations.begin(), shifted_permutations.end(),
                   std::back_inserter(permuted_text),
                   [&text](int p) { return text[p]; });

    m_tree = WaveletTree(permuted_text, alphabet_size);
    m_occurrences = cumulative_sum_occurences(text, alphabet_size);
    m_text_size = text.size();
}

const std::pair<int, int> FmIndex::backward_search(const Letters &query) {
    int start = 0;
    int end = m_tree.size();
    for (int letter : query) {
        if (letter < 0) {
            start = 0;
            end = 0;
            break;
        }
        start = m_occurrences[letter] + m_tree.rank(letter, start);
        end = m_occurrences[letter] + m_tree.rank(letter, end);
        if (start == end) break;
    }
    return std::make_pair(start, end);
}

const std::unordered_set<int> FmIndex::next_candidates(const Letters &query) {
    std::unordered_set<int> candidates;
    if (query.empty()) {
        for (int i = 1; i < m_tree.get_alphabet_size(); i++)
            candidates.insert(i);
        return candidates;
    }
    std::pair<int, int> range = backward_search(query);
    for (int i = range.first; i < range.second; i++)
        candidates.insert(m_tree[i]);
    return candidates;
}

const Letters FmIndex::get_subsequent_sequence(int index) {
    Letters subsequent_sequence;

    int first_character = m_tree[index];
    if (first_character == 0)  // End of sequence
        return subsequent_sequence;
    subsequent_sequence.push_back(first_character);

    index = get_index_next_element(index);

    int second_character = m_tree[index];
    if (second_character == 0)  // End of sequence
        return subsequent_sequence;
    subsequent_sequence.push_back(second_character);
    return subsequent_sequence;
}

const int FmIndex::get_index_next_element(int index) {
    int c = m_tree[index];
    return m_occurrences[c] + m_tree.rank(c, index);
}

Indexes shift_one(Indexes ints) {
    for (std::size_t i = 0; i < ints.size(); i++)
        if (ints[i] == 0)
            ints[i] = ints.size() - 1;
        else
            ints[i]--;

    return ints;
}

Indexes counting_sort(std::vector<int> const &values,
                      Indexes const &permutation, std::size_t range) {
    int n = values.size();
    Indexes new_permutation(n);
    std::vector<int> cnt(range);

    for (int i = 0; i < n; i++) cnt[values[permutation[i]]]++;
    for (std::size_t i = 1; i < range; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--)
        new_permutation[--cnt[values[permutation[i]]]] = permutation[i];

    return new_permutation;
}

std::vector<int> generate_classes(std::vector<int> const &values,
                                  Indexes const &permutation, int text_size,
                                  int substring_length) {
    std::vector<int> classes(text_size);

    classes[permutation[0]] = 0;
    int nb_classes = 1;
    for (int i = 1; i < text_size; i++) {
        std::pair<int, int> cur = {
            values[permutation[i]],
            values[(permutation[i] + substring_length) % text_size]};
        std::pair<int, int> prev = {
            values[permutation[i - 1]],
            values[(permutation[i - 1] + substring_length) % text_size]};
        if (cur != prev) ++nb_classes;
        classes[permutation[i]] = nb_classes - 1;
    }
    return classes;
}

// Heavily inspired from https://cp-algorithms.com/string/suffix-array.html
Indexes sort_cyclic_shifts(Letters const &text, std::size_t alphabet_size) {
    // Initialization
    int n = text.size();
    Indexes permutation(n);

    for (int i = 0; i < n; i++) permutation[i] = i;

    permutation = counting_sort(text, permutation, alphabet_size);

    std::vector<int> classes = text;
    classes = generate_classes(classes, permutation, n, 0);

    // steps
    for (int h = 1; h < n; h *= 2) {
        int nb_classes = classes[permutation.back()] + 1;

        std::transform(permutation.begin(), permutation.end(),
                       permutation.begin(),
                       [n, h](int p) { return p < h ? p - h + n : p - h; });

        permutation = counting_sort(classes, permutation, nb_classes);

        classes = generate_classes(classes, permutation, n, h);
    }

    return permutation;
}

std::vector<int> cumulative_sum_occurences(Letters const &text,
                                           std::size_t alphabet_size) {
    std::vector<int> count(alphabet_size), occurrences(alphabet_size);
    for (auto letter : text) count[letter]++;
    for (std::size_t i = 1; i < alphabet_size; i++)
        occurrences[i] = count[i - 1] + occurrences[i - 1];
    return occurrences;
}
