/*
    Piles.cpp
    CS 340
    Project 1: Kings in the Corner
    Ryan Konkul 671462664 rkonku2
*/

#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;

DrawPile::DrawPile() {
    const int NUM_SUITS = 4;
    const int NUM_RANKS = 13;
    for(int i=1; i<=NUM_RANKS; i++) { 
        for(int j=1; j<=NUM_SUITS; j++) { 
            CardPile::add_card(Card(i,j));
        }
    }
    CardPile::shuffle();
}
void DrawPile::Deal(Player &player1, Player &player2) {
    for(int i=0; i<7; i++) { //deal 7 cards each
        player1.add_card(cards[cards.size()-1]);   
        cards.pop_back();
        player2.add_card(cards[cards.size()-1]);
        cards.pop_back();
    }
}
void DrawPile::reset() {
    clear();
    const int NUM_SUITS = 4;
    const int NUM_RANKS = 13;
    for(int i=1; i<=NUM_RANKS; i++) { 
        for(int j=1; j<=NUM_SUITS; j++) { 
            CardPile::add_card(Card(i,j));
        }
    }
    CardPile::shuffle();
}

LayoutPiles::LayoutPiles() {
    for(int i=0; i<8; i++) {
        layout_piles.push_back(CardPile());
    }
}
void LayoutPiles::print_layout_piles() const {
    cout << "\n";
    for(vector<CardPile>::size_type i=0; i<layout_piles.size(); i++) {
        cout << "Pile " << (i+1) << ": ";
        for(vector<CardPile>::size_type j=0; j<(unsigned)layout_piles[i].size(); j++) {
            layout_piles[i].get_card(j).print_card();
        }
        cout << "\n";
    }
}
bool LayoutPiles::Add_Card_no_empty(int p, Card c) {
        if(p >= 0 && p < 4) { //center piles
        if(layout_piles[p].size()==0) {
            return false;
        }
        else if(layout_piles[p].get_top_card().is_valid_move(c)) {
            layout_piles[p].add_card(c);
            return true;            
        }
    }
    else if(p >= 4 && p < 8) { //corner piles
        if(layout_piles[p].size()==0 && c.get_rank() == 'K') {
            layout_piles[p].add_card(c);
            return true;
        }
        else if(layout_piles[p].size()==0) {
            return false;
        }
        else if(layout_piles[p].get_top_card().is_valid_move(c)) {
            layout_piles[p].add_card(c);
            return true;
        }
    }
    return false;
}
bool LayoutPiles::Add_Card(int p, Card c) { 
    if(p >= 0 && p < 4) { //center piles
        if(layout_piles[p].size()==0) {//if no card there
            layout_piles[p].add_card(c);
            return true;
        }
        else if(layout_piles[p].get_top_card().is_valid_move(c)) {//if valid move onto pile
            layout_piles[p].add_card(c);
            return true;            
        }
    }
    else if(p >= 4 && p < 8) { //corner piles
        if(layout_piles[p].size()==0 && c.get_rank() == 'K') {//if adding a king to a corner pile
            layout_piles[p].add_card(c);
            return true;
        }
        else if(layout_piles[p].size()==0) {//can't add non kings to corners
            return false;
        }
        else if(layout_piles[p].get_top_card().is_valid_move(c)) {//if valid move
            layout_piles[p].add_card(c);
            return true;
        }
    }
    return false;
}
bool LayoutPiles::move_pile(int pile1, int pile2) {
    if(pile1 < 0 || pile1 > 3 || pile2 < 0 || pile2 > 7) return false;//bound checking
    if(pile1 == pile2) return false; if(layout_piles[pile1].size() == 0) return false;//checking moves that don't make sense  
    if(layout_piles[pile2].size() == 0 && (pile2 >= 0 && pile2 < 4)) {//moving a center pile around in circles
        layout_piles[pile2].add_pile(layout_piles[pile1]);
        return true;
    }
    else if(layout_piles[pile2].size() == 0 && pile2 > 3 && pile2 < 8 && layout_piles[pile1].get_bottom_card().get_rank() == 'K') {
        layout_piles[pile2].add_pile(layout_piles[pile1]); //if moving a king pile from center piles to corner
        return true;
    } 
    else if(layout_piles[pile2].size() == 0 && pile2 > 3 && pile2 < 8)  {//can't move non king card to corners 
        return false; 
    }
    else if(layout_piles[pile2].get_top_card().Card::is_valid_move(layout_piles[pile1].get_bottom_card())) {
        layout_piles[pile2].add_pile(layout_piles[pile1]); //moving pile on top of another
        return true;
    }  
    return false;
}
int LayoutPiles::size(int pile) const {
    return layout_piles[pile].size();
}
CardPile LayoutPiles::get_pile(int pile) {
    CardPile c = layout_piles[pile];
    return c;
}
void LayoutPiles::clear() {
    for(int i=0; i<(signed)layout_piles.size(); i++) {
        layout_piles[i].clear();
    }
}

