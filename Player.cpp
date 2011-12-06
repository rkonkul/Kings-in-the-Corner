/*
    Player.cpp
    CS 340
    Project 1: Kings in the Corner
    Ryan Konkul 671462664 rkonku2
*/

#include "stdafx.h"
#include <algorithm>

Player::Player() { 
    penalty_points = 0; 
}
void Player::player_sort() {
    std::sort(cards.begin(), cards.end());
}
void Player::add_points(int p) {
    penalty_points += p;
}
int Player::get_points() const {
    return penalty_points;
}

