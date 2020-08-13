#include "Bitset.hpp"

#include <algorithm>
#include <bitset>

Bitset::Bitset() {}

Bitset::Bitset(std::size_t size)
    : m_data(size / 32 + (size % 32 != 0)), m_size(size) {}

bool Bitset::operator[](std::size_t index) const {
    return m_data[index / 32] >> index % 32 & 1;
}

void Bitset::add(std::size_t index) { m_data[index / 32] |= 1 << index % 32; }

size_t Bitset::count_among_first_k_bits(std::size_t k) const {
    std::size_t count = 0;
    for (std::size_t i = 0; i < k / 32; i++)
        count += std::bitset<32>(m_data[i]).count();
    for (std::size_t i = k / 32 * 32; i < k; i++) count += operator[](i);
    return count;
}
