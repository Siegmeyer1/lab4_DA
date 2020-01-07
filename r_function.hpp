#ifndef R_FUNCTION_H
#define R_FUNCTION_H 1

#include <string>
#include <vector>

template<typename T>
void RFunction(const std::string &s, std::vector<std::vector<T>> &v) {
    for (int i = s.size() - 1; i >= 0; i--) {
        if (s[i] == ' ') {
            v[v.size() - 1].push_back(i);
        }
        v[s[i] - 97].push_back(i);
    } 
}

#endif // R_FUNCTION_H