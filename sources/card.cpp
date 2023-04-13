// #pragma once
#include "card.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace ariel;

Card::Card(int suit, int value)
{
    this->suit = suit;
    this->value = value;
}

string Card::convertCard()
{
    string ret=string(Card::convert_value_enum[this->value-1])+ " of ";
    // else ret = std::to_string(this->value) + " of ";
    ret += string(Card::convert_suit_enum[this->suit-1]);
    return ret;
}
