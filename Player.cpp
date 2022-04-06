// Player.cpp

#include "Player.hpp"
// MIGHT HAVE TO PUT INTO HEADER
#include "Card.hpp"

Player::Player() {}

void Player::placeBet(double idx) {
    betSettled = false;
    // DECISION MAKING BASED ON FAVORABLE SITUATION
    int bet = 10;
    if (idx < 3) {
        bet = 10;
    } else if (idx < 5) {
        bet = 20;
    } else if (idx < 7) {
        bet = 30;
    } else if (idx < 9) {
        bet = 40;
    } else {
        bet = 50;
    }
    betAmount = bet;
}

int Player::makeDecision() {
    // DECISION TO HIT OR STAND
    // 0 = hit, 1 = stand
    int decision = 0;


    return decision;
}

bool Player::isSettled() {
    return betSettled;
}

int Player::getBetAmount() {
    return betAmount;
}

int Player::getScore() {
    int score = 0;
    for (Card *c : cards) {
        // Add up scores
        score += c->getValue();
    }
    return score;
}

void Player::dealCard(Card *c) {
    cards.push_back(c);
}

int Player::getCapital() {
    return capital;
}

void Player::increaseCapital(int win) {
    capital += win;
}

void Player::decreaseCapital(int loss) {
    capital -= loss;
}

void Player::settleBet() {
    betSettled = true;
}