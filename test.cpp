#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>

int main() {
    std::string pattern;
    std::getline(std::cin, pattern);
    
    std::string input;
    std::string text;
    std::string word;

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
            text += word + " ";
            endOfWord += 2;
            wordCnt++;
        }
        text.pop_back();
        lineCnt++;
        wordCnt = 1;
    }

    std::cout << "pattern:\n" << pattern << "\n";
    std::cout << "text: \n" << text << "\n";

    for (auto vector : information) {
        std::cout << "lineCnt: " << vector[0] << ", wordCnt: " << vector[1] << ", endOfWord: " << vector[2] << ".\n";
    }

    return 0;
}