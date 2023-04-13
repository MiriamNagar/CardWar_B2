#pragma once
#include <string>
using namespace std;

namespace ariel{

enum Suit : unsigned char
{
    hearts = 1,
    clubs,
    diamonds,
    spades
};

enum Value : unsigned char
{
    ace = 1,
    two,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king   
};

class Card
{
public:
    Card(){}
    Card(Suit suit, Value value);
    int get_val(){return this->value;}
    int get_suit(){return this->suit;}
    string convertCard();
// private:
    Suit suit;
    Value value;
    inline static const char *convert_suit_enum[] = { "hearts", "clubs", "diamonds", "spades" };
    inline static const char *convert_value_enum[] = { "ace", "two", "three", "four", "five", "six", "seven",
                                                "eight", "nine", "ten", "jack", "queen", "king" };
};
}