//
// Created by Liam Ross on 09/02/2022.
//

#include "Dictionary.h"

Dictionary::Dictionary() : currentWord{}, words{} {
    initializeWordsVec();
}

void Dictionary::initializeWordsVec() {
    std::ifstream dictionaryFile{"../dictionary.txt"};

    if (!dictionaryFile) {
        std::cerr << "Error reading file!" << std::endl;
        return;
    }

    std::string temp{};

    while(dictionaryFile >> temp) {
        words.push_back(temp);
    }
}

void Dictionary::setCurrentWord() {
    std::default_random_engine defaultRandomEngine(time(0));
    std::uniform_int_distribution<int> intDistribution(0, words.size()-1);
    currentWord = words.at(intDistribution(defaultRandomEngine));
}

std::string Dictionary::getCurrentWord() const {
    return currentWord;
}

