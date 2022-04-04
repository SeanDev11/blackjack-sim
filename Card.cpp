// Card.cpp

#include "Card.hpp"

Card::Card(int val) 
: value{val}
{}


int Card::getValue() {
    return value;
}

void Card::setValue(int val) {
    // Only to be used for aces
    value = val;
}