#ifndef SEARCH_HPP
#define SEARCH_HPP 1

#include <string>
#include <utility>
#include <vector>
#include <iostream>

void Search(const std::string &str, const std::string &pattern, const std::vector<std::vector<int>> & information, 
            std::vector<int> &bigL, std::vector<int> &littleL, std::vector<std::vector<int>> &r, int wordsInPattern) {
    int k = pattern.size() - 1;
    //std::vector<std::pair<int, int>> entry;
    while (k < str.size()) {
        int i = pattern.size() - 1;
        int h = k;
        while ((i >= 0) && (pattern[i] == str[h])) {
            i--;
            h--;
        } 
        if (i == -1) {
            int counter = 0;
            while (information[counter][2] != k) {
                counter++;
            }
            std::cout << information[counter - wordsInPattern + 1][0] << ", " << information[counter - wordsInPattern + 1][1] << "\n";
            if (pattern.size() > 2) {
                k += pattern.size() - littleL[1];
            } else {
                k++;
            }
        } else {
            int maxSuff;
            if (i == pattern.size() - 1) {
                maxSuff = 1;
            } else {
                if (bigL[i + 1] > 0) {
                    maxSuff = pattern.size() - bigL[i + 1] - 1;
                } else {
                    maxSuff = pattern.size() - littleL[i + 1] - 1;
                }
            }
            int maxSymb = pattern.size();
            if (str[h] == ' ') {
                for (int j = 0; j < r[r.size() - 1].size(); j++) {
                    if (r[r.size() - 1][j] < i) {
                        maxSymb = std::max(1, i - r[r.size() - 1][j]);
                        break;
                    }
                }
            }
            if (str[h] >= 97 && str[h] <= 122) {
                for (int j = 0; j < r[str[h] - 97].size(); j++) {
                    if (r[str[h] - 97][j] < i) {
                        maxSymb = std::max(1, i - r[str[h] - 97][j]);
                        break;
                    }
                }
            }
            k += std::max(maxSuff, maxSymb);
        }
    }
}

#endif // SEARCH_HPP