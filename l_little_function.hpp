#ifndef L_LITTLE_FUNCTION_HPP
#define L_LITTLE_FUNCTION_HPP 1

#include <vector>
#include <string>
#include "n_function.hpp"

template<typename T>
std::vector<T> LLittleFunction(const std::string &s, std::vector<T> &v) {
    std::vector<T> l(s.size());
    for (int i = s.size() - 1; i >= 0; i--) {
        int j = (s.size() - 1) - i;
        if (v[j] == j + 1) {
            l[i] = j + 1;
        } else {
            if (i == s.size() - 1) {
                l[i] = 0;
            }
            l[i] = l[i + 1];
        }
    }
    
    return l;
}

#endif // L_LITTLE_FUNCTION_HPP