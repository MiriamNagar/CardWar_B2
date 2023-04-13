#pragma once
#include <list>
#include <string>
#include "player.hpp"
#include "card.hpp"
#include <iostream>
#include <cstdlib>

using namespace std;

namespace ariel
{
    class Game
    {
        private:
            Player* playerA;
            Player* playerB;
            int current_turn;
            int all_cards[52] = {0};
            int winner; // 1- player 1, 2- player 2, 0- none, 3- draw
            // int game_over; //0- not over, 1- over
            string printL;
            string printStatA;
            string printStatB;
            string printLast;
            bool flipped;


        public:
            Game(Player& nameA, Player& nameB);
            void dealCards();
            void playTurn();
            void printLastTurn();
            void playAll();
            void printWiner();
            void printLog();
            void printStats();

    };
}