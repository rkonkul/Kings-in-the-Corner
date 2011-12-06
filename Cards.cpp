/*
    Card.cpp
    CS 340
    Project 1: Kings in the Corner
    Ryan Konkul 671462664 rkonku2
*/

#include "stdafx.h"
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>

using namespace std;

int convert_rank_to_int(char c) {
    if(c == 'A') return 1;
    else if(c > '1' && c <='9') return (int) c - 48;
    else if(c == 'T') return 10;
    else if(c == 'J') return 11;
    else if(c == 'Q') return 12;
    else if(c == 'K') return 13;
    else return -1;
}

Card::Card(char r, char s) {
    rank = r;
    suit = s;
    if(r == 'a') rank = 'A';
    else if(r == 't') rank = 'T';
    else if(r == 'j') rank = 'J';
    else if(r == 'q') rank = 'Q';
    else if(r == 'k') rank = 'K';
    if(s == 'c') suit = 'C';
    else if(s == 'd') suit = 'D';
    else if(s == 'h') suit = 'H';
    else if(s == 's') suit = 'S';
    if(r != 'A'&& r != '2'&& r != '3'&& r != '4'&& r != '5'&& r != '6'&& r != '7'&& r != '8'&&
       r != '9'&& r != 'T'&& r != 'J'&& r != 'Q'&& r != 'K'&& r != 'a'&& r != 't'&& r != 'j'&&
       r != 'q'&& r != 'k') {
           std::cout << "\nInvalid rank: " << r << std::endl;
           r = '0';
           s = '0';
    }
    if(s != 'C'&& s != 'D'&& s != 'H'&& s != 'S'&& s != 'd'&& s != 'h'&& s != 's'&& s != 'c') {
        cout << "\nInvalid suit: " << s << endl;
        r = '0';
        s = '0';
    }
}
Card::Card(int r, int s) {
    if(r==1) rank = 'A';
    else if(r==10) rank = 'T';
    else if(r==11) rank = 'J';
    else if(r==12) rank = 'Q';
    else if(r==13) rank = 'K';
    else if(r > 1 && r < 10) rank = (char) r + 48; //convert int to char
    else {
        cout << "Bad rank: " << r;
        r = '0';
    }
    if(s==1) suit = 'C';
    else if(s==2) suit = 'D';
    else if(s==3) suit = 'H';
    else if(s==4) suit = 'S';
    else {
        cout << "Bad suit: " << s;
        s = '0';
    }
}
Card::Card() {
    rank = 'A';
    suit = 'C';
}
char Card::get_rank() const {
    return rank;
}
int Card::get_int_rank() const {
    if(rank == 'A') return 1;
    else if(rank > '1' && rank <= '9') return rank-48;
    else if(rank == 'T') return 10;
    else if(rank == 'J') return 11;
    else if(rank == 'Q') return 12;
    else if(rank == 'K') return 13;
    else return -1;
}
char Card::get_suit() const {
    return suit;
}
bool Card::is_valid_move(Card c2) {
    if((get_int_rank()-1) == c2.get_int_rank()) {
        if(is_black() && c2.is_red()) {
            return true;
        }
        else if(is_red() && c2.is_black())
            return true;
    }
   return false;
}
bool operator<(Card c1, Card c2) {
    return convert_rank_to_int(c1.get_rank()) < convert_rank_to_int(c2.get_rank());
}
bool operator>(Card c1, Card c2) {
    return convert_rank_to_int(c1.get_rank()) > convert_rank_to_int(c2.get_rank());
}
bool operator==(Card c1, Card c2) {
    return (c1.get_rank() == c2.get_rank() && c1.get_suit() == c2.get_suit());
}
bool Card::is_red() const {
    if(suit == 'D' || suit == 'H') return true;
    else return false;
}
bool Card::is_black() const {
    if(suit == 'S' || suit == 'C') return true;
    else return false;
}
CardPile::CardPile(vector<Card> c) {
    cards = c;
}
CardPile::CardPile() {
    vector<Card> c;
    cards = c;
}
void CardPile::add_card(Card c) {
    cards.push_back(c);
}
Card CardPile::get_card(int i) const {
    return cards[i];
}
Card CardPile::get_top_card() const {
    return cards[cards.size()-1];
}
Card CardPile::get_bottom_card() const {
    return cards[0];
}
void CardPile::clear() {
    cards.clear();
}
bool CardPile::remove_card(Card c) {
    for(vector<Card>::size_type i=0; i<cards.size(); i++) {
        if(cards[i] == c) {
            cards.erase(cards.begin()+i,cards.begin()+i+1); 
            return true;
        }
    }
    return false;
}
void CardPile::print_pile() const {
    cout << "\n";
    for(vector<Card>::size_type i=0; i<cards.size(); i++) {
        cout << cards[i].get_rank() << cards[i].get_suit() << " ";
    }
    cout << "\n";
}
void CardPile::shuffle() {
    srand((unsigned)time(NULL));
    random_shuffle(cards.begin(), cards.end());
}
int CardPile::size() const {
    return cards.size();
}
bool CardPile::contains(Card c) const {
    for(vector<Card>::size_type i=0; i<cards.size(); i++) {
        if(cards[i] == c) return true;
    }
    return false;
}
void CardPile::add_pile(CardPile &p) {
    for(int i=0; i<p.size(); i++) {
        cards.push_back(p.get_card(i));
    }
    p.clear();
}

