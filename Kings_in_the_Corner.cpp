/*
    Kings in the Corner.cpp
    CS 340
    Project 1: Kings in the Corner
    Ryan Konkul 671462664 rkonku2
*/

#include "stdafx.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <string>

using namespace std;

//Safely gets a line from cin
inline
void get_line(string &s) {
    cout.flush();
    if (cin.peek() == '\n') {
        cin.ignore();
    }
    getline(cin, s);
    return;
}

int main () {
    Player human;
    Player computer;
    Round round = Round(human, computer); //construct a round from 2 players
    string line; 
    bool done = false;
    bool computer_deals = true;
    cout << "\nComputer deals.\nPlayer goes first.\n";
    while(!done) {
        human.player_sort(); //sort the player's cards for readability
        computer.player_sort();
        round.print_state(human, computer);
        cout << "\n>";
        get_line(line); //get a line from the user
        cout << "\n";        
        if(line.at(0) == 'Q' || line.at(0) == 'q') {
            cout << "\nAre you sure you want to quit? ";
            get_line(line);
            if(line.at(0) == 'Y' || line.at(0) == 'y')
                done = true;
        }
        else if(line.at(0) == 'H' || line.at(0) == 'h') {
            cout << "\nAvailable commands:\nQ - Quit\nH - help\nA - About\nD - Draw a card and end turn\n"
                 << "L [rank][suit] [pile] - Lays a card onto a pile\nM [pile1] [pile2] - Moves pile1"
                 << " onto pile2\n";
            get_line(line); //pause to read what was printed
        }
        else if(line.at(0) == 'A' || line.at(0) == 'a') {
            cout << "\nProject 1: Kings in the Corner\nAuthor: Ryan Konkul\nCS 340\nDue Date: 9/13/11\n\n";
            get_line(line);
        }
        else if(line.at(0) == 'D' || line.at(0) == 'd') {
            if(!round.is_draw_pile_empty()) 
                round.draw_from_draw_pile(human);
            round.computer_turn(computer); //execute computer turn
            cout << "\n";
        }
        else if(line.at(0) == 'L' || line.at(0) == 'l') {
            if(line.length() < 6) cout << "Incorrect command. Type h for help\n";
            else {
                int x = line.at(2);
                int y = line.at(5)-49;
                Card c = Card(line.at(2), line.at(3));
                if(round.player_has_card(human, x, line.at(3))) {
                    if(!round.lay_card(human, y, c) || line.at(5)-49 < 0 || line.at(5)-49 > 7) {
                        cout << "Invalid laycard to pile " << line.at(5)-48 << "\n";
                    }
                }
                else cout << "Player does not have card " << c.get_rank() << c.get_suit() << "\n";
            }            
        }
        else if(line.at(0) == 'M' || line.at(0) == 'm') {
            if(line.length() < 5) 
               cout << "\nInvalid command. Type h for help";
            else if(!round.move_pile(line.at(2)-49, line.at(4)-49)) {//try to move pile
                cout << "\nInvalid move from pile " << line.at(2) << " to pile " << line.at(4);
            } //if successful, no error message
        }
        else  {
            cout << "Unknown Command\nType 'H' for help\n";
            get_line(line);
        }
        if(human.size() == 0 || computer.size() == 0) {//end round detection
            round.print_state(human, computer);
            round.reset(human, computer); //reset and deal a new round
            cout << "Round over.\nPlayer: " << human.get_points() << "\nComputer: " << computer.get_points() << "\n";
            if(human.get_points() >= 25 && computer.get_points() >= 25) {
                if(human.get_points() > computer.get_points()) {
                    cout << "Computer wins!\n";
                }
                else cout << "Human wins!\n";//if equal points, human wins
                done = true;
            }
            else if(human.get_points() >= 25) {
                cout << "Computer wins!\n";
                done = true;
            }
            else if(computer.get_points() >= 25) {
                cout << "Player wins!\n";
                done = true;
            }
            get_line(line);
            if(computer_deals && !done) computer_deals = false;
            else if(!computer_deals && !done) computer_deals = true;
            if(!computer_deals && !done) {
                round.computer_turn(computer);
                cout << "\nPlayer 'deals'\nComputer goes first.\n";
            }
            else if(!done) cout << "\nComputer deals.\nPlayer goes first.\n";
        }
    }
    return 0;
}

