// main.cpp

#include <iostream>
#include "Game.hpp"

int main() {
    Game game = Game(1, 1, 1);

    std::cout << "Testing" << std::endl;

    game.play();

    game.printPlayerBalances();

    std::cout << "Ended Testing" << std::endl;

    return 0;
}