#include "gtest/gtest.h"
#include "SubqueryGenerator.hpp"

class SubqueryGeneratorTest : public ::testing::Test {
 protected:
    Letters letters = {2, 1, 3, 1, 3, 1, 0};  // banana$
    std::size_t alphabet_size = 4;
    FmIndex fmIndex = FmIndex(letters, alphabet_size);
    Letters query = {1, 3, 2};
    SubqueryGenerator subquery_generator = SubqueryGenerator(query);
};

TEST_F(SubqueryGeneratorTest, generate_subqueries) {
    std::vector<Letters> expected_queries = {
        {1, 3, 2},
        {2, 3, 2},
        {3, 3, 2},
        {3, 2},
        {1, 2},
        {2, 2},
        {2}
    };

    std::vector<int> expected_number_substitutions = {
        0,
        1,
        1,
        1,
        2,
        2,
        2
    };

    std::vector<Subquery> actual;

    while (true) {
        auto query = subquery_generator.next(fmIndex);
        if (query.query.empty())
            break;
        actual.push_back(query);
    }

    for (int i = 0; i < actual.size(); i++) {
        for (int j = 0; j < actual[i].query.size(); j++)
            ASSERT_EQ(
                actual[i].query[j],
                expected_queries[i][j]
            );
        ASSERT_EQ(actual[i].number_substitutions, expected_number_substitutions[i]);
    }
}
