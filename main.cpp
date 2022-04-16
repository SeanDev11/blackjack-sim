// main.cpp

#include <iostream>
#include "Game.hpp"

int main() {
    int winnings = 0;
    for (int i = 0; i < 1; i++) {
        Game game = Game(2, 1, 1000000);
        game.play();
        winnings += game.getPlayerBalance(0);
        game.printPlayerStats();
    }

    
    std::cout << "Total winnings: $ " << winnings << " Average winnings per 10 hands: $ " << double(winnings)/10000 << " Average winnings per hand: $ " << double(winnings)/1000000 << std::endl;
    return 0;
}