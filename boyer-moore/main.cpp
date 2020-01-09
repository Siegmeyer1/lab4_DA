#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <sstream>
#include <cctype>
#include "preprocessing.hpp"
#include "search.hpp"

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string pattern, input, word;
    std::getline(std::cin, input);
    if (input.back() == '\n') {
        input.pop_back();
    }
    std::for_each(input.begin(), input.end(), [](char &c) {
        c = std::tolower(c);
    });
    std::stringstream patternSS(input);
    int wordsInPattern = 0;
    while (patternSS >> word) {
        pattern += word + " ";
        wordsInPattern++;
    }
    if (!pattern.empty()) {
        pattern.pop_back();    
    }
    
    std::string text;
    std::vector<std::vector<int>> information;

    int lineCnt = 1, wordCnt = 1, endOfWord = 0, startOfWord = 0;
    while (std::getline(std::cin, input)) {
        bool first = true;
        for (int i = 0; i < input.size(); i++) {
            if (input[i] == ' ') {
                if (first) {
                    continue;
                } else {
                    information.push_back(std::move(std::vector<int>{lineCnt, wordCnt, endOfWord - 1, startOfWord}));
                    text += " ";
                    endOfWord++;
                    startOfWord = endOfWord;
                    first = true;
                    wordCnt++;
                }
            } else {
                first = false;
                endOfWord++;
                text += std::tolower(input[i]);
                if (i == input.size() - 1) {
                    information.push_back(std::move(std::vector<int>{lineCnt, wordCnt, endOfWord - 1, startOfWord}));
                    text += " ";
                    endOfWord++;
                    startOfWord = endOfWord;
                }
            }
        }
        lineCnt++;
        wordCnt = 1;
    }

    if (!text.empty()) {
        text.pop_back();
    }

    std::vector<int> nFunction(pattern.size()), lBigFunction, lLittleFunction;
    std::vector<std::vector<int>> rFunction(27);

    Preprocessing(nFunction, lBigFunction, lLittleFunction, rFunction, pattern);
    Search(text, pattern, information, lBigFunction, lLittleFunction, rFunction , wordsInPattern);

    return 0;
}