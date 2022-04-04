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
    // Only applies when player hasnt busted or had a natural
    // If not, pay out depends on dealer bust / player score
    
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
        for (Player *p : players) {
            p->placeBet();
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

        if ((double(usedCardsCount)/(deck->getCardCount()*52)) >= 0.75) {
            deck->shuffle();
            deck->burnCard();
        }
    }
}

void Game::checkNaturals() {
    // If natural -> settle bet


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