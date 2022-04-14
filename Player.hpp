// Player.hpp

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "Card.hpp"
#include "Deck.hpp"
#include <iostream>
#include "Game.hpp"

class Player
{
public:
    void placeBet(double idx);
    int makeDecision(int dealerUpCard, int hand, Deck* deck, double hiLoIdx, Game* gm);
    bool isSettled();

    int getBetAmount(int hand);
    int getCapital();
    void increaseCapital(int win);
    void decreaseCapital(int loss);

    void dealCard(Card* c, int i, Game* gm);

    void settleBet(int hand);

    int getScore(int hand);

    bool isStanding(int hand);

    int getNumHands();
private:
    bool betSettled[4] = {false, false, false, false};
    int betAmount[4] = {0, 0, 0, 0};
    int capital;

    bool standing[4] = {false, false, false, false};

    //std::vector<Card*> cards;

    std::vector< std::vector<Card*> > hands;
    
    void doubleDown(int hand, Deck* deck, Game* gm);

    void splitPair(int hand, Deck* deck, Game* gm);

    bool isHardHand(int hand);
};

#endif