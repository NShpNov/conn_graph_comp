#include "basics.hpp"

std::vector<int> RAM_algorithm(DSU<int> dsu, std::vector<std::pair<int, int>> E) {
    for (int i = 0; i < E.size(); i++) {
        dsu.merge(E[i].first, E[i].second);
    }
    return dsu.calculate_component_numbers();
}

std::vector<std::pair<int, int>> pseudo_random_edges(const int n, const int am) {
    int amount = 0;
    if (am > (n * (n - 1)) / 2)
        amount = (n * (n - 1)) / 2;
    else
        amount = am;
    std::vector<std::pair<int, int>> array;
    for (int i = 0; i < amount; i++) {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_real_distribution<double> dist(0, n);
        int tmp1 = (int)(dist(mt));
        int tmp2 = (int)(dist(mt));

        std::pair<int, int> tmp(tmp1, tmp2);

        bool flag = false;
        for (int j = 0; j < array.size(); j++)
            if ((array[j] == tmp) || ((array[j].first == tmp.second) && (array[j].second == tmp.first))||(tmp.first == tmp.second))
                flag = true;
        if (!flag)
            array.push_back(tmp);
    }
    return array;
}