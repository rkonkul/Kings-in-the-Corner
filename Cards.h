/*
    Cards.h
    CS 340
    Project 1: Kings in the Corner
    Ryan Konkul 671462664 rkonku2
*/

#ifndef CARDS_H
#define CARDS_H

#include "stdafx.h"
#include <vector>
#include <iostream>

//Returns an int converted from a char representing rank
int convert_rank_to_int(char c);

class Card { //class definition
    private: //data members
        char rank, suit;
    public:
        //Main Constructor
        //rank may be (A or 2-9 or T J K Q)
        //suit may be (C D H S)
        Card(char r, char s);
        //default constructor
        //Constructs card with rank A and suit C
        Card();
        //Constructs a card from ints 1-13 and 1-4
        //Converts values to construct Card
        Card(int r, int s);
        //Returns char representing rank.
        char get_rank() const; 
        //Returns int representing rank.
        int get_int_rank() const;
        //Return char representing suit.
        char get_suit() const;
        //Overloaded <operator
        friend bool operator<(Card c1, Card c2);
        //Overloaded >operator
        friend bool operator>(Card c1, Card c2);
        //Overloaded ==operator
        friend bool operator==(Card c1, Card c2);
        //Returns true if card is Red
        bool is_red() const;
        //Returns true if card is Black
        bool is_black() const;
        //Checks if second card may be placed on top of first card
        //Returns true if valid move
        bool is_valid_move(Card c2);
        //Prints out the card
        void print_card() const { std::cout << rank << suit << " "; }
};


class CardPile {
    protected:
        std::vector<Card> cards;
    public:
        //Constructs a Pile from given vector of cards.
        CardPile(std::vector<Card> c);
        //Constructs a Pile of no cards
        CardPile();
        //Adds a card on top of the Pile
        void add_card(Card c);
        //Removes a card from the pile
        //Returns true if found the card and removed it
        bool remove_card(Card c);
        //Returns the card at given index
        Card get_card(int index) const;
        //Returns the top Card of the pile
        Card get_top_card() const;
        //Returns the bottom Card of the pile
        Card get_bottom_card() const;
        //Prints out the Pile
        void print_pile() const;
        //Shuffles the Pile using STL random_shuffle()
        void shuffle();
        //Returns number of cards in Pile
        int size() const;
        //Returns true if card is in this pile
        bool contains(Card c) const;
        //Clears all the Cards from the pile
        void clear();
        //Adds a CardPile to calling object and clears parameter
        //No rules followed
        void add_pile(CardPile &p);
};

#endif

