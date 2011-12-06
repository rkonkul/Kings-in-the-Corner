/*
    Round.cpp
    CS 340
    Project 1: Kings in the Corner
    Ryan Konkul 671462664 rkonku2
*/

#include "stdafx.h"
#include "Round.h"
#include <iostream>
#include <vector>

using namespace std;

Round::Round(Player &p1, Player &p2) {
    draw_pile.Deal(p1, p2);
    for(int i=0; i<4; i++) {
        Card temp = draw_pile.get_top_card();
        layout_piles.Add_Card(i, temp);
        draw_pile.remove_card(temp);
    }
}
void Round::print_state(const Player &p1, const Player &p2) const {
    layout_piles.print_layout_piles();
    cout << "\nComputer: " << p2.get_points() << " points";
    p2.print_pile();
    cout << "\nPlayer: " << p1.get_points() << " points";
    p1.print_pile();
    cout << "\nDeck: ";
    draw_pile.print_pile();
}
bool Round::is_draw_pile_empty() const{
    return draw_pile.size()==0;
}
bool Round::draw_from_draw_pile(Player &p) {
    if(draw_pile.size() != 0) {
        p.add_card(draw_pile.get_top_card());
        draw_pile.remove_card(draw_pile.get_top_card());
        return true;
    }
    else return false;
}
bool Round::player_has_card(const Player &p, char r, char s) {
    Card temp = Card(r, s);
    return p.contains(temp);
}
bool Round::lay_card(Player &p, int &pile, Card c) {
    if(!layout_piles.Add_Card(pile, c)) {
        return false;
    }
    p.remove_card(c);
    return true;
}
bool Round::lay_card_no_empty(Player &p, int &pile, Card c) {
    if(!layout_piles.Add_Card_no_empty(pile, c)) {
        return false;
    }
    p.remove_card(c);
    return true;
}
bool Round::move_pile(int pile1, int pile2) {
    return layout_piles.move_pile(pile1, pile2);
}
void Round::computer_turn(Player &computer) {
 /*1  Lay down all kings in the computer player's hand onto an empty pile 5 through 8. 
    If a king exists in a player's hand, at least one of the piles 5 through 8 will be empty.
    Also check if there is a King at the bottom of piles 1 through 4. If so, move this pile 
    to an empty pile 5 though 8.
   2 If a pile can be moved onto of another pile, do so. If successful, repeat.
   3 Lay down a card on top of any non-empty pile. If successful, goto step 2.
   4 Lay down a card on top of any empty pile 1 through 4. If successful, goto step 2.
   5 If the computer player has not layed down all cards in its hand, draw a card from 
    the draw pile and end the computer player's turn. */
    while(ai_step1(computer));
    bool goto_step2 = true;
    while(goto_step2) {
        if(ai_step2(computer)) continue;
        if(ai_step3(computer)) continue;
        if(ai_step4(computer)) continue;
        goto_step2 = false;
    }
    //step 5
    if(draw_pile.size() > 0 && computer.size() != 0)
        draw_from_draw_pile(computer);
}
bool Round::ai_step1(Player &computer) {
    cout << "step 1 ";
    vector<int> empty_piles;
    for(int i=4; i<8; i++) { //first check if computer has any Kings to place
        if(layout_piles.size(i)==0) empty_piles.push_back(i);
    }
    for(int i=0; i<computer.size(); i++) {
        if(computer.get_card(i).get_rank() == 'K') {
            cout << "\nComputer places a King on pile " << empty_piles[0]+1 << "\n";
            layout_piles.Add_Card(empty_piles[0], computer.get_card(i));
            computer.remove_card(computer.get_card(i));
            return true;
        }
    } 
    vector<int> empty_piles2;  
    for(int i=4; i<8; i++) { //Then move Kings in piles 1-4 to corners
        if(layout_piles.size(i)==0) empty_piles2.push_back(i);
    }
    for(int i=0; i<4; i++) {
        if(layout_piles.size(i) > 0 && layout_piles.get_pile(i).get_bottom_card().get_rank() == 'K') {
            layout_piles.move_pile(i, empty_piles2[0]);
            cout << "\nComputer moved a King from pile " << i+1 << " to pile " << empty_piles2[0]+1 << "\n";
            return true;
        }
    } 
    return false;
}
bool Round::ai_step2(Player &computer) {
    cout << "step 2 ";
    for(int i=0; i<4; i++) { //step 2
        for(int j=0; j<8; j++) {
            if(layout_piles.get_pile(j).size() != 0) { //dont move a pile to an empty pile
                if(layout_piles.move_pile(i, j)) { //human may want to but don't have computer do it.
                    cout << "\nComputer moves pile " << i+1 << " to pile " << j+1 << "\n";    
                    return true;
                }
            }
        }
    }
    return false;
}
bool Round::ai_step3(Player &computer) {
    cout << "step 3 ";
    for(int i=0; i<8; i++) { //step 3 
        for(int j=0; j<computer.size(); j++ ) {
            if(lay_card_no_empty(computer, i, computer.get_card(j))) {
                cout << "\nComputer lays a card to non-empty pile " << i+1 << "\n";
                return true; 
            }
        }
    }
    return false;
}
bool Round::ai_step4(Player &computer) {
    cout << "step 4 ";
    vector<int> empty_piles;
    for(int i=0; i<4; i++) { //step 4
        if(layout_piles.size(i)==0) empty_piles.push_back(i);
    }
    if(empty_piles.size() != 0 && computer.size() != 0) {
        lay_card(computer, empty_piles[0], computer.get_top_card());
        cout << "\nComputer lays a card onto empty pile " << empty_piles[0]+1 << "\n";
        return true;
    }
    return false;
}
void Round::reset(Player &p1, Player &p2) {
    for(int i=0; i<p1.size(); i++) {
        if(p1.get_card(i).get_rank() == 'K') {
            p1.add_points(10);
        }
        else 
            p1.add_points(1);
    }
    for(int i=0; i<p2.size(); i++) {
        if(p2.get_card(i).get_rank() == 'K') {
            p2.add_points(10);
        }
        else 
            p2.add_points(1);
    }
    p1.clear();
    p2.clear();
    draw_pile.reset();
    for(int i=0; i<8; i++) {
        layout_piles.clear();
    }
    draw_pile.Deal(p1, p2);
    for(int i=0; i<4; i++) {
        Card temp = draw_pile.get_top_card();
        layout_piles.Add_Card(i, temp);
        draw_pile.remove_card(temp);
    } 
}

