//
//  GameState.cpp
//  Connect Four Game
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Modified by Salma Emara and Ethan Hugh on 2023-09-06.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//

#include "GameState.h"
#include "globals.h"

// ECE244 Student: add you code below

//constructor
GameState::GameState(){
    selectedRow = 0;
    selectedColumn = 0;
    moveValid = true;
    gameOver = false;
    winner = Empty;

    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
            gameBoard[i][j] = Empty;
        }
    }
}

int GameState::get_selectedRow(){  // Return the selected row (in the range 0..boardSize - 1)
    return selectedRow;
}

int GameState::get_selectedColumn(){ // Return the selected column (in the range 0..boardSize - 1)
    return selectedColumn;
}

// Set the selected row to value in the range (in the range 0..boardSize - 1)
  // An out of range value is ignored and the function just returns
void GameState::set_selectedRow(int value){
    selectedRow = value;
}

// Set the selected column in the range (in the range 0..boardSize - 1)
// An out of range value is ignored and the function just returns
void GameState::set_selectedColumn(int value){
    selectedColumn = value;
}

// Get moveValid value
bool GameState:: get_moveValid(){
    return moveValid;
}

// Set the moveValid variable to value
void GameState::set_moveValid(bool value){
    moveValid = value;
}

// Get the gameOver value
bool GameState::get_gameOver(){
    return gameOver;
}

// Set the gameOver variable to value
void GameState::set_gameOver(bool value){
    gameOver = value;
}

// Get the value of turn
bool GameState::get_turn(){
    return turn;
}

// Set the value of turn
void GameState::set_turn(bool value){
    turn = value;
}

 // Get the value of winner
int GameState::get_winner(){
    return winner;
}

 // Set the value of winner;
void GameState::set_winner(int value){
    winner = value;
}

  // Get the game board value at the board location at row and col
  // This method checks that row, col and value are in range/valid
  // and if not it returns Empty
int GameState::get_gameBoard(int row, int col){
    if(row >= boardSize || col >= boardSize){
       return Empty; 
    }

    //else, row and col are valid 
    return gameBoard[row][col];
}

  // Set the game board value at the board location at row and col to value
  // This method checks that row, col and value are in range/valid and if not it
  // just returns
  void GameState::set_gameBoard(int row, int col, int value){
    if(row > 6 || row < 0 || col > 6 || col < 0){ //row and col is not valid 
        return;
    }

    gameBoard[row][col] = value;


  }

