#include "SubqueryGenerator.hpp"

SubqueryGenerator::SubqueryGenerator(const Letters &query)
    : m_query(query.begin(), query.end()),
      m_mutable_query(query.begin(), query.end()),
      m_number_deletions(0),
      m_substitution_index(-1) {}

Subquery SubqueryGenerator::next(FmIndex &fm_index) {
    Subquery subquery;
    if ((m_number_deletions == 2 &&
         m_substitution_index == m_mutable_query.size() - 1) ||
        m_mutable_query.empty()) {
        subquery.query = {};
        return subquery;
    }

    if (!m_next_subqueries.empty()) {
        subquery.query = m_next_subqueries.back();
        m_next_subqueries.pop_back();
    } else {
        if (m_substitution_index == -1) {
            m_substitution_index++;
            subquery.query = m_query;
        } else if (m_substitution_index == m_mutable_query.size() - 1) {
            m_number_deletions++;
            m_substitution_index = 0;
            m_mutable_query.erase(m_mutable_query.begin());
            subquery.query = m_mutable_query;
        } else {
            auto query_until_replacement =
                Letters(m_mutable_query.begin(),
                        m_mutable_query.begin() + m_substitution_index);
            auto candidates = fm_index.next_candidates(query_until_replacement);
            for (auto candidate : candidates) {
                if (candidate != m_mutable_query[m_substitution_index] &&
                    candidate != 0) {
                    int old_letter = m_mutable_query[m_substitution_index];
                    m_mutable_query[m_substitution_index] = candidate;
                    m_next_subqueries.push_back(m_mutable_query);
                    m_mutable_query[m_substitution_index] = old_letter;
                }
            }
            m_substitution_index++;
            if (m_next_subqueries.empty()) return next(fm_index);
            subquery.query = m_next_subqueries.back();
            m_next_subqueries.pop_back();
        }
    }

    subquery.number_substitutions =
        m_number_deletions + (m_substitution_index > 0);
    return subquery;
}
