#ifndef L_BIG_FUNCTION_HPP
#define L_BIG_FUNCTION_HPP 1

#include <vector>
#include <string>
#include "n_function.hpp"

template<typename T>
std::vector<T> LBigFunction(const std::string &s, std::vector<T> &v) {
    std::vector<T> l(s.size());
    for (int j = 0; j < s.size() - 1; j++) {
        if (v[j] == 0) {
            continue;
        } 
        int i = s.size() - v[j];
        l[i] = j;
    }

    return l;
}

#endif // L_BIG_FUNCTION_HPP