Project 1: Kings in the Corner
CS 340
Ryan Konkul 
rkonku2

To compile and run the program, enter commands

make -f KingsMake Kings_in_the_Corner
./Kings_in_the_Corner

Game Description:
http://www.pagat.com/domino/kingscorners.html

Usage: Upon beginning the program, the player may execute 
one of the following commands:
Q : quits the program
H : displays a help file
A : displays the about file
D : draws a card from the draw pile and ends player's turn
L <Rank><Suit> <Pile> : lays a card onto a given pile. 
Displays an error message if player does not have the 
given card or invalid move
M <Pile1> <Pile2> : moves pile1 onto pile2 if valid move

Comments:
I took an object oriented approach at this project. I 
kept function and method descriptions in the header 
files to allow quick scanning and reuse of the 
classes. During gameplay Round::print_state() prints 
the player's hand as well as the computer's and the 
drawpile for debugging. When the computer executes 
it's turn, statements are printed for what step the 
computer is in and what move it had made.  
 