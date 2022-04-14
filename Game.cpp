// Game.cpp

#include "Game.hpp"
#include "Player.hpp"

Game::Game(int numDecks, int numPlayers, int hands) 
: deck{new Deck(numDecks)}, handsToPlay{hands}
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
        for (int i = 0; i < p->getNumHands(); i++) {
            if (p->getScore(i) > 21) {
                // Player loses bet
                p->decreaseCapital(p->getBetAmount(i));
                p->settleBet(i);
            }
        }
    }
    // Check for dealer bust
    if (dealer.getScore() > 21) {
        for (Player *p : players) {
            if (p->isSettled() == false) {
                // Player wins bet
                for (int i = 0; i < p->getNumHands(); i++) {
                    p->increaseCapital(p->getBetAmount(i));
                    p->settleBet(i);
                }
            }
        }
    } else {
        for (Player *p : players) {
            if (p->isSettled() == false) {
                for (int i = 0; i < p->getNumHands(); i++) {
                    if (p->getScore(i) > dealer.getScore()) {
                        // Player wins bet
                        p->increaseCapital(p->getBetAmount(i));
                        p->settleBet(i);
                    } else if (p->getScore(i) < dealer.getScore()) {
                        // Player loses bet
                        p->decreaseCapital(p->getBetAmount(i));
                        p->settleBet(i);
                    } else {
                        // No money changes hands
                        p->settleBet(i);
                    }
                }
            }
        }
    }
}

void Game::play() {


    // Shuffle and cut the decks
    if (constants::LOGGING) {
        std::cout << "Shuffling" << std::endl;
    }
    deck->shuffle();
    
    // Burn a card (done by player in casino)
    if (constants::LOGGING) {
        std::cout << "Burning" << std::endl;
    }
    deck->burnCard();
    // Repeat for number of hands specified
    for (int i = 0; i < handsToPlay; i++) {
        // Clear visible cards
        // MIGHT HAVE TO CHANGE SO THAT ELEMENTS ARE NOT DELETED. ALSO SEE POP_BACK USAGE TO AVOID DESTROYING ELEMENTS
        std::cout << "Hand: " << i << std::endl;
        if (constants::LOGGING) {
            std::cout << "Clearing visible cards" << std::endl;
        }

        for (Card* c : visibleCards) {
            std::cout << c->getValue() << " ";

        }
        std::cout << std::endl;
        visibleCards.clear();
        if (constants::LOGGING) {
            std::cout << "Placing bets" << std::endl;
        }
        // Players place bets
        double hiLoIndex = getHiLoIdx();

        std::cout << "HILO IDX " << hiLoIndex << std::endl;

        
        

        for (Player *p : players) {
            p->placeBet(hiLoIndex);
        }
        if (constants::LOGGING) {
            std::cout << "Initial Deal" << std::endl;
        }
        // Cards are dealt
        initialDeal();
        if (constants::LOGGING) {
            std::cout << "Naturals check" << std::endl;
        }
        // CHECK FOR NATURALS HERE?
        checkNaturals();
        if (constants::LOGGING) {
            std::cout << "Making decision" << std::endl;
        }
        for (Player *p : players) {
            // Make decision ends when player busts or decides to stand
            // HANDLE BUSTS
            if (p->isSettled() == false) {
                for (int i = 0; i < 4; i++) {
                    while (p->makeDecision(dealer.getUpCard(), i, deck, getHiLoIdx(), this) == 0) {
                        std::cout << "WHEELIN DEALIN " << std::endl;
                        p->dealCard(deck->getTop(), i, this);
                    }
                }
            }
        }

        visibleCards.push_back(dealer.getCard(1));

        if (constants::LOGGING) {
            std::cout << "Dealer decision" << std::endl;
        }
        // Make decision ends when dealer busts or decides to stand
        while (dealer.makeDecision() == 0) {
            dealer.dealCard(deck->getTop());
        }
        if (constants::LOGGING) {
            std::cout << "Settling bets" << std::endl;
        }
        // Settle bets
        settleBets();

        totalSeenCards += visibleCards.size();
        pointCount = getPointCount();
        if (constants::LOGGING) {
            std::cout << "USED CARDS COUNT: " << deck->getUsedCardCount() << std::endl;
        }
        if ((double(deck->getUsedCardCount())/(deck->getCardCount())) >= 0.75) {
            std::cout << "SHUFFLING DECK AGAIN" << std::endl;
            deck->shuffle();
            deck->burnCard();
            totalSeenCards = 0;
            pointCount = 0;
        }

        std::cout << std::endl;
    }
}

void Game::checkNaturals() {
    // If natural -> settle bet
    // NATURAL PAYS 3:2
    // Check dealer natural
    if (dealer.getScore() == 21) {
        for (Player *p : players) {
            if (p->getScore(0) == 21) {
                // No money changes hands
                p->settleBet(0);

            } else {
                // Player loses bet amount
                p->decreaseCapital(p->getBetAmount(0));
                p->settleBet(0);
            }
        }
    } else {
        for (Player *p : players) {
            if (p->getScore(0) == 21) {
                // Player gets paid 3:2
                p->increaseCapital(0.5*p->getBetAmount(0));
                p->settleBet(0);
            }
        }
    }

}

void Game::initialDeal() {
    // Deal to each player starting to the left of the dealer and going clockwise
    for (int i = 0; i < 2; i++) {
        if (constants::LOGGING) {
            std::cout << "Dealing to players" << std::endl;
        }
        for (Player *p : players) {
            if (constants::LOGGING) {
                std::cout << "Get top" << std::endl;
            }
            Card *dealt = deck->getTop();
            if (constants::LOGGING) {
                std::cout << "add to visible cards" << std::endl;
            }
            // visibleCards.push_back(dealt);
            if (constants::LOGGING) {
                std::cout << "Deal card" << std::endl;
            }
            p->dealCard(dealt, 0, this);
        }
        if (constants::LOGGING) {
            std::cout << "Dealing to dealer" << std::endl;
        }
        // Deal to dealer. First one face up, second face down
        if (i == 0) {
            Card *dealt = deck->getTop();
            visibleCards.push_back(dealt);
            dealer.dealCard(dealt);
        } else {
            Card *dealt = deck->getTop();
            dealer.dealCard(dealt);
        }
    }

}

double Game::getHiLoIdx() {
    std::cout << "POINT COUNT: " << double(getPointCount()) << " CARD COUNT: " << deck->getCardCount() << " " << "SEEN CARDS: " << totalSeenCards << std::endl;

    double idx = 100*(double(getPointCount())/(deck->getCardCount()-(totalSeenCards+visibleCards.size())));
    return idx;
}


int Game::getPointCount() {
    
    int cnt = 0;
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


void Game::printPlayerBalances() {
    int i = 1;
    for (Player *p : players) {
        std::cout << "Player " << i << ": $";
        std::cout << p->getCapital() << std::endl;

    }


}