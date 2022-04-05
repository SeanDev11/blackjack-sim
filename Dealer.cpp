// Dealer.cpp

#include "Dealer.hpp"

#include "Card.hpp"

Dealer::Dealer() {}


int Dealer::makeDecision() {
    // returns 0 if hit, 1 if stand


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