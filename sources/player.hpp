#pragma once
#include <string>
#include "card.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>


using namespace std;


namespace ariel{
    class Player
    {
        // private:
        public:
            static unsigned long const DECK_OF_CARDS_PLAYER_SIZE = 26;
            string name;
            int num_of_cards_won;
            int num_of_cards_left;
            vector<Card> cards_left;
            // array<Card, DECK_OF_CARDS_PLAYER_SIZE> cards_left;
            // Card* cards_left = new Card[DECK_OF_CARDS_PLAYER_SIZE];
            bool playing_game;
            // Card cards_won[26];
            // int index_card_won;
        // public:
            // Player(Player p);
            Player(string name);
            // ~Player(){delete[] cards_left;}
            int stacksize();
            int cardesTaken();
            void printCards();
    };
}
