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
    std::string pattern, input;
    std::getline(std::cin, pattern);
    std::for_each(pattern.begin(), pattern.end(), [](char &c) {
        c = std::tolower(c);
    });
    std::stringstream patternSS(pattern);
    int wordsInPattern = 0;
    while (patternSS >> input) {
        wordsInPattern++;
    }  
    std::string text, word;
    std::vector<std::vector<int>> information;

    int lineCnt = 1, wordCnt = 1, endOfWord = 0;
    while (std::getline(std::cin, input)) {
        if (lineCnt != 1) {
            text += " ";
        }
        std::stringstream inputSS(input);
        while (inputSS >> word) {
            endOfWord += word.size() - 1;
            information.push_back(std::vector<int>{lineCnt, wordCnt, endOfWord});
            std::for_each(word.begin(), word.end(), [](char &c) {
                c = std::tolower(c);
            });
            text += word + " ";
            endOfWord += 2;
            wordCnt++;
        }
        text.pop_back();
        lineCnt++;
        wordCnt = 1;
    }

    std::vector<int> nFunction(pattern.size()), lBigFunction, lLittleFunction;
    std::vector<std::vector<int>> rFunction(27);

    Preprocessing(nFunction, lBigFunction, lLittleFunction, rFunction, pattern);
    Search(text, pattern, information, lBigFunction, lLittleFunction, rFunction , wordsInPattern);

    std::cout << pattern << "\n" << text << "\n";
    
    return 0;
}