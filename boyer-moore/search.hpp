#ifndef SEARCH_HPP
#define SEARCH_HPP 1

#include <string>
#include <vector>
#include <iostream>

void Search(const std::string &str, const std::string &pattern, const std::vector<std::vector<int>> &information, 
            std::vector<int> &bigL, std::vector<int> &littleL, std::vector<std::vector<int>> &r, int wordsInPattern) {
    int k = pattern.size() - 1;
    std::vector<int> entry;
    while (k < str.size()) {
        int i = pattern.size() - 1;
        int h = k;
        while ((i >= 0) && (pattern[i] == str[h])) {
            i--;
            h--;
        } 
        if (i == -1) {
            entry.push_back(k);
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
                    maxSuff = pattern.size() - littleL[i + 1];
                }
            }
            int maxSymb = 1;
            if (str[h] == ' ') {
                for (int j = 0; j < r[r.size() - 1].size(); j++) {
                    if (r[r.size() - 1][j] < i) {
                        maxSymb = std::max(1, i - r[r.size() - 1][j]);
                        break;
                    }
                }
            }
            if (str[h] >= 97 && str[h] <= 122) {
                int j;
                for (j = 0; j < r[str[h] - 97].size(); j++) {
                    if (r[str[h] - 97][j] < i) {
                        maxSymb = std::max(1, i - r[str[h] - 97][j]);
                        break;
                    }
                }
                if (j - 1 == r[str[h] - 97].size()) {
                    maxSymb = k + i + 1;
                }
            }
            k += std::max(maxSuff, maxSymb);
        }
    }
    for (int infCnt = 0, entryCnt = 0; entryCnt < entry.size(); infCnt++) {
        if (information[infCnt][3] <= entry[entryCnt] && information[infCnt][2] >= entry[entryCnt]) {
            std::cout << information[infCnt - wordsInPattern + 1][0] << ", " << information[infCnt - wordsInPattern + 1][1] << "\n";
            entryCnt++;
            infCnt--;
        }
    }
}

#endif // SEARCH_HPP