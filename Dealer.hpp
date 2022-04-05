// Dealer.hpp

#ifndef DEALER_HPP
#define DEALER_HPP

#include <vector>

class Dealer
{
public:
    int makeDecision();
    void dealCard(Card *c);

    int getScore();
private:
    std::vector<Card*> cards;
};



#endif