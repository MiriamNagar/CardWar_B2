// #pragma once
#include "player.hpp"
#include <string>
#include <iostream>

using namespace std;
using namespace ariel;


Player::Player(string name)
{
    // if(!name) throw invalid_argument("Invalid name");
    this->name = name;
    this->num_of_cards_won = 0;
    // this->cards_won = {};
    this->num_of_cards_left = 26;
    // this->cards_left ;
    // this->index_card_won = 0;
    this->playing_game = false;
}

int Player::stacksize()
{
    return this->num_of_cards_left;
}

int Player::cardesTaken()
{
    return this->num_of_cards_won;
}

void Player::printCards()
{
    for(int i = 25; i >= 0 ; i++)
    {
        cout << (this->cards_left[i]).convertCard() << endl;
    }
}