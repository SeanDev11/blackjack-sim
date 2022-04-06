// Game.cpp

#include "Game.hpp"

Game::Game(int numDecks, int numPlayers) 
: deck{new Deck(numDecks)}
{
    for (int i = 0; i < numPlayers; i++) {
        players.push_back(new Player());
    }


}

void Game::settleBets() {
    // Only applies when player hasnt had a natural
    // If not, pay out depends on dealer bust / player score
    // Check for player busts
    for (Player *p : players) {
        if (p->getScore() > 21) {
            // Player loses bet
            p->decreaseCapital(p->getBetAmount());
            p->settleBet();
        }
    }
    // Check for dealer bust
    if (dealer.getScore() > 21) {
        for (Player *p : players) {
            if (p->isSettled() == false) {
                // Player wins bet
                p->increaseCapital(p->getBetAmount());
                p->settleBet();
            }
        }
    } else {
        for (Player *p : players) {
            if (p->isSettled() == false) {
                if (p->getScore() > dealer.getScore()) {
                    // Player wins bet
                    p->increaseCapital(p->getBetAmount());
                    p->settleBet();
                } else if (p->getScore() < dealer.getScore()) {
                    // Player loses bet
                    p->decreaseCapital(p->getBetAmount());
                    p->settleBet();
                } else {
                    // No money changes hands
                    p->settleBet();
                }
            }
        }
    }
}

void Game::play() {
    // Shuffle and cut the decks
    
    deck->shuffle();
    
    // Burn a card (done by player in casino)
    deck->burnCard();
    // Repeat for number of hands specified
    for (int i = 0; i < handsToPlay; i++) {
        // Clear visible cards
        // MIGHT HAVE TO CHANGE SO THAT ELEMENTS ARE NOT DELETED. ALSO SEE POP_BACK USAGE TO AVOID DESTROYING ELEMENTS
        visibleCards.clear();

        // Players place bets
        double hiLoIndex = getHiLoIdx();
        for (Player *p : players) {
            p->placeBet(hiLoIndex);
        }
        // Cards are dealt
        initialDeal();
        // CHECK FOR NATURALS HERE?
        checkNaturals();

        for (Player *p : players) {
            // Make decision ends when player busts or decides to stand
            // HANDLE BUSTS
            if (p->isSettled() == false) {
                while (p->makeDecision() == 0) {
                    p->dealCard(deck->getTop());
                }
            }
        }
        // Make decision ends when dealer busts or decides to stand
        while (dealer.makeDecision() == 0) {
            dealer.dealCard(deck->getTop());
        }
        // Settle bets
        settleBets();

        totalSeenCards += visibleCards.size();
        pointCount = getPointCount();

        if ((double(usedCardsCount)/(deck->getCardCount()*52)) >= 0.75) {
            deck->shuffle();
            deck->burnCard();
            totalSeenCards = 0;
            pointCount = 0;
        }
    }
}

void Game::checkNaturals() {
    // If natural -> settle bet
    // NATURAL PAYS 3:2
    // Check dealer natural
    if (dealer.getScore() == 21) {
        for (Player *p : players) {
            if (p->getScore() == 21) {
                // No money changes hands
                p->settleBet();
            } else {
                // Player loses bet amount
                p->decreaseCapital(p->getBetAmount());
                p->settleBet();
            }
        }
    } else {
        for (Player *p : players) {
            if (p->getScore() == 21) {
                // Player gets paid 3:2
                p->increaseCapital(0.5*p->getBetAmount());
                p->settleBet();
            }
        }
    }

}

void Game::initialDeal() {
    // Deal to each player starting to the left of the dealer and going clockwise
    for (int i = 0; i < 2; i++) {
        for (Player *p : players) {
            Card *dealt = deck->getTop();
            visibleCards.push_back(dealt);
            p->dealCard(dealt);
        }
        // Deal to dealer. First one face down, second face up
        if (i == 0) {
            Card *dealt = deck->getTop();
            dealer.dealCard(dealt);
        } else {
            Card *dealt = deck->getTop();
            visibleCards.push_back(dealt);
            dealer.dealCard(dealt);
        }
    }

}

double Game::getHiLoIdx() {
    double idx = 100*(double(getPointCount())/(deck->getCardCount()-totalSeenCards));
    return idx;
}


int Game::getPointCount() {
    int cnt;
    for (int i = 0; i < visibleCards.size(); i++) {
        switch (visibleCards[i]->getValue()) {
            case 1:
                cnt += -1;
                break;
            case 10:
                cnt += -1;
                break;
            case 11:
                cnt += -1;
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            default:
                cnt += 1;
        }
    }
    return pointCount + cnt;
}