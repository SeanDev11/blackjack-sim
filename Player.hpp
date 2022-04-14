// Player.hpp

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <vector>

#include "Card.hpp"
#include "Deck.hpp"
#include <iostream>

class Game;

class Player
{
public:
    void placeBet(double idx);
    int makeDecision(int dealerUpCard, int hand, Deck* deck, double hiLoIdx, Game* gm);
    

    int getBetAmount(int hand);
    int getCapital();
    void increaseCapital(int win);
    void decreaseCapital(int loss);

    void dealCard(Card* c, int i, Game* gm);

    void settleBet(int hand);
    bool isSettled(int hand);

    int getScore(int hand);

    bool isStanding(int hand);

    int getNumHands();

    std::vector<Card*> getHand(int hand);

    void insure(int hand);
    bool isInsured();
    int getSideBet();

    void clearHands();
    void resetInsurance();
    
    int getSplitPairCnt();
    int getDoubleDownCnt();
    int getWinCnt();
    int getLossCnt();

private:
    bool betSettled[4] = {false, false, false, false};
    int betAmount[4] = {0, 0, 0, 0};
    int capital = 0;

    bool insured = false;
    int sideBet = 0;

    bool standing[4] = {false, false, false, false};

    //std::vector<Card*> cards;

    std::vector< std::vector<Card*> > hands;
    
    void doubleDown(int hand, Deck* deck, Game* gm);

    bool checkHandMakeup(int hand, int c1, int c2);

    void splitPair(int hand, Deck* deck, Game* gm);

    bool isHardHand(int hand);

    void resetBets();

    int doubleDownCnt = 0;

    int splitPairCnt = 0;

    int winCnt = 0;
    int lossCnt = 0;

};

#endif