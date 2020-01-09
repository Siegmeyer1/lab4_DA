#ifndef SEARCH_HPP
#define SEARCH_HPP 1

#include <string>
#include <vector>
#include <iostream>

void Search(const std::string &str, const std::string &pattern, const std::vector<std::vector<int>> &information,
            std::vector<int> &n, std::vector<int> &bigL, std::vector<int> &littleL, std::vector<std::vector<int>> &r, int wordsInPattern) {
    int k = pattern.size() - 1;
    std::vector<int> entry;
    std::vector<int> m(str.size());
    while (k < str.size()) {
        int i = pattern.size() - 1;
        int h = k;
        while (true) {
            if (m[h] == 0) {
                if (str[h] == pattern[i]) {
                    if (i == 0) {
                        entry.push_back(k); // сообщить о вхождении
                        m[k] = pattern.size(); // подстрока [k - pattern.size() + 1 .. k] совпадает с образцом
                        // такой сдвиг, что префикс образца должен совпасть с суффиксом
                        if (pattern.size() > 2) {
                            k += pattern.size() - littleL[1];
                        } else {
                            k++;
                        }
                        break; //конец фазы
                    } else { // если  i > 0
                        h--;
                        i--;
                    }
                } else { // несовпадение
                    m[k] = k - h;
                    // нахождение хорошего суффикса
                    int maxSuff;
                    if (i == pattern.size() - 1) { // если не совпал первый символ
                        maxSuff = 1;
                    } else {
                        if (bigL[i + 1] > 0) {
                            maxSuff = pattern.size() - bigL[i + 1] - 1;
                        } else {
                            maxSuff = pattern.size() - littleL[i + 1];
                        }
                    }
                    // нахождение плохого символа
                    int maxSymb = 1;
                    bool badSymbFound = false;
                    if (str[h] == ' ') { // если несовпадение в символе ' '
                        for (int j = 0; j < r[r.size() - 1].size(); j++) {
                            if (r[r.size() - 1][j] < i) {
                                maxSymb = std::max(1, i - r[r.size() - 1][j]);
                                badSymbFound = true;
                                break;
                            }
                        }
                    }
                    if (str[h] >= 97 && str[h] <= 122) { // если несовпадение в букве
                        for (int j = 0; j < r[str[h] - 97].size(); j++) {
                            if (r[str[h] - 97][j] < i) {
                                maxSymb = std::max(1, i - r[str[h] - 97][j]);
                                badSymbFound = true;
                                break;
                            }
                        }
                    }
                    if (!badSymbFound) { // если символа строки нет до позиции i, то сдвигаем за этот символ
                        maxSymb = i + 1;
                    }

                    k += std::max(maxSuff, maxSymb);
                    break; // конец фазы
                }
            } else if (m[h] < n[i]) {
                i -= m[h];
            } else if (m[h] >= n[i] && n[i] >= i) {
                entry.push_back(k); // сообщить о вхождении
                m[k] = k - h; 
                // такой сдвиг, что префикс образца должен совпасть с суффиксом
                if (pattern.size() > 2) {
                    k += pattern.size() - littleL[1];
                } else {
                    k++;
                }
                break; // конец фазы
            } else if (m[h] > n[i] && n[i] < i) {
                m[k] = k - h;
                // несовпадение в i - n[i]
                // нахождение хорошего суффикса
                int maxSuff;
                if (i - n[i] == pattern.size() - 1) { // если не совпал первый символ
                    maxSuff = 1;
                } else {
                    if (bigL[i - n[i] + 1] > 0) {
                        maxSuff = pattern.size() - bigL[i - n[i] + 1] - 1;
                    } else {
                        maxSuff = pattern.size() - littleL[i - n[i] + 1];
                    }
                }
                // нахождение плохого символа
                int maxSymb = 1;
                bool badSymbFound = false;
                if (str[h - n[i]] == ' ') { // если несовпадение в символе ' '
                    for (int j = 0; j < r[r.size() - 1].size(); j++) {
                        if (r[r.size() - 1][j] < i - n[i]) {
                            maxSymb = std::max(1, i - n[i] - r[r.size() - 1][j]);
                            badSymbFound = true;
                            break;
                        }
                    }
                }
                if (str[h - n[i]] >= 97 && str[h - n[i]] <= 122) { // если несовпадение в букве
                    for (int j = 0; j < r[str[h - n[i]] - 97].size(); j++) {
                        if (r[str[h - n[i]] - 97][j] < i - n[i]) {
                            maxSymb = std::max(1, i - n[i] - r[str[h - n[i]] - 97][j]);
                            badSymbFound = true;
                            break;
                        }
                    }
                }
                if (!badSymbFound) { // если символа строки нет до позиции i, то сдвигаем за этот символ
                    maxSymb = i - n[i] + 1;
                }

                k += std::max(maxSuff, maxSymb);
                break; // конец фазы
            } else if (m[h] == n[i] && n[i] < i) {
                i -= m[h];
                h -= m[h];
            }
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