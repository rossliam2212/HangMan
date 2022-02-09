//
// Created by Liam Ross on 09/02/2022.
//

#ifndef HANGMAN_DICTIONARY_H
#define HANGMAN_DICTIONARY_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <ctime>

class Dictionary {
private:
    std::string currentWord;
    std::vector<std::string> words;

public:
    Dictionary();
    ~Dictionary() = default;
    void initializeWordsVec();
    void setCurrentWord();
    std::string getCurrentWord() const;
};


#endif //HANGMAN_DICTIONARY_H
