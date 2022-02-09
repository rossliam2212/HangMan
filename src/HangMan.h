//
// Created by Liam Ross on 09/02/2022.
//

#ifndef HANGMAN_HANGMAN_H
#define HANGMAN_HANGMAN_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <iomanip>

#include "Dictionary.h"

class HangMan {
private:
    std::string name;
    Dictionary dictionary;

    std::string word;
    std::vector<char> guesses;
    int numCorrectGuesses;
    int numIncorrectGuesses;
    std::vector<char> wrongGuesses;

    bool newGame;

    const int width{12};

public:
    explicit HangMan(std::string name);
    ~HangMan() = default;

    void startGame();

private:
    void printWelcome() const;
    void printInstructions() const;
    void getPlayerInput();
    void checkPlayerGuess(char guess);
    void setUp();
    bool printWordState();
    void printHangMan() const;
    void printWrongGuesses();
    void handleGameWin();
    void handleLoseGame();
    void playAgain();
    void resetGame();
};


#endif //HANGMAN_HANGMAN_H
