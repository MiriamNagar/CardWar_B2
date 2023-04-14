// #pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "game.hpp"
#include "player.hpp"
#include "card.hpp"
#include <array>
#include <vector>

using namespace std;

namespace ariel{
Game::Game(Player& A, Player& B): playerA(A), playerB(B)
{
    // if(this->playerA == NULL || !this->playerB) throw invalid_argument("one of the players entered are invalid");
    if(this->playerA.playing_game || this->playerB.playing_game) throw invalid_argument("one of the players are currently playing in another game");
    this->current_turn = 0;
    this->winner = 0;
    this->flipped = false;
    this->amount_of_draws = 0;
    this->game_ended = false;

    this->playerA.num_of_cards_left = 26;
    this->playerB.num_of_cards_left = 26;

    this->playerA.playing_game = true;
    this->playerB.playing_game = true;

    if(&playerA != &playerB) this->dealCards();
}

void Game::dealCards()
{
    int counter = 0;
    size_t range_v = 13;
    size_t range_s = 4;
    while (counter < 26)
    {
        size_t num_v = (size_t)rand() % range_v;
        size_t num_s = (size_t)rand() % range_s;
        if(this->all_cards[((num_v)*4 + num_s)] == 0)
        {
            this->all_cards[((num_v)*4 + num_s)] = 1;
            Card c((num_s+1), (num_v+1));
            this->playerA.cards_left.push_back(c);
            counter++;
        }
    }
    // cout<< counter<< endl;
    int j = 0;
    counter = 0;
    for(size_t i = 0 ; i< 52; i++)
    {
        if(this->all_cards[i] == 0)
        {
            this->all_cards[i] = 1;
            Card c((i%4)+1, (i/4)+1);
            this->playerB.cards_left.push_back(c);
            counter++;
        }
    }
    // cout<< counter<< endl;
    for(size_t i =0 ;i< 52;i++)
    {
        this->all_cards[i] = 0;
    }
}

void Game::playTurn()
{
    if (&playerA == &playerB) throw invalid_argument("same player entered twice");
    if(game_ended) throw invalid_argument("game ended...no more turns.");
    // int start_index = this->current_turn;
    this->printLast = "";
    int flag = 0; 
    int count_winnings = 0;
    while(flag == 0)
    {
        if(this->playerA.cards_left[this->current_turn].get_val() < this->playerB.cards_left[this->current_turn].get_val())
        {
            this->printLast += playerA.name + " played " + (playerA.cards_left[this->current_turn]).convertCard() + " " +
                              playerB.name + " played " + (playerB.cards_left[this->current_turn]).convertCard() + ". " + playerB.name + " wins.";
            this->playerB.num_of_cards_won += count_winnings + 1;
            this->flipped = false;
            this->current_turn += 1;
            count_winnings = 0;
            flag = 1;
        }
        else if(this->playerA.cards_left[this->current_turn].get_val() > this->playerB.cards_left[this->current_turn].get_val())
        {
            this->printLast += playerA.name + " played " + (playerA.cards_left[this->current_turn]).convertCard() + " " +
                              playerB.name + " played " + (playerB.cards_left[this->current_turn]).convertCard() + ". " + playerA.name + " wins.";
            // this->playerA.cards_won[this->playerA.index_card_won] = this->playerB.cards_left[this->current_turn];
            // cout<< "==============================================================================="<<endl;
            this->playerA.num_of_cards_won += count_winnings + 1;
            this->flipped = false;
            this->current_turn += 1;
            count_winnings = 0;
            flag = 1;
        }
        else
        {
            this->printLast = playerA.name + " played " + (playerA.cards_left[this->current_turn]).convertCard() + " " +
                              playerB.name + " played " + (playerB.cards_left[this->current_turn]).convertCard() + ". Draw.";
            this->current_turn += 2;
            this->flipped = true;
            this->amount_of_draws += 1;
            count_winnings += 2;
            if(this->current_turn > 25){
                int left = 52-(this->playerA.num_of_cards_won + this->playerB.num_of_cards_won);
                this->playerA.num_of_cards_won += left/2;
                this->playerB.num_of_cards_won += left/2;
            }
        }
        if(this->current_turn > 25)
        {
            this->playerA.playing_game = false;
            this->playerB.playing_game = false;
            if(this->playerA.num_of_cards_won > this->playerB.num_of_cards_won) this->winner = 1;
            else if(this->playerA.num_of_cards_won < this->playerB.num_of_cards_won) this->winner = 2;
            else this->winner = 3;
            this->game_ended = true;
            flag = 1;
        }
    }
    this->playerA.num_of_cards_left = 26 - this->current_turn;
    this->playerB.num_of_cards_left = 26 - this->current_turn;
    this->printL += printLast + "\n";
}

void Game::printLastTurn()
{
    cout << this->printLast << endl;
}

void Game::playAll()
{
    while(this->current_turn < 26)
    {
        this->playTurn();
    }
    this->playerA.playing_game = false;
    this->playerB.playing_game = false;
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
    cout << this->playerA.name << " statistics: " << endl;
    cout << "    win rate: " << (double)playerA.num_of_cards_won/(this->current_turn+1) << endl;
    cout << "    cards won: " << playerA.cardesTaken() << endl;
    cout << this->playerB.name << " statistics: " << endl;
    cout << "    win rate: " << (double)playerB.num_of_cards_won/(this->current_turn +1) << endl;
    cout << "    cards won: " << playerB.cardesTaken() << endl;
    cout << "draw rate: " << (double)this->amount_of_draws/(this->current_turn+1) << endl;
    cout << "amount of draws: " << this->amount_of_draws << endl;
}
}