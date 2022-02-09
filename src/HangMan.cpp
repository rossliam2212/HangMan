//
// Created by Liam Ross on 09/02/2022.
//

#include "HangMan.h"

#define underline "\033[4m" // Add underline to text
#define removeUnderline "\033[0m" // Remove underline from text
#define green "\x1B[32m" // Make text green
#define red "\x1B[31m" // Make text red
#define white "\x1B[97m" // Make text white

HangMan::HangMan(std::string name) :
        name{std::move(name)},
        word{},
        dictionary{},
        guesses{},
        wrongGuesses{},
        guessesRemaining{},
        numIncorrectGuesses{},
        numCorrectGuesses{},
        newGame{true} {
}

void HangMan::startGame() {
    setUp();

    if (newGame) {
        printWelcome();
        printInstructions();
        newGame = false;
    }

    std::cout << underline << green << "\n- Game Started!" << white << removeUnderline << std::endl;
    std::cout << "Your word is " << word.length() << " letters" << std::endl;

    while (true) {
        printHangMan();
        if (numIncorrectGuesses >= 6) {
            handleLoseGame();
            break;
        }
        printWrongGuesses();

        getPlayerInput();
        if (printWordState()) {
            handleGameWin();
            break;
        }
    }
}

void HangMan::getPlayerInput() {
    char guess{};
    std::cout << underline << green << "\nPlease enter your guess:" << white << removeUnderline << "\n>";
    std::cin >> guess;

    checkPlayerGuess(guess);
}

void HangMan::checkPlayerGuess(char guess) {
    for (const auto& c : word) {
        if (std::find(word.begin(), word.end(), guess) != word.end()) {
            guesses.push_back(guess);
            return;
        }
    }
    wrongGuesses.push_back(guess);
    numIncorrectGuesses++;
}

bool HangMan::printWordState() {
    std::cout << "\n";

    int correctGuessCount{};
    std::cout << "Your Word (" << word.length() << " letters): " << std::endl;
    for (const auto& c : word) {
        if (std::find(guesses.begin(), guesses.end(), c) != guesses.end()) {
            std::cout << c;
            correctGuessCount++;
        } else {
            std::cout << "_";
        }
    }
    std::cout << "\n";
    numCorrectGuesses = correctGuessCount;
    return correctGuessCount == word.length();
}

void HangMan::printWrongGuesses() {
    std::cout << "\n===========================" << std::endl;
    std::cout << "| Letters Remaining: " << std::setw(3) << std::right << "" << (word.length() - numCorrectGuesses) << " |" << std::endl;
    std::cout << "| Incorrect Guesses: " << std::setw(3) << std::right << "" << numIncorrectGuesses << " |" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "| Correct Letters:";
    for (const auto& c : guesses)
        std::cout << green << c << " " << white;
    std::cout << "\n| Incorrect Letters:";
    for (const auto& c : wrongGuesses)
        std::cout << red << c << " " << white;
    std::cout << "\n===========================" << std::endl;
}

void HangMan::handleGameWin() {
    std::cout << green << "\nCongratulations " << name << "! You win!" << white << std::endl;

    playAgain();
}

void HangMan::handleLoseGame() {
    std::cout << red << "\n\nGame Over! Hard Luck " << name << white << std::endl;
    std::cout << "Your word was: " << word << std::endl;

    playAgain();
}

void HangMan::playAgain() {
    std::cout << "\nWould you like to play again? (y/n) \n>";
    char playAgain{};
    std::cin >> playAgain;

    while (tolower(playAgain) != 'y' && tolower(playAgain) != 'n') {
        std::cout << "Invalid option! Try again (y/n) \n>";
        std::cin >> playAgain;
    }

    if (playAgain == 'y') {
        resetGame();
    } else {
        std::cout << "\nThanks for playing " << name << "!" << std::endl;
    }
}

void HangMan::resetGame() {
    guesses.clear();
    wrongGuesses.clear();
    numIncorrectGuesses = 0;
    numCorrectGuesses = 0;

    startGame();
}

void HangMan::printHangMan() const {
    std::cout << "\n";
    std::cout << " ------+" << std::endl;
    std::cout << " |     |" << std::endl;

    if (numIncorrectGuesses >= 1)
        std::cout << red << " O    " << white << std::endl;
    if (numIncorrectGuesses >= 2) {
        std::cout << red << "\\ " << white;
        if (numIncorrectGuesses >= 3)
            std::cout << red << "/" << white << std::endl;
        else
            std::cout << "\n";
    }
    if (numIncorrectGuesses >= 4)
        std::cout << red << " | " << white << std::endl;

    if (numIncorrectGuesses >= 5) {
        std::cout << red << "/ " << white;
        if (numIncorrectGuesses >= 6)
            std::cout << red << "\\" << white;
        else
            std::cout << "\n";
    }
}

void HangMan::printWelcome() const {
    std::cout << green << "\n===== Welcome to Hang Man " << name << "! =====" << white << std::endl;
    std::cout << std::setw(width) << std::left << "" << " ------+" << std::endl;
    std::cout << std::setw(width) << std::left << "" << " |     |" << std::endl;
    std::cout << std::setw(width) << std::left << "" << " O    -+-" << std::endl;
    std::cout << std::setw(width) << std::left << "" << "\\ /" << std::endl;
    std::cout << std::setw(width) << std::left << "" << " | " << std::endl;
    std::cout << std::setw(width) << std::left << "" << "/ \\" << std::endl;
}

void HangMan::setUp() {
    dictionary.setCurrentWord();
    word = dictionary.getCurrentWord();
    std::cout << "Word: " << word << std::endl;
}

void HangMan::printInstructions() const {
    std::cout << underline << green << "\n- Game Instructions" << white << removeUnderline << std::endl;
    std::cout << "- When the game starts, you will be given a random word to guess, which is represented by a row of underscores (e.g ______)"
              << "\n- You will be asked to guess one letter from the word every turn."
                 "\n  If your guess is correct, the letter will be revealed in the correct positions."
                 "\n  If your guess is incorrect, one part of the stick man will be drawn."
             << "\n- If you guess incorrectly 6 times, the stick man will be hung and the game is over."
             << "\n- If you guess the word correctly before the stick man is hung, you win!" << std::endl;

}
