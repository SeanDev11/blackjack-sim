// Deck.cpp

#include "Deck.hpp"
#include "Card.hpp"
#include "Game.hpp"

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
    for (int i = 0; i < 3; i++) {
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

    setAces();

    // Shuffle all unused cards
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::shuffle(std::begin(unusedCards), std::end(unusedCards), rng);
}


int Deck::getCardCount() {
    return numDecks*52;
}

Card* Deck::getTop(Game * gm) {
    // Gets and removes top (back) card
    // ADDED THIS TO DEAL DOWN TO FEWER CARDS
    if (unusedCards.size() == 0) {
        
        shuffle();
        burnCard(gm);
        gm->setPointCount(0);
        gm->setTotalSeenCards(0);
        gm->incrementShuffleCount();
        
    }
    Card* c = unusedCards.back();
    
    usedCards.push_back(c);
    
    unusedCards.pop_back();    
    
    return c;
}

void Deck::burnCard(Game * gm) {
    getTop(gm);
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

void Deck::printDeck() {
    shuffle();
    int cardCount[10] = { 0 };
    /*int two = 0;
    int three = 0;
    int four = 0;
    int five = 0;
    int six = 0;
    int seven = 0;
    int eight = 0;
    int nine = 0;
    int ten = 0;
    int eleven = 0;*/
    
    for (Card* c : unusedCards) {
        cardCount[c->getValue()-2] += 1;
        //std::cout << c->getValue() << std::endl;
    }

    for (int i = 0; i < 10; i++) {
        std::cout << i+2 << "'s: " << cardCount[i] << std::endl;
    }


}