#pragma once
#include <string>
#include "card.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

namespace ariel{
    class Player
    {
        // private:
        public:
            string name;
            int num_of_cards_won;
            int num_of_cards_left;
            Card* cards_left = new Card[26];
            bool playing_game;
            // Card cards_won[26];
            // int index_card_won;
        // public:
            Player(string name);
            ~Player(){delete[] cards_left;}
            int stacksize();
            int cardesTaken();
            void printCards();
    };
}
