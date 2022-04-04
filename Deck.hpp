// Deck.hpp

#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

class Deck
{
public:

    Deck(int numberOfDecks);

    void shuffle();
    void burnCard();

    Card* getTop();
    int getCardCount();
private:
    int numDecks;

    std::vector<Card*> unusedCards;

    std::vector<Card*> usedCards;


};




#endif