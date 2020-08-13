#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

#include "CSubseq.hpp"

using namespace std;

int main() {
    ifstream file("/home/bluesheeptoken/Project/subseq/benchmark/FIFA_int.dat");
    string line;
    std::vector<std::vector<int>> data;
    while (getline(file, line)) {
        data.push_back({});
        istringstream stream(line);
        copy(istream_iterator<int>(stream), istream_iterator<int>(),
             back_inserter(data.back()));
    }

    std::vector<int> text = {};

    for (int i = 0; i < 20450; ++i) {
        text.insert(text.end(), data[i].begin(), data[i].end());
        text.push_back(0);
    }

    cout << "starting to feed" << endl;

    CSubseq model(text, *std::max_element(text.begin(), text.end()) + 1, 1);

    cout << "starting to predict" << endl;

    for (int i = 0; i < 1; ++i)
        model.predict(std::vector<int>(data[i].end() - 6, data[i].end() - 2));

    cout << "finished" << endl;

    return 0;
}
