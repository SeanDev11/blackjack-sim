// Game.hpp

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>


#include "Dealer.hpp"
#include "Card.hpp"

namespace constants
{
    const bool LOGGING = false;
    const bool TRACING = false;
    const bool DOUBLING = true;
    const bool SPLITTING = true;
}

class Player;
class Deck;

class Game
{
public:
    Game(int numDecks, int numPlayers, int hands);

    void play();

    std::vector<Card*> visibleCards;

    double getHiLoIdx();

    int getPointCount();
    void setPointCount(int i);

    void setTotalSeenCards(int i);
    void printPlayerStats();

    int getPlayerBalance(int i);

    void incrementShuffleCount();

private:
    std::vector<Player*> players;

    Deck *deck;

    Dealer dealer;

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

    int dealerNaturalCnt = 0;
    
};

#endif