#include "FmIndex.hpp"

#include <algorithm>
#include <bitset>

Indexes shift_one(Indexes ints);
Indexes sort_cyclic_shifts(Letters const &text, std::size_t alphabet_size);
std::vector<int> counting_sort(Letters const &text, std::size_t alphabet_size);

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
    m_occurrences = counting_sort(text, alphabet_size);
    m_text_size = text.size();
}

const std::pair<int, int> FmIndex::backward_search(const Letters &query) {
    int start = 0;
    int end = m_tree.size();
    for (int letter : query) {
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

// Heavily inspired from https://cp-algorithms.com/string/suffix-array.html
Indexes sort_cyclic_shifts(Letters const &text, std::size_t alphabet_size) {
    // Initialization
    int n = text.size();
    Indexes permutations(n);
    std::vector<int> classes(n), cnt(std::max(alphabet_size, text.size()), 0);
    for (int i = 0; i < n; i++) cnt[text[i]]++;
    for (std::size_t i = 1; i < alphabet_size; i++) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++) permutations[--cnt[text[i]]] = i;
    classes[permutations[0]] = 0;
    int nb_classes = 1;
    for (int i = 1; i < n; i++) {
        if (text[permutations[i]] != text[permutations[i - 1]]) nb_classes++;
        classes[permutations[i]] = nb_classes - 1;
    }

    // steps
    Indexes permutations_n(n);
    std::vector<int> classes_n(n);
    for (int h = 1; h < n; h *= 2) {
        for (int i = 0; i < n; i++) {
            permutations_n[i] = permutations[i] - h;
            if (permutations_n[i] < 0) permutations_n[i] += n;
        }

        fill(cnt.begin(), cnt.end(), 0);

        for (int i = 0; i < n; i++) cnt[classes[permutations_n[i]]]++;
        for (int i = 1; i < nb_classes; i++) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; i--)
            permutations[--cnt[classes[permutations_n[i]]]] = permutations_n[i];
        classes_n[permutations[0]] = 0;
        nb_classes = 1;
        for (int i = 1; i < n; i++) {
            std::pair<int, int> cur = {classes[permutations[i]],
                                       classes[(permutations[i] + h) % n]};
            std::pair<int, int> prev = {
                classes[permutations[i - 1]],
                classes[(permutations[i - 1] + (1 << h)) % n]};
            if (cur != prev) ++nb_classes;
            classes_n[permutations[i]] = nb_classes - 1;
        }
        classes.swap(classes_n);
    }

    return permutations;
}

std::vector<int> counting_sort(Letters const &text, std::size_t alphabet_size) {
    std::vector<int> count(alphabet_size), occurrences(alphabet_size);
    for (auto letter : text) count[letter]++;
    for (std::size_t i = 1; i < alphabet_size; i++)
        occurrences[i] = count[i - 1] + occurrences[i - 1];
    return occurrences;
}
