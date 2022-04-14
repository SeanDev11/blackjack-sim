// Game.hpp

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

#include "Deck.hpp"
#include "Dealer.hpp"
#include "Card.hpp"

namespace constants
{
    const bool LOGGING = false;

}

class Player;

class Game
{
public:
    Game(int numDecks, int numPlayers, int hands);

    void play();

    std::vector<Card*> visibleCards;

    double getHiLoIdx();

    int getPointCount();

    void printPlayerStats();

private:
    std::vector<Player*> players;

    Deck *deck;

    Dealer dealer;

    //int usedCardsCount = 0;

    int totalSeenCards = 0;

    int handsToPlay;

    int pointCount = 0;

    void initialDeal();

    void settleBets();

    void checkNaturals();

    int shuffleCnt = 0;

    int playerDrawCnt[7] = {0,0,0,0,0,0,0};

    int playerNaturalCnt[7] = {0,0,0,0,0,0,0};

    int playerTieCnt[7] = {0,0,0,0,0,0,0};
    
};

#endif