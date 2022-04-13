// Player.cpp

#include "Player.hpp"
// MIGHT HAVE TO PUT INTO HEADER
#include "Card.hpp"

// Player::Player() {}

void Player::placeBet(double idx) {
    betSettled[0] = false;
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
    betAmount[0] = bet;
}

int Player::makeDecision(int dealerUpCard, int hand, Deck* deck, double hiLoIdx, Game* gm) {
    // DECISION TO HIT OR STAND
    // 0 = hit, 1 = stand

    if (hand >= hands.size()) {return 1;}

    if (betSettled[hand] == true) {return 1;}

    if (standing[hand] == true) {return 1;}

    int decision = 0;
    int score = getScore(hand);

    if (score == 21) {return 1;}

    // Check for pair
    if ((cards.size() == 2) && (hands.size() < 4)) {
        if (hands[hand][0]->getValue() == hands[hand][1]->getValue()) {
            switch (hands[hand][0]->getValue()) {
                case 11:
                    if (dealerUpCard < 7) {
                        // SPLIT PAIR
                        
                        splitPair(hand, deck, gm);
                        // Draw one more card on each ace.
                        //dealCard(deck->getTop(), hand, gm);
                        //dealCard(deck->getTop(), hand+1);
                        standing[hand] = true;
                        standing[hand+1] = true;
                        return 1;
                        // ONLY FOR NON ACESreturn makeDecision(dealerUpCard, hand);

                    } else if (dealerUpCard == 7) {
                        if (hiLoIdx > -33) {
                            splitPair(hand, deck, gm);
                            // Draw one more card on each ace.
                            //dealCard(deck->getTop(), hand);
                            //dealCard(deck->getTop(), hand+1);
                            standing[hand] = true;
                            standing[hand+1] = true;
                            return 1;
                        }
                    } else if (dealerUpCard == 8) {
                        if (hiLoIdx > -24) {
                            splitPair(hand, deck, gm);
                            // Draw one more card on each ace.
                            //dealCard(deck->getTop(), hand);
                            //dealCard(deck->getTop(), hand+1);
                            standing[hand] = true;
                            standing[hand+1] = true;
                            return 1;
                        }
                    } else if (dealerUpCard == 9) {
                        if (hiLoIdx > -22) {
                            splitPair(hand, deck, gm);
                            // Draw one more card on each ace.
                            //dealCard(deck->getTop(), hand);
                            //dealCard(deck->getTop(), hand+1);
                            standing[hand] = true;
                            standing[hand+1] = true;
                            return 1;
                        }
                    } else if (dealerUpCard == 10) {
                        if (hiLoIdx > -20) {
                            splitPair(hand, deck, gm);
                            // Draw one more card on each ace.
                            ///dealCard(deck->getTop(), hand);
                            //dealCard(deck->getTop(), hand+1);
                            standing[hand] = true;
                            standing[hand+1] = true;
                            return 1;
                        }
                    } else if (dealerUpCard == 11) {
                        if (hiLoIdx > -17) {
                            splitPair(hand, deck, gm);
                            // Draw one more card on each ace.
                            //dealCard(deck->getTop(), hand);
                            //dealCard(deck->getTop(), hand+1);
                            standing[hand] = true;
                            standing[hand+1] = true;
                            return 1;
                        }
                    }
                    break;
                case 10:
                    switch (dealerUpCard) {
                        case 7:
                            if (hiLoIdx > 19) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                            break;
                        case 6:
                            if (hiLoIdx > 7) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                            break;
                        case 5:
                            if (hiLoIdx > 6) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                            break;
                        case 4:
                            if (hiLoIdx > 10) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                            break;
                        case 3:
                            if (hiLoIdx > 17) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                            break;
                        case 2:
                            if (hiLoIdx > 25) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                            break;

                        default:
                            break;
                    }
                    break;

                case 9:
                    switch (dealerUpCard) {
                        case 9:
                                if (hiLoIdx > -22) {
                                    splitPair(hand, deck, gm);
                                    return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                                }
                                break;
                        case 8:
                                if (hiLoIdx > -16) {
                                    splitPair(hand, deck, gm);
                                    return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                                }
                                break;
                        case 7:
                                if (hiLoIdx > 8) {
                                    splitPair(hand, deck, gm);
                                    return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                                }
                                break;
                        case 6:
                                if (hiLoIdx > -14) {
                                    splitPair(hand, deck, gm);
                                    return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                                }
                                break;
                        case 5:
                                if (hiLoIdx > -15) {
                                    splitPair(hand, deck, gm);
                                    return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                                }
                                break;
                        case 4:
                                if (hiLoIdx > -10) {
                                    splitPair(hand, deck, gm);
                                    return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                                }
                                break;
                        case 3:
                                if (hiLoIdx > -8) {
                                    splitPair(hand, deck, gm);
                                    return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                                }
                                break;
                        case 2:
                                if (hiLoIdx > -3) {
                                    splitPair(hand, deck, gm);
                                    return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                                }
                                break;
                        
                        default:
                            break;

                    }
                    break;
                case 8:
                    if (dealerUpCard < 10) {
                        splitPair(hand, deck, gm);
                        return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                    } else if (dealerUpCard == 10) {
                        if (hiLoIdx < 24) {
                            splitPair(hand, deck, gm);
                            return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                        }
                    } else if (dealerUpCard == 11) {
                        if (hiLoIdx > -18) {
                            splitPair(hand, deck, gm);
                            return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                        }
                    } 
                    break;
                case 7:
                    if (dealerUpCard == 2) {
                        if (hiLoIdx > -22) {
                            splitPair(hand, deck, gm);
                            return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                        }
                    } else if (dealerUpCard == 3) {
                        if (hiLoIdx > -29) {
                            splitPair(hand, deck, gm);
                            return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                        }
                    } else if (dealerUpCard == 3) {
                        if (hiLoIdx > -35) {
                            splitPair(hand, deck, gm);
                            return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                        }
                    } else if (dealerUpCard < 9) {
                        splitPair(hand, deck, gm);
                        return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                    }
                    break;
                case 6:
                    switch (dealerUpCard) {
                        case 2:
                            if (hiLoIdx > 0) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                        case 3:
                            if (hiLoIdx > -3) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                        case 4:
                            if (hiLoIdx > -8) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                        case 5:
                            if (hiLoIdx > -13) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                        case 6:
                            if (hiLoIdx > -16) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                        case 7:
                            if (hiLoIdx > -8) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                        default:
                            break;

                    }
                    break;
                case 4:
                    switch (dealerUpCard) {
                        case 3:
                            if (hiLoIdx > 18) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                        case 4:
                            if (hiLoIdx > 8) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                        case 5:
                            if (hiLoIdx > 0) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                        default:
                            break;
                    }
                    break;
                case 3:
                    if (dealerUpCard == 2) {
                        if (hiLoIdx > -21) {
                            splitPair(hand, deck, gm);
                            return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                        }
                    } else if (dealerUpCard == 3) {
                        if (hiLoIdx > -34) {
                            splitPair(hand, deck, gm);
                            return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);   
                        }
                    } else if (dealerUpCard < 8) {
                        splitPair(hand, deck, gm);
                        return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                    }
                    break;
                case 2:
                    switch (dealerUpCard) {
                        case 2:
                            if (hiLoIdx > -9) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                        case 3:
                            if (hiLoIdx > -15) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                        case 4:
                            if (hiLoIdx > -22) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                        case 5:
                            if (hiLoIdx > -30) {
                                splitPair(hand, deck, gm);
                                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                            }
                        case 6:
                            splitPair(hand, deck, gm);
                            return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                        case 7:
                            splitPair(hand, deck, gm);
                            return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
    }
    // Done checking pairs
    

    if (score > 21) {
        for (Card *c : hands[hand]) {
            if (c->getValue() == 11) {
                c->setValue(1);
                return makeDecision(dealerUpCard, hand, deck, hiLoIdx, gm);
            } else {
                return 1;
            }
        }
    } else {
        // Decide whether to double down
        // Check if soft or hard hand. Then follow table for decision making


    }


    return decision;
}


void Player::splitPair(int hand, Deck* deck, Game* gm) {
    std::vector<Card*> newHand;
    newHand.push_back(hands[hand][1]);
    // Get rid of one of the pairs cards
    hands[hand].pop_back();
    // Add new hand with one card
    hands.push_back(newHand);
    // Deal one new card on each hand
    dealCard(deck->getTop(), hand, gm);
    dealCard(deck->getTop(), hand+1, gm);
    
}


bool Player::isSettled() {
    return betSettled[0];
}

int Player::getBetAmount(int hand) {
    return betAmount[hand];
}

int Player::getScore(int hand) {
    int score = 0;
    for (Card *c : hands[hand]) {
        // Add up scores
        score += c->getValue();
    }
    return score;
}

void Player::dealCard(Card *c, int hand, Game* gm) {
    if (c->getValue() == 1) {
        c->setValue(11);
    }
    if (hands.size() == 0) {
        std::vector<Card*> h = {c};
        hands.push_back(h);
    } else {
        hands[hand].push_back(c);
    }
    gm->visibleCards.push_back(c);
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

void Player::settleBet(int hand) {
    betSettled[hand] = true;
    //betAmount = 0;
}


bool Player::isStanding(int hand) {
    return standing[hand];
}


int Player::getNumHands() {
    return hands.size();
}