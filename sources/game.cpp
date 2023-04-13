// #pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "game.hpp"
#include "player.hpp"
#include "card.hpp"

using namespace std;

namespace ariel{
Game::Game(Player& A, Player& B): playerA(A), playerB(B)
{
    // if(this->playerA == NULL || !this->playerB) throw invalid_argument("one of the players entered are invalid");
    if(this->playerA.playing_game || this->playerB.playing_game) 
        throw invalid_argument("one of the players are currently playing in another game");
    if(&(this->playerA) == &(this->playerB)) throw invalid_argument("same player entered twice");; 
    this->current_turn = 25;
    this->winner = 0;
    // this->game_over = 0;
    // this->all_cards = {0};
    this->flipped = 0;

    this->playerA.playing_game = true;
    this->playerB.playing_game = true;

    this->dealCards();
}

void Game::dealCards()
{
    int counter = 0;
    int range_v = 13 + 1;
    int range_s = 4 + 1;
    int i = 0;
    Suit s;
    Value v;
    while (counter < 26)
    {
        int num_v = rand() % range_v;
        int num_s = rand() % range_s;
        if(this->all_cards[num_v+num_s-2] == 0)
        {
            this->all_cards[num_v+num_s] = 1;
            s = static_cast<Suit>(num_s);
            v = static_cast<Value>(num_v);
            Card c(s, v);
            this->playerA.cards_left[i++] = c;
            counter++;
        }
    }
    int j = 0;
    for(int i = 0 ; i< 52; i++)
    {
        // int num_v = rand() % range_v;
        // int num_s = rand() % range_s;
        if(this->all_cards[i] == 0)
        {
            this->all_cards[i] = 1;
            s = static_cast<Suit>((i%4)+1);
            v = static_cast<Value>((i/4)+1);
            Card c(s, v);
            this->playerB.cards_left[j++] = c;
        }
    }
}

void Game::playTurn()
{
    int start_index = this->current_turn;
    int flag = 0; 
    int count_winnings = 0;
    while(flag == 0)
    {
        if(this->current_turn < 0)
        {
            if(this->flipped)
            {
                int left = 52-(this->playerA.num_of_cards_won + this->playerB.num_of_cards_won);
                this->playerA.num_of_cards_won += left/2;
                this->playerB.num_of_cards_won += left/2;
            }
            if(this->playerA.num_of_cards_won > this->playerB.num_of_cards_won) this->winner = 1;
            else if(this->playerA.num_of_cards_won < this->playerB.num_of_cards_won) this->winner = 2;
            else this->winner = 3;

            return;
        }
        if(this->playerA.cards_left[this->current_turn].get_val() < this->playerB.cards_left[this->current_turn].get_val())
        {
            this->printLast = playerA.name + " played " + (playerA.cards_left[this->current_turn]).convertCard() + 
                              playerB.name + " played " + (playerB.cards_left[this->current_turn]).convertCard() + ". " + playerB.name + " wins.";
            // this->playerB->cards_won[this->playerB->index_card_won] = this->playerA->cards_left[this->current_turn];
            this->playerB.num_of_cards_won += count_winnings + 1;
            this->flipped = false;
            count_winnings = 0;
            flag = 1;
        }
        else if(this->playerA.cards_left[this->current_turn].get_val() > this->playerB.cards_left[this->current_turn].get_val())
        {
            this->printLast = playerA.name + " played " + (playerA.cards_left[this->current_turn]).convertCard() + 
                              playerB.name + " played " + (playerB.cards_left[this->current_turn]).convertCard() + ". " + playerA.name + " wins.";
            // this->playerA->cards_won[this->playerA->index_card_won] = this->playerB->cards_left[this->current_turn];
            this->playerA.num_of_cards_won += count_winnings + 1;
            this->flipped = false;
            count_winnings = 0;
            flag = 1;
        }
        else //if(this->playerA->cards_left[this->current_turn] == this->playerB->cards_left[this->current_turn])
        {
            this->printLast = playerA.name + " played " + (playerA.cards_left[this->current_turn]).convertCard() + 
                              playerB.name + " played " + (playerB.cards_left[this->current_turn]).convertCard() + ". Draw.";
            this->current_turn += 2;
            this->flipped = true;
            count_winnings += 1;
        }
    }
    this->playerA.num_of_cards_left = this->current_turn + 1;
    this->playerB.num_of_cards_left = this->current_turn + 1;
}

void Game::printLastTurn()
{
    cout << this->printLast << endl;
}

void Game::playAll()
{
    while(this->current_turn >= 0)
    {
        this->playTurn();
        this->printL += printLast + "\n";
    }
}

void Game::printWiner()
{
    if(this->winner == 0)
    {
        cout << "the game is not over yet" << endl;
        return;
    }
    else if(this->winner == 1){cout << this->playerA.name << endl;}
    else if(this->winner == 2){cout << this->playerB.name << endl;}
    else{cout << "a draw" << endl;}
}

void Game::printLog()
{
    cout << this->printL << endl;
}

void Game::printStats()
{
    cout << this->printStatA << endl;
    cout << this->printStatB << endl;
}
}