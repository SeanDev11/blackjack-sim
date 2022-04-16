// Deck.hpp

#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

#include "Card.hpp"

class Game;

class Deck
{
public:

    Deck(int numberOfDecks);

    void shuffle();
    void burnCard(Game * gm);

    Card* getTop(Game * gm);
    int getCardCount();

    int getUsedCardCount();

    void setAces();

    void printDeck();

private:
    int numDecks;

    std::vector<Card*> unusedCards;

    std::vector<Card*> usedCards;


};


#endif