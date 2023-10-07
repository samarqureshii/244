//
//  playMove.cpp
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
//  ECE244 Student: write your code for playMove in this file

#include "GameState.h"
#include "globals.h"

// Function prototypes (if you need)

void playMove(GameState& game_state) {
  // Change turn if move is valid,
  // Change gameOver
  // Change winner

  if(game_state.get_moveValid()){ //change turn if move is valid

    if (game_state.get_turn()){ //if turn is true, set to false
      game_state.set_turn(false);
    }

    else{
      game_state.set_turn(true);
    }

  }

  int winner = Empty;

  int directions[4][2] = {{1, 0}, //vertical x = 0, y = col
                          {0,1}, //horizontal y = 0, x = row
                          {1,1}, // diagonal y = x
                          {1,-1}}; //diagonal y = -x
  

  for(int i = 0; i <=6; i++){ //going through each of the rows
    for(int j = 0; j <=6; j++){ //going through each of the columns
      int curr = game_state.get_gameBoard(i,j);
      if(curr!=Empty){ //still in the bounds of the board

        for(int d = 0; d < 4; d++){ 
          //temp row and col to check a single direction without modifying the value of i or j
          int row = i;
          int col = j;
          int count = 0; //how many are in a row 

          //keep going in that direction until we hit edge of board, 
          //until we reach a piece of the opposite colour, 
          //or until we hit 4 in a row 

          while(row >=0 && row <=6 && col >=0 && col <=6 //are we still within the board for THIS check?
                && curr == game_state.get_gameBoard(row,col)){ //is the next consecutive piece in this direction the same colour?
            count++; //guarantees two or more of the SAME pieces in a row in any given direction
            row+=directions[d][0];
            col+=directions[d][1];

            if (row < 0 || row > 6 || col < 0 || col > 6) {
              break; //last iteration case to avoid out of bounds error
            }
          }

          if(count >=4 ){ //game over!
            if(curr == R){
              winner = R;
            }
            else{ //Y won
              winner = Y;
            }
          }
        
    
        }

      }

    }

  }

  //set winner for every move, R, Y or Empty
  game_state.set_winner(winner); //set winner

  //change gameOver
  if(game_state.get_winner() != Empty){
    game_state.set_gameOver(true);
  }

}

//check if the round is over or not 
// int roundOver(GameState& game_state){ //return the winner of the game, 1 for R, -1 for Y, or Empty for the game is still going
//   int directions[4][2] = {{1, 0}, //vertical x = 0, y = col
//                           {0,1}, //horizontal y = 0, x = row
//                           {1,1}, // diagonal y = x
//                           {1,-1}}; //diagonal y = -x
  

//   for(int i = 0; i <=6; i++){ //going through each of the rows
//     for(int j = 0; j <=6; j++){ //going through each of the columns
//       int curr = game_state.get_gameBoard(i,j);
//       if(curr!=Empty){ //still in the bounds of the board

//         for(int d = 0; d < 4; d++){ 
//           //temp row and col to check a single direction without modifying the value of i or j
//           int row = i;
//           int col = j;
//           int count = 1; //how many are in a row 

//           //keep going in that direction until we hit edge of board, 
//           //until we reach a piece of the opposite colour, 
//           //or until we hit 4 in a row 

//           while(row >=0 && row <=6 && col >=0 && col <=6 //are we still within the board for THIS check?
//                 && curr == game_state.get_gameBoard(row,col)){ //is the next consecutive piece in this direction the same colour?
//             count++; //guarantees two or more of the SAME pieces in a row in any given direction
//             row+=directions[d][0];
//             col+=directions[d][1];

//             if (row < 0 || row > 6 || col < 0 || col > 6) {
//               break; //last iteration case to avoid out of bounds error
//             }
//           }

//           if(count >=4 ){ //game over!
//             if(curr == R){
//               return R;
//             }
//             else{ //Y won
//               return Y;
//             }
//           }
        
    
//         }

//       }

//     }

//   }

//   return Empty; //game is still going, nobody has reached 4 consecutive pieces

// }