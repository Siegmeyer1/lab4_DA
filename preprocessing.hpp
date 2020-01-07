#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP 1

#include <vector>
#include "z_function.hpp"
#include "r_function.hpp"
#include "n_function.hpp"
#include "l_little_function.hpp"
#include "l_big_function.hpp"

void Preprocessing(std::vector<int> &n, std::vector<int> &bigL, std::vector<int> &littleL,
                    std::vector<std::vector<int>> &r, const std::string &pattern) {
    NFunction(pattern, n);
    bigL = LBigFunction(pattern, n);
    littleL = LLittleFunction(pattern, n);
    RFunction(pattern, r);
}

#endif // PREPROCESSING_HPP