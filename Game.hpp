// Game.hpp

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include "Player.hpp"
#include "Deck.hpp"
#include "Dealer.hpp"
#include "Card.hpp"

class Game
{
public:
    Game(int numDecks, int numPlayers);

    void play();

    std::vector<Card*> visibleCards;


private:
    std::vector<Player*> players;

    Deck *deck;

    Dealer dealer;

    int usedCardsCount;

    int handsToPlay;


    void initialDeal();

    void settleBets();

    void checkNaturals();
    
};

#endif