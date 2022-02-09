#include <iostream>
#include <vector>
#include <string>

#include "HangMan.h"

int main() {
    std::string name{};
    std::cout << "Please enter your name: \n>";
    std::cin >> name;

    HangMan game{name};
    game.startGame();
    return 0;
}
