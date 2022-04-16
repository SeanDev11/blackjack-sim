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
    
    int makeDecision_v2(int dealerUpCard, int hand, Deck* deck, double hiLoIdx, Game* gm);

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

    int getMaxLoss();
    int getMaxWin();
    void setMaxWin(int win);
    void setMaxLoss(int loss);


    void incrementBustCnt();
    int getBustCnt();

    int getTotalInitialBets();

private:
    bool betSettled[4] = {false, false, false, false};
    int betAmount[4] = {0, 0, 0, 0};
    int capital = 0;

    bool hasAce(int hand);

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

    int maxLoss = -1;
    int maxWin = -1;


    int bustCnt = 0;

    int totalInitialBets = 0;

    // Contains the index needed to split, 200 = always split, 300 = never split
    // Splitting 8,8 against a 10 when index is LESS THAN 24
    // Split 3,3 against an 8 when the idx is greater than 6 and less than -2
    int pairSplitDecision[11][11] = {{-17, 200, 200, 200, 200, 200, -33, -24, -22, -20, -17},
                                     {300, -9, -15, -22, -30, 200, 200, 300, 300, 300, 300},
                                     {300, -21, -34, 200, 200, 200, 200, 6, 300, 300, 300},
                                     {300, 300, 18, 8, 0, 300, 300, 300, 300, 300, 300},
                                     {300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300},
                                     {300, 0, -3, -8, -13, -16, -8, 300, 300, 300, 300},
                                     {300, -22, -29, -35, 200, 200, 200, 200, 300, 300, 300},
                                     {-18, 200, 200, 200, 200, 200, 200, 200, 200, 24, -18},
                                     {10, -3, -8, -10, -15, -14, 8, -16, -22, 300, 10},
                                     {300, 25, 17, 10, 6, 7, 19, 300, 300, 300, 300},
                                     {-17, 200, 200, 200, 200, 200, -33, -24, -22, -20, -17}};

    // Contains the index needed to double down, 300 = never double down 
    int softDoubleDownDecision[11][11] = {{300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300},
                                          {300, 300, 10, 2, -19, -13, 300, 300, 300, 300, 300},
                                          {300, 300, 11, -3, -13, -19, 300, 300, 300, 300, 300},
                                          {300, 300, 19, -7, -16, -23, 300, 300, 300, 300, 300},
                                          {300, 300, 21, -6, -16, -32, 300, 300, 300, 300, 300},
                                          {300, 1, -6, -14, -28, -30, 300, 300, 300, 300, 300},
                                          {300, 300, -2, -15, -18, -23, 300, 300, 300, 300,300},
                                          {300, 300, 9, 5, 1, 0, 300, 300, 300, 300, 300},
                                          {300, 300, 20, 12, 8, 8, 300, 300, 300, 300, 300},
                                          {300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300},
                                          {300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300}};
    
    // Contains the index needed to double down, 300 = never double down
    int hardDoubleDownDecision[7][11] = {{300, 300, 300, 300, 20, 26, 300, 300, 300, 300, 300},
                                         {300, 300, 300, 27, 18, 24, 300, 300, 300, 300, 300},
                                          {300, 300, 45, 21, 14, 17, 300, 300, 300, 300, 300},
                                          {300, 300, 22, 11, 5, 5, 22, 300, 300, 300, 300},
                                          {300, 3, 0, -5, -10, -12, 4, 14, 300, 300,300},
                                          {6, -15, -17, -21, -24, -26, -17, -9, -3, 7, 6},
                                          {-3, -23, -26, -29, -33, -35, -26, -16, -10, -9, -3}};

    // 200 = draw, 300 = stand
    int hardDrawingDecision[6][11] = {{200, 14, 6, 2, -1, 0, 200, 200, 200, 200, 200},
                                      {200, 1, -2, -5, -9, -8, 50, 200, 200, 200, 200},
                                      {200, -5, -8, -13, -17, -17, 20, 38, 200, 200, 200},
                                      {16, -12, -17, -21, -26, -28, 13, 15, 12, 8, 16},
                                      {14, -21, -25, -30, -34, -35, 10, 11, 6, 2, 14},
                                      {-15, 300, 300, 300, 300, 300, 300, 300, 300, 300, -15}};

    int softDrawingDecision[2][11] = {{200, 200, 200, 200, 200, 200, 29, 200, 200, 200, 200},
                                      {-6, 300, 300, 300, 300, 300, 300, 300, 200, 12, -6}};

};

#endif