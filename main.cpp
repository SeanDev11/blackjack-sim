// main.cpp

#include <iostream>
#include "Game.hpp"

int main() {
    Game game = Game(2, 1, 100000);

    game.play();

    game.printPlayerStats();

    return 0;
}