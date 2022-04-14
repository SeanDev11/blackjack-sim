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

    void printPlayerBalances();

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
    
};

#endif