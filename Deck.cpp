// Deck.cpp

#include "Deck.hpp"
#include "Card.hpp"


Deck::Deck(int numberOfDecks) 
    : numDecks{numberOfDecks}
{
    for (int i = 2; i < 12; i++) {
        // Add 4 of each card per deck(4 suits)
        for (int x = 0; x < 4*numDecks; x++) {
            unusedCards.push_back(new Card(i));
        }
    }
    // Add face cards for each deck
    for (int i = 0; i < 3*numDecks; i++) {
        for (int x = 0; x < 4*numDecks; x++) {
            unusedCards.push_back(new Card(10));
        }
    }
}

void Deck::shuffle()
{
    // Copy cards from used to unused
    int size = usedCards.size();
    for (int i = size-1; i > -1; i--) {
        unusedCards.push_back(usedCards[i]);
        usedCards.pop_back();
    }
    // TEST REMOVE LATER
    if (usedCards.size() != 0) {
        std::cout << "ERROR IN SHUFFLE!!!";
    }
    // Shuffle all unused cards
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(std::begin(unusedCards), std::end(unusedCards), rng);
}


int Deck::getCardCount() {
    return numDecks*52;
}

Card* Deck::getTop() {
    // Gets and removes top (back) card
    Card* c = unusedCards.back();
    usedCards.push_back(c);
    unusedCards.pop_back();    
    return c;
}

void Deck::burnCard() {
    getTop();
}


int Deck::getUsedCardCount() {
    return usedCards.size();
}

void Deck::setAces() {
    for (Card* c : unusedCards) {
        if (c->getValue() == 1) {
            c->setValue(11);
        }
    } 
}