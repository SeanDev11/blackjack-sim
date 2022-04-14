// Player.cpp

#include "Player.hpp"
#include "Game.hpp"


// Player::Player() {}

void Player::placeBet(double idx) {
    resetBets();
    
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

void Player::resetBets() {
    for (int i = 0; i < 4; i++) {
        betSettled[i] = false;
        betAmount[i] = 0;
        standing[i] = false;
    }
}


int Player::makeDecision(int dealerUpCard, int hand, Deck* deck, double hiLoIdx, Game* gm) {
    // DECISION TO HIT OR STAND
    // 0 = hit, 1 = stand

    if (hand >= hands.size()) {return 1;}

    if (betSettled[hand] == true) {return 1;}

    if (standing[hand] == true) {return 1;}

    int decision = 1;
    int score = getScore(hand);

    if (score == 21) {return 1;}

    // Check for pair
    if ((hands[hand].size() == 2) && (hands.size() < 4)) {
        if (hands[hand][0]->getValue() == hands[hand][1]->getValue()) {
            //std::cout << "GOT PAIR" << std::endl;
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
        if (hands[hand].size() == 2) {
            if (isHardHand(hand) == true) {
                // Hard Hand
                score = getScore(hand);
                double idx = gm->getHiLoIdx();
                switch (score) {
                    case 11:
                        switch (dealerUpCard) {
                            case 11:
                                if (idx > -3) {
                                    // DOUBLE DOWN
                                    doubleDown(hand, deck, gm);
                                    return 1; 
                                }
                                break;
                            case 10:
                                if (idx > -9) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break;
                            case 9:
                                if (idx > -10) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 8:
                                if (idx > -16) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 7:
                                if (idx > -26) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break;
                            case 6:
                                if (idx > -35) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 5:
                                if (idx > -33) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 4:
                                if (idx > -29) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 3:
                                if (idx > -26) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 2:
                                if (idx > -23) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            default:
                                break;
                        }
                    case 10:
                        switch (dealerUpCard) {
                            case 11:
                                if (idx > 6) {
                                    // DOUBLE DOWN
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break;
                            case 10:
                                if (idx > 7) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break;
                            case 9:
                                if (idx > -3) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 8:
                                if (idx > -9) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 7:
                                if (idx > -17) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break;
                            case 6:
                                if (idx > -26) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 5:
                                if (idx > -24) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 4:
                                if (idx > -21) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 3:
                                if (idx > -17) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 2:
                                if (idx > -15) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            default:
                                break;
                        }
                    case 9:
                        switch (dealerUpCard) {
                            case 8:
                                if (idx > 14) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 7:
                                if (idx > 4) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break;
                            case 6:
                                if (idx > -12) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 5:
                                if (idx > -10) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 4:
                                if (idx > -5) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 3:
                                if (idx > 0) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 2:
                                if (idx > 3) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            default:
                                break;
                        }
                    case 8:
                        switch (dealerUpCard) {
                            case 7:
                                if (idx > 22) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break;
                            case 6:
                                if (idx > 5) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 5:
                                if (idx > 5) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 4:
                                if (idx > 11) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 3:
                                if (idx > 22) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break;
                            default:
                                break;
                        }
                    case 7:
                        switch (dealerUpCard) {
                            case 6:
                                if (idx > 17) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 5:
                                if (idx > 14) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 4:
                                if (idx > 21) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 3:
                                if (idx > 45) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break;
                            default:
                                break;
                        }
                    case 6:
                        switch (dealerUpCard) {
                            case 6:
                                if (idx > 24) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 5:
                                if (idx > 18) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 4:
                                if (idx > 27) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            default:
                                break;
                        }
                    case 5:
                        switch (dealerUpCard) {
                            case 6:
                                if (idx > 26) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break; 
                            case 5:
                                if (idx > 20) {
                                    doubleDown(hand, deck, gm);
                                    return 1;
                                }
                                break;  
                            default:
                                break;
                        }
                    default:
                        break;
                }
            } else {
                // Soft Hand
                int aceIdx = -1;
                int otherIdx = 1;
                for (int i = 0; i < 2; i++) {
                    if (hands[hand][i]->getValue() == 11) {
                        aceIdx = i;
                    }
                }
                if (aceIdx == 1) {
                    otherIdx = 0;
                }
                if (aceIdx > -1) {
                    switch (hands[hand][otherIdx]->getValue()) {
                        case 9:
                            switch(dealerUpCard) {
                                case 3:
                                    if (hiLoIdx > 20) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 4:
                                    if (hiLoIdx > 12) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 5:
                                    if (hiLoIdx > 8) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 6:
                                    if (hiLoIdx > 8) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                default:
                                    break;
                            }       
                        case 8:
                            switch(dealerUpCard) {
                                case 3:
                                    if (hiLoIdx > 9) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 4:
                                    if (hiLoIdx > 5) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 5:
                                    if (hiLoIdx > 1) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 6:
                                    if (hiLoIdx > 0) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                default:
                                    break;
                            }      
                        case 7:
                            switch(dealerUpCard) {
                                case 3:
                                    if (hiLoIdx > -2) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 4:
                                    if (hiLoIdx > -15) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 5:
                                    if (hiLoIdx > -18) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 6:
                                    if (hiLoIdx > -23) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                default:
                                    break;
                            }      
                        case 6:
                            switch(dealerUpCard) {
                                case 2:
                                    if (hiLoIdx > 1) {
                                        if (hiLoIdx < 10) {
                                            doubleDown(hand, deck, gm);
                                            return 1;
                                        }
                                    }
                                    break;
                                case 3:
                                    if (hiLoIdx > -6) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 4:
                                    if (hiLoIdx > -14) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 5:
                                    if (hiLoIdx > -28) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 6:
                                    if (hiLoIdx > -30) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                default:
                                    break;
                            }      
                        case 5:
                            switch(dealerUpCard) {
                                case 3:
                                    if (hiLoIdx > 21) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 4:
                                    if (hiLoIdx > -6) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 5:
                                    if (hiLoIdx > -16) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 6:
                                    if (hiLoIdx > -32) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                default:
                                    break;
                            }      
                        case 4:
                            switch(dealerUpCard) {
                                case 3:
                                    if (hiLoIdx > 19) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 4:
                                    if (hiLoIdx > -7) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 5:
                                    if (hiLoIdx > -16) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 6:
                                    if (hiLoIdx > -23) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                default:
                                    break;
                            }      
                        case 3:
                            switch(dealerUpCard) {
                                case 3:
                                    if (hiLoIdx > 11) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 4:
                                    if (hiLoIdx > -3) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 5:
                                    if (hiLoIdx > -13) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 6:
                                    if (hiLoIdx > -19) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                default:
                                    break;
                            }      
                        case 2:
                            switch(dealerUpCard) {
                                case 3:
                                    if (hiLoIdx > 10) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 4:
                                    if (hiLoIdx > 2) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 5:
                                    if (hiLoIdx > -19) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                case 6:
                                    if (hiLoIdx > -13) {
                                        doubleDown(hand, deck, gm);
                                        return 1;
                                    }
                                    break;
                                default:
                                    break;
                            }      

                        default:
                            break;
                    }
                }
            }
        }
    }
    if (standing[hand] == true) {return 1;}
    // Done checking for doubling down
    // Decide whether to draw or stand

    if (isHardHand(hand) == true) {
        // hard hand
        score = getScore(hand);
        if (score > 17) {
            return 1;
        } else if (score == 17) {
            if (dealerUpCard == 11) {
                if (hiLoIdx > -15) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                return 1;
            }
        } else if (score == 16) {
            switch (dealerUpCard) {
                case 2:
                    if (hiLoIdx > -21) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 3:
                    if (hiLoIdx > -25) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 4:
                    if (hiLoIdx > -30) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 5:
                    if (hiLoIdx > -34) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 6:
                    if (hiLoIdx > -35) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 7:
                    if (hiLoIdx > 10) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 8:
                    if (hiLoIdx > 11) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 9:
                    if (hiLoIdx > 6) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 10:
                    if (hiLoIdx > 2) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 11:
                    if (hiLoIdx > 14) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                default:
                    break;
            }
        } else if (score == 15) {
            switch (dealerUpCard) {
                case 2:
                    if (hiLoIdx > -12) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 3:
                    if (hiLoIdx > -17) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 4:
                    if (hiLoIdx > -21) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 5:
                    if (hiLoIdx > -26) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 6:
                    if (hiLoIdx > -28) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 7:
                    if (hiLoIdx > 13) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 8:
                    if (hiLoIdx > 15) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 9:
                    if (hiLoIdx > 12) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 10:
                    if (hiLoIdx > 8) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 11:
                    if (hiLoIdx > 16) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                default:
                    break;
            }
        } else if (score == 14) {
            switch (dealerUpCard) {
                case 2:
                    if (hiLoIdx > -5) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 3:
                    if (hiLoIdx > -8) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 4:
                    if (hiLoIdx > -13) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 5:
                    if (hiLoIdx > -17) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 6:
                    if (hiLoIdx > -17) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 7:
                    if (hiLoIdx > 20) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 8:
                    if (hiLoIdx > 38) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                default:
                    return 0;
                    break;
            }
        } else if (score == 13) {
            switch (dealerUpCard) {
                case 2:
                    if (hiLoIdx > 1) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 3:
                    if (hiLoIdx > -2) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 4:
                    if (hiLoIdx > -5) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 5:
                    if (hiLoIdx > -9) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 6:
                    if (hiLoIdx > -8) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 7:
                    if (hiLoIdx > 50) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                default:
                    return 0;
                    break;
            }
        } else if (score == 12) {
            switch (dealerUpCard) {
                case 2:
                    if (hiLoIdx > -21) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 3:
                    if (hiLoIdx > -25) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 4:
                    if (hiLoIdx > -30) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 5:
                    if (hiLoIdx > -34) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 6:
                    if (hiLoIdx > -35) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 7:
                    if (hiLoIdx > 10) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 8:
                    if (hiLoIdx > 11) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 9:
                    if (hiLoIdx > 6) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 10:
                    if (hiLoIdx > 2) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 11:
                    if (hiLoIdx > 14) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                default:
                    break;
            }
        } else {
            return 0;
        }

    } else {
        // Soft hand
        score = getScore(hand);

        if (score > 18) {
            return 1;
        } else if (score == 18) {
            switch (dealerUpCard) {
                case 9:
                    return 0;
                    break;
                case 10:
                    if (hiLoIdx > 12) {
                        return 1;
                    } else {
                        return 0;
                    }
                    break;
                case 11:
                    if (hiLoIdx > -6) {
                        return 1;
                    } else {
                        return 0;
                    }
                default:
                    return 1;
                    break;
            }
        } else if (score == 17) {
            if (dealerUpCard < 7) {
                return 0;
            } else if (dealerUpCard == 7) {
                if (hiLoIdx > 29) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        } else {
            return 0;
        }


    }


    return decision;
}


void Player::splitPair(int hand, Deck* deck, Game* gm) {
    if (constants::LOGGING) {
        for (int i = 0; i < hands.size(); i++) {
                std::cout << "Hand " << i << ": ";
                for (Card* c : hands[i]) {
                    std::cout << c->getValue() << " ";
                }
                std::cout << std::endl;
        }
        std::cout << "------" << std::endl;
    }
    
    
    std::vector<Card*> newHand;
    newHand.push_back(hands[hand][1]);
    // Get rid of one of the pairs cards
    hands[hand].pop_back();
    // Add new hand with one card
    hands.push_back(newHand);
    // Deal one new card on each hand
    dealCard(deck->getTop(), hand, gm);
    dealCard(deck->getTop(), hands.size()-1, gm);

    splitPairCnt += 1;
    if (constants::LOGGING) {
        for (int i = 0; i < hands.size(); i++) {
            //
            if (hands[i].size() > 2) {
                std::cout << "AHHHHHHHHHHHHHHJHJHJHJHJHJHJHJHJHJHJHHHHHHHHHHHHHGGGGGGGGGGGGGGGGGGGGGGGGHGHHHHHGHHHHGHHHH" << std::endl;
                
                for (int i = 0; i < hands.size(); i++) {
                    std::cout << "Hand " << i << ": ";
                    for (Card* c : hands[i]) {
                        std::cout << c->getValue() << " ";
                    }
                    std::cout << std::endl;
                }
                std::cout << "------" << std::endl;
            }
            
        }
    }

    
    
    
}

void Player::doubleDown(int hand, Deck* deck, Game* gm) {
    dealCard(deck->getTop(), hand, gm);
    standing[hand] = true;
    betAmount[hand] += betAmount[hand];
    doubleDownCnt += 1;
}

bool Player::isSettled(int hand) {
    return betSettled[hand];
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
    winCnt += 1;
    capital += win;
}

void Player::decreaseCapital(int loss) {
    lossCnt += 1;
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

bool Player::isHardHand(int hand) {
    // returns true if hard, false if soft
    bool hard = true;

    for (Card *c : hands[hand]) {
        if (c->getValue() == 11) {
            if (getScore(hand) < 22) {
                return false;
            } else {
                c->setValue(1);
            }
        } else if (c->getValue() == 1) {
            c->setValue(11);
            if (getScore(hand) < 22) {
                return false;
            } else {
                c->setValue(1);
            }

        }
    }
    return hard;
}


bool Player::checkHandMakeup(int hand, int c1, int c2) {
    if (hands[hand][0]->getValue() == c1) {
        if (hands[hand][1]->getValue() == c2) {
            return true;
        } else {
            return false;
        }
    } else if (hands[hand][1]->getValue() == c1) {
        if (hands[hand][0]->getValue() == c2) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

std::vector<Card*> Player::getHand(int hand) {
    return hands[hand];
}

void Player::clearHands() {
    for (int i = 0; i < hands.size(); i++) {
        hands[i].clear();
    }
    hands.clear();
}

int Player::getDoubleDownCnt() {
    return doubleDownCnt;
}

int Player::getSplitPairCnt() {
    return splitPairCnt;
}

int Player::getWinCnt() {
    return winCnt;
}

int Player::getLossCnt() {
    return lossCnt;
}

void Player::insure(int hand) {
    insured = true;
    sideBet = 0.5*betAmount[hand];
}

bool Player::isInsured() {
    return insured;
}

int Player::getSideBet() {
    return sideBet;
}

void Player::resetInsurance() {
    insured = false;
    sideBet = 0;
}