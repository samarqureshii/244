//
//  connectfour.cpp
//  Connect Four Game
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Modified by Salma Emara and Ethan Hugh on 2023-09-06
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <iostream>
#include <string>
using namespace std;

#include "GameState.h"
#include "globals.h"

// Function prototypes

// The main function
int main() {
  /**********************************************************************************/
  /* Create three initialized game state objects in an array */
  /**********************************************************************************/
  const int numOfRounds = 3;
  GameState game_state[numOfRounds];

  // Read one integer from the user that represents the column
  // the player would like to place their piece (R or Y) in
  // You can assume there will be no formatting errors in the input

  int col;
  int round = 0;
  int Rwins = 0;
  int Ywins = 0;
  
  std::cout << "Game " << round + 1 << std::endl;
  while (round < numOfRounds && !game_state[round].get_gameOver()) {

    std::cout << "Enter column to place piece: ";
    cin >> col;
 
    if( cin.eof() ) {
      cout << endl << "Game ended by user." << endl ;
      exit( 0 ) ;
    }
    if( cin.fail() ) {
      cin.clear() ;
      cin.ignore( 1000, '\n' ) ;
      col = -1 ; // giving col invalid value so it will be handled as invalid input below
    }
  
    // Check validity of input and if not valid, handle accordingly
      //input is not R or Y or if the column has been completly filled up, 
    while(col< 0 || col > 6 || game_state[round].get_gameBoard(6, col)!= Empty){
      std::cout << "Invalid column!" << std::endl;;
      std::cout << "Enter column to place piece: ";
      cin >> col;
    }

    // The coordinates are valid; set the selectedRow and selectedColumn
    // members of the game state to the read values
    // Note that the corresponding mutators of GameState must be first
    // implemented before this works

    //atp, col is valid so:
    game_state[round].set_selectedColumn(col);
    std::cout << "column chosen: " << col << std::endl;;

    //find the lowest available row that the piece can go into (in that row)
    for(int i = 0; i <= 6; i++){
      if(game_state[round].get_gameBoard(i, col) == Empty){ //we have found the lowest row we can place a piece in 
        game_state[round].set_selectedRow(i);

        if(game_state[round].get_turn()){ //red's turn
          game_state[round].set_gameBoard(i, col, R);
        }

        else{ //yellow's turn
          game_state[round].set_gameBoard(i, col, Y);
        }

        break;
      }
    }
    
    // Call playMove
    playMove(game_state[round]);

    // Print the GameState object, as prescribed in the handout
    for (int i = 6; i >= 0; i--) { //printing the rows
        for (int j = 0; j <= 6; j++) { //printing the columns
            if (game_state[round].get_gameBoard(i, j) == Empty) {
                std::cout << '_';
            } 
            else if (game_state[round].get_gameBoard(i, j) == R){ 
                std::cout << 'R' ;
            }

            else if (game_state[round].get_gameBoard(i, j) == Y){ 
                std::cout << 'Y' ;
            }
        }
        std::cout << '\n';
    }

    // Check if a player won this round and if so handle accordingly
    if (game_state[round].get_gameOver()) {
    char currentWinner = game_state[round].get_winner();
    if (currentWinner == R) Rwins++;
    else if (currentWinner == Y) Ywins++;

    std::cout << (currentWinner == R ? "R won this round!" : "Y won this round!") << std::endl;

    round++;

    //check every time 
    if (Rwins == 2) {
        std::cout << "R won the match!" << std::endl;
        break;  
    }
    else if (Ywins == 2) {
        std::cout << "Y won the match!" << std::endl;
        break;  
    }

    //continue to next round 
    if (round < numOfRounds) {
        game_state[round].set_turn(true); // red starts again 
        std::cout << "Game " << round + 1 << std::endl;
    }
  }

  }
}

  
