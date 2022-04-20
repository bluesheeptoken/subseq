#pragma once

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>
#include <cstdint>
#include <tuple>
#include <vector>

class Bitset {
   public:
    Bitset();
    explicit Bitset(std::size_t size);

    bool operator[](std::size_t index) const;
    void add(std::size_t index);

    size_t count_among_first_k_bits(std::size_t k) const;

    const std::vector<std::uint32_t>& get_data() const { return m_data; }
    const std::size_t size() const { return m_size; }
    template <class Archive>
    void serialize(Archive& archive) {
        archive(m_data, m_size);
    }

   private:
    std::vector<std::uint32_t> m_data;
    std::size_t m_size;
};
