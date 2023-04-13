#pragma once
#include <string>
using namespace std;

namespace ariel{

class Card
{
public:
    ~Card(){}

    Card(){suit = 0 ; value = 0;}
    Card(int suit, int value);
    // Card(Card c);
    int get_val (){return value;}
    int get_suit(){return suit;}
    string convertCard();
// private:
    int suit;
    int value;
    inline static const string convert_suit_enum[] = { "hearts", "clubs", "diamonds", "spades" };
    inline static const string convert_value_enum[] = { "ace", "2", "3", "4", "5", "6", "7",
                                                "8", "9", "10", "jack", "queen", "king" };
};
}

// inline static const char *convert_value_enum[] = { "ace", "two", "three", "four", "five", "six", "seven",
//                                             "eight", "nine", "ten", "jack", "queen", "king" };