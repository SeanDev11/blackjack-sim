// Game.cpp

#include "Game.hpp"
#include "Player.hpp"
#include "Deck.hpp"

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
            if (p->isSettled(i) == false) {
                if (p->getScore(i) > 21) {
                    // Player loses bet
                    p->incrementBustCnt();
                    p->decreaseCapital(p->getBetAmount(i));
                    p->settleBet(i);
                }
            }
        }
    }
    // Check for dealer bust
    if (dealer.getScore() > 21) {
        for (Player *p : players) {
            //if (p->isSettled() == false) {
                // Player wins bet
                for (int i = 0; i < p->getNumHands(); i++) {
                    if (p->isSettled(i) == false) {
                        p->increaseCapital(p->getBetAmount(i));
                        p->settleBet(i);
                    }
                }
            //}
        }
    } else {
        for (Player *p : players) {
            //if (p->isSettled() == false) {
                for (int i = 0; i < p->getNumHands(); i++) {
                    if (p->isSettled(i) == false) {
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
                            playerTieCnt[0] += 1;
                            p->settleBet(i);
                        }
                    }
                }
            //}
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
    deck->burnCard(this);
    // Repeat for number of hands specified
    for (int i = 0; i < handsToPlay; i++) {
        // Clear visible cards
        // MIGHT HAVE TO CHANGE SO THAT ELEMENTS ARE NOT DELETED. ALSO SEE POP_BACK USAGE TO AVOID DESTROYING ELEMENTS
        dealer.clearHand();

        for (Player *p : players) {
            p->clearHands();
            p->resetInsurance();
        }

        deck->setAces();

        if (constants::LOGGING) {
            std::cout << "Hand: " << i << std::endl;
            std::cout << "Clearing visible cards" << std::endl;
        }
        if (constants::LOGGING) {
            for (Card* c : visibleCards) {
                std::cout << c->getValue() << " ";
            }
        }
        
        visibleCards.clear();
        if (constants::LOGGING) {
            std::cout << "Placing bets" << std::endl;
        }
        if (constants::TRACING) {
            std::cout << "-------------------------" << std::endl;
            std::cout << "Hand: " << i << std::endl;

        }

        // Players place bets
        double hiLoIndex = getHiLoIdx();
        if (constants::TRACING) {
            std::cout << "Pre-bet idx: " << hiLoIndex << std::endl;
        }

        if (constants::LOGGING) {
            std::cout << "HILO IDX " << hiLoIndex << std::endl;
        }

        for (Player *p : players) {
            p->placeBet(hiLoIndex);
        }

        if (constants::TRACING) {
            std::cout << "Initial bet: " << players[0]->getBetAmount(0) << std::endl;
        }

        if (constants::LOGGING) {
            std::cout << "Initial Deal" << std::endl;
        }
        // Cards are dealt
        initialDeal();

        if (constants::TRACING) {
            std::cout << "Hole cards" << std::endl;
            std::cout << "Player: " << players[0]->getHand(0)[0]->getValue() << " " << players[0]->getHand(0)[1]->getValue() << std::endl;
            std::cout << "Dealer: " << dealer.getUpCard() << " " << dealer.getCard(1)->getValue() << std::endl;
        }

        // Insurance
        if (dealer.getUpCard() == 11) {
            if (getHiLoIdx() > 8) {
                // Insure
                for (Player *p : players) {
                    p->insure(0);
                }
            }

        }

        if (constants::TRACING) {
            std::cout << "Insured: " << players[0]->isInsured() << " " << players[0]->getSideBet() << std::endl;
        } 
        
        if (constants::LOGGING) {
            std::cout << "Player: ";
            for (Player *p : players) {
                for (Card *c : p->getHand(0)) {
                    std::cout << c->getValue() << " ";
                }
            }
            std::cout << "= " << players[0]->getScore(0) << std::endl;

            std::cout << "Dealer: ";
            for (Card* c : dealer.getHand()) {
                std::cout << c->getValue() << " ";
            }

            std::cout << "= " << dealer.getScore() << std::endl;
        }

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
            if (p->isSettled(0) == false) {
                for (int j = 0; j < p->getNumHands(); j++) {
                    while (p->makeDecision_v2(dealer.getUpCard(), j, deck, getHiLoIdx(), this) == 0) {
                        
                        if (constants::TRACING) {
                            std::cout << "PLAYER DRAWS: ";
                            for (Card* c : players[0]->getHand(j)) {
                                std::cout << c->getValue() << " ";
                            }
                            std::cout << std::endl;
                        }   

                        playerDrawCnt[0] += 1;
                        p->dealCard(deck->getTop(this), j, this);
                    }
                    
                    if (constants::TRACING) {
                        std::cout << "PLAYER STOOD: ";
                        for (Card* c : players[0]->getHand(j)) {
                            std::cout << c->getValue() << " ";
                        }
                        std::cout << std::endl;
                    }
                
                }
            }
        }
        // Dealer flips over second card
        visibleCards.push_back(dealer.getCard(1));

        if (constants::LOGGING) {
            std::cout << "Dealer decision" << std::endl;
        }
        // Make decision ends when dealer busts or decides to stand
        bool dealerMustDecide = false;
        for (Player *p : players) {
            for (int k = 0; k < p->getNumHands(); k++) {
                if (p->isSettled(k) == false) {
                    dealerMustDecide = true;
                }
            }
        }

        if (dealerMustDecide == true) { 
        /////
        while (dealer.makeDecision() == 0) {
            if (constants::TRACING) {
                std::cout << "DEALER DRAWS: ";
                for (Card* c : dealer.getHand()) {
                    std::cout << c->getValue() << " ";
                }
                std::cout << std::endl;
            }
            
            Card* c = deck->getTop(this);
            dealer.dealCard(c);
            visibleCards.push_back(c);
        }

        if (constants::TRACING) {
            std::cout << "DEALER STOOD: ";
            for (Card* c : dealer.getHand()) {
                std::cout << c->getValue() << " ";
            }
            std::cout << std::endl;
        }

        //////
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

        if (constants::TRACING) {
            std::cout << "END Hand: " << i << std::endl;
            std::cout << "-------------------------" << std::endl;
        }

        if ((double(deck->getUsedCardCount())/(deck->getCardCount())) >= 0.95) {
            if (constants::LOGGING) {
                std::cout << "SHUFFLING DECK AGAIN" << std::endl;
            }
            deck->shuffle();
            deck->burnCard(this);
            totalSeenCards = 0;
            pointCount = 0;
            shuffleCnt +=1;
        }

        
    }
}

void Game::checkNaturals() {
    // If natural -> settle bet
    // NATURAL PAYS 3:2
    // Check dealer natural
    if (dealer.getScore() == 21) {
        dealerNaturalCnt += 1;
        if (constants::TRACING) {
            std::cout << "DEALER NATURAL: " << dealer.getCard(0) << " " << dealer.getCard(1) << std::endl;
        }



        for (Player *p : players) {
            if (p->isInsured() == true) {
                if (constants::TRACING) {
                    std::cout << "Player was insured" << std::endl;
                }
                p->increaseCapital(2*(p->getSideBet()));
            }

            if (p->getScore(0) == 21) {

                if (constants::TRACING) {
                    std::cout << "PLAYER NATURAL: " << players[0]->getHand(0)[0]->getValue() << " " << players[0]->getHand(0)[1]->getValue() << std::endl;
                }

                // No money changes hands
                playerTieCnt[0] += 1;
                playerNaturalCnt[0] += 1;
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

                if (constants::TRACING) {
                    std::cout << "PLAYER NATURAL: " << players[0]->getHand(0)[0]->getValue() << " " << players[0]->getHand(0)[1]->getValue() << std::endl;
                }

                // Player gets paid 3:2
                playerNaturalCnt[0] += 1;
                p->increaseCapital(0.5*(p->getBetAmount(0)));
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
            Card *dealt = deck->getTop(this);
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
            Card *dealt = deck->getTop(this);
            visibleCards.push_back(dealt);
            dealer.dealCard(dealt);
        } else {
            Card *dealt = deck->getTop(this);
            dealer.dealCard(dealt);
        }
    }

}

double Game::getHiLoIdx() {
    // std::cout << "POINT COUNT: " << double(getPointCount()) << " CARD COUNT: " << deck->getCardCount() << " " << "SEEN CARDS: " << totalSeenCards+visibleCards.size() << std::endl;
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
                break;
        }
    }
    return pointCount + cnt;
}


void Game::printPlayerStats() {
    int i = 1;
    for (Player *p : players) {
        std::cout << "--------" << std::endl;
        std::cout << "Player " << i << std::endl;
        std::cout << "$ " << p->getCapital() << std::endl;
        
        std::cout << "Hands won: " << p->getWinCnt() << std::endl;
        std::cout << "Hands lost: " << p->getLossCnt() << std::endl;
        std::cout << "Hands tied: " << playerTieCnt[0] << std::endl;
        std::cout << "Player naturals: " << playerNaturalCnt[0] << std::endl;
        std::cout << "Dealer naturals: " << dealerNaturalCnt << std::endl;
        std::cout << "Draws: " << playerDrawCnt[0] << std::endl;
        std::cout << "Busts: " << p->getBustCnt() << std::endl;
        std::cout << "Pairs split: " << p->getSplitPairCnt() << std::endl;
        std::cout << "Doubled down: " << p->getDoubleDownCnt() << std::endl;
        std::cout << "Average bet: " << double(p->getTotalInitialBets())/handsToPlay << std::endl;
        std::cout << "Max win: " << p->getMaxWin() << std::endl;
        std::cout << "Max loss: " << p->getMaxLoss() << std::endl;

        std::cout << "Shuffle count: " << shuffleCnt << std::endl;

        std::cout << "--------" << std::endl;
    }

    deck->printDeck();
    
}

int Game::getPlayerBalance(int i) {
    return players[i]->getCapital();
}

void Game::incrementShuffleCount() {
    shuffleCnt += 1;
}

void Game::setPointCount(int i) {
    pointCount = i;
}

void Game::setTotalSeenCards(int i) {
    totalSeenCards = 0;
}