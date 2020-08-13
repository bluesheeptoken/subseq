#pragma once

#include <vector>

enum class type { Letter, Index };

template <type T>
class vector : public std::vector<int> {
   public:
    using std::vector<int>::vector;
};

using Letters = vector<type::Letter>;
using Indexes = vector<type::Index>;
