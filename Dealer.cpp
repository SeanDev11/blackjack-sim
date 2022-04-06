// Dealer.cpp

#include "Dealer.hpp"

#include "Card.hpp"

Dealer::Dealer() {}


int Dealer::makeDecision() {
    // returns 0 if hit, 1 if stand
    // Dealer stands on soft 17
    int score = getScore();
    if (score > 16) {
        if (score > 21) {
            for (Card *c : cards) {
                if (c->getValue() == 11) {
                    c->setValue(1);
                    return makeDecision(); 
                }
            }
        }
        return 1;
    } else {
        return 0;
    }

}

void Dealer::dealCard(Card *c) {
    cards.push_back(c);
}

int Dealer::getScore() {
    int score = 0;
    for (Card *c : cards) {
        // Add up scores
        score += c->getValue();
    }
    return score;
}

