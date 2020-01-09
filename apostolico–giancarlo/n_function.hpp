#ifndef N_FUNCTION_H
#define N_FUNCTION_H 1

#include <vector>
#include <string>
#include <algorithm>

template<typename T>
void NFunction(const std::string &s, std::vector<T> &v) {
    if (s.size() == 0) {
        return;
    }
    int size = s.size(), l = size - 1, r = size - 1, k = size - 2;

    while (k >= 0) {
        if (k < r) {
            for (int i = size - 1, j = k; j != -1; i--, j--) {
                if (s[i] == s[j]) {
                    v[k]++;
                } else {
                    break;
                }
            }
            if (v[k] > 0) {
                r = k - v[k] + 1;
                l = k;
            }
            k--;
        } else {
            if (v[size - 1 - l + k] < k - r + 1) {
                v[k] = v[size - 1 - l + k];
            } else {
                v[k] = k - r + 1;
                for (int i = size - k + r - 2, j = r - 1; j != -1; i--, j--) {
                    if (s[i] == s[j]) {
                        v[k]++;
                    } else {
                        break;
                    }
                }
                if (k - v[k] + 1 <= r - 1) {
                    r = k - v[k] + 1;
                    l = k;
                }
            }
            k--;
        }
    }
}

#endif // N_FUNCTION_H