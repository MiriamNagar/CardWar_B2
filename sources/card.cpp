// #pragma once
#include "card.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace ariel;

Card::Card(Suit suit, Value value)
{
    this->suit = suit;
    this->value = value;
}

string ret;

string Card::convertCard()
{
    // string ret;
    if(this->value > 10) ret =Card::convert_value_enum[this->value-1];
    else ret = std::to_string(this->value) + " of ";
    ret = Card::convert_suit_enum[this->suit-1];
    return ret;
}
