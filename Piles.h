/*
    Piles.h
    CS 340
    Project 1: Kings in the Corner
    Ryan Konkul 671462664 rkonku2
*/

#ifndef PILES_H
#define PILES_H

#include "stdafx.h"
#include <vector>

class DrawPile: public CardPile { //inherits from CardPile
    public: 
        //Constructs a 52 card deck, shuffled
        DrawPile();
        //Deals 7 cards each to 2 Players
        void Deal(Player &player1, Player &player2);
        //Resupplies and shuffles deck
        void reset();
};

class LayoutPiles { //represents layout piles
    private:
        //0-3 are center piles, 4-7 are corners
        std::vector<CardPile> layout_piles;
    public:  
        //Constructs 8 piles
        LayoutPiles();
        //Adds a card to the top of a given pile
        //Returns true if valid move
        bool Add_Card(int pile, Card c);
        //Same as Add_Card but doesn't add to empty piles
        bool Add_Card_no_empty(int pile, Card c);
        //Prints out contents of LayoutPiles
        void print_layout_piles() const;
        //Moves pile1 on top of pile2 if valid move
        bool move_pile(int pile1, int pile2);
        //Returns size of given pile
        int size(int pile) const;
        //Returns the pile specified
        CardPile get_pile(int pile);
        //Clears the piles of cards
        void clear();
};

#endif

