#pragma once
#include <vector>

#include "FmIndex.hpp"
#include "Subquery.hpp"
#include "types.hpp"

class SubqueryGenerator {
   public:
    SubqueryGenerator(const Letters &query);
    Subquery next(FmIndex &fmIndex);

   private:
    Letters m_query;
    Letters m_mutable_query;
    std::size_t m_number_deletions;
    int m_substitution_index;
    std::vector<Letters> m_next_subqueries;
};