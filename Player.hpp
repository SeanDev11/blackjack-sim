// Player.hpp

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

class Player
{
public:
    void placeBet();
    int makeDecision();
    bool isSettled();

    int getBetAmount();
    int getCapital();
    void increaseCapital(int win);
    void decreaseCapital(int loss);

    void dealCard(Card* c);
private:
    bool betSettled;
    int betAmount;
    int capital;

    std::vector<Card*> cards;

    int getScore();
};

#endif