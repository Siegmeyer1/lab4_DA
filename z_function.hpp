#ifndef Z_FUNCTION_HPP
#define Z_FUNCTION_HPP 1

#include <vector>
#include <string>
#include <algorithm>

template<typename T>
void ZFunction(const std::string &s, std::vector<T> &v) {
    int l = 0, r = 0, k = 1, size = s.size();

    while (k < size) {
        if (k > r) {
            for (int i = 0, j = k; j != size; i++, j++) {
                if (s[i] == s[j]) {
                    v[k]++;
                } else {
                    break;
                }
            }
            if (v[k] > 0) {
                r = k + v[k] - 1;
                l = k;
            }
            k++;
        } else {
            if (v[k - l] < r - k + 1) {
                v[k] = v[k - l];
            } else {
                v[k] = r - k + 1;
                for (int i = r - k + 1, j = r + 1; j != size; i++, j++) {
                    if (s[i] == s[j]) {
                        v[k]++;
                    } else {
                        break;
                    }
                }
                if (v[k] + k - 1 >= r + 1) {
                    r = k + v[k] - 1;
                    l = k;
                }
            }
            k++;
        }
    }
}

#endif // Z_FUNCTION_HPP