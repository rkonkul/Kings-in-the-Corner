/*
    Player.h
    CS 340
    Project 1: Kings in the Corner
    Ryan Konkul 671462664 rkonku2
*/

#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"

class Player : public CardPile{//inherits from CardPile
    private: //class inherits because most methods in CardPiles are unchanged for Player
        int penalty_points;
    public:
        //Constructs a Player
        Player();
        //Sorts player's cards according to rank, suit not sorted
        void player_sort(); 
        //Adds penalty points to player
        void add_points(int p);
        //Returns number of penalty points player has
        int get_points() const;
};

#endif

