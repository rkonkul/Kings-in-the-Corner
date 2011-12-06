/*
    Round.h
    CS 340
    Project 1: Kings in the Corner
    Ryan Konkul 671462664 rkonku2
*/

#ifndef ROUND_H
#define ROUND_H

#include "stdafx.h"

class Round { //represents Round state
    private:
        DrawPile draw_pile; 
        LayoutPiles layout_piles; 
    public:
        //Constructs a Round from 2 players
        Round(Player &p1, Player &p2);
        //Prints the current state of hands and piles
        void print_state(const Player &p1, const Player &p2) const;
        //Returns true if drawpile is empty
        bool is_draw_pile_empty() const;
        //Gives a player a card from the drawpile
        //Returns false if drawpile was empty
        bool draw_from_draw_pile(Player &p);
        //Returns true if given player has card described
        bool player_has_card(const Player &p, char r, char s);
        //Takes a card from the player and adds it to a given pile
        //Returns true if successful
        bool lay_card(Player &p, int &pile, Card c);
        //Same as lay_card but does not move to empty piles
        bool lay_card_no_empty(Player &p, int &pile, Card c);
        //Moves pile2 on top of pile1 if it is a valid move
        //Returns true if valid and successful
        bool move_pile(int pile1, int pile2);
        //Executes computer turn according to AI specified in project description
        void computer_turn(Player &p);
        //AI steps
        //Returns true if made a move
        bool ai_step1(Player &computer);
        bool ai_step2(Player &computer);
        bool ai_step3(Player &computer);
        bool ai_step4(Player &computer);
        //Resets roundstate and tallys points
        void reset(Player &p1, Player &p2);
};

#endif

