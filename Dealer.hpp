// Dealer.hpp

#ifndef DEALER_HPP
#define DEALER_HPP

#include <vector>
#include "Card.hpp"

class Dealer
{
public:
    int makeDecision();
    void dealCard(Card *c);
    int getUpCard();
    int getScore();

    Card* getCard(int i);
private:
    std::vector<Card*> cards;
};



#endif