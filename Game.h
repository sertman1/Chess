#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Piece.h"
#include "Board.h"
#include "Exceptions.h"

namespace Chess
{

  class Game {
	  
  public:
    // This default constructor initializes a board with the standard
    // piece positions, and sets the state to white's turn
    Game();
    
    // Returns true if it is white's turn
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    bool turn_white() const { return is_white_turn; }
    
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    // Displays the game by printing it to stdout
    void display() const { board.display(); }
    
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    // Checks if the game is valid
    bool is_valid_game() const { return board.has_valid_kings(); }
   
    // checks if movment is straight
    bool straight(const Position& start, const Position& end);

    // Checks if movement is diagonal
    bool diagonal(const Position& start, const Position& end);

    // Cheacks if start and end pieces are same color
    bool same_color(const Position& start, const Position& end);

    // Checks to see if path is clear (true if clear, false if not)
    bool clear_path(const Position& start, const Position& end);

    // Checks if positions is within board 
    bool legal_square(const Position& pos);

    // Tries to move the piece at start to the piece at end
    // Returns true if this move would be a legal move 
    bool make_pseudomove(const Position& start, const Position& end);

    // Attempts to make a move. If successful, the move is made and
    // the turn is switched white <-> black. Otherwise, an exception is thrown
    void make_move(const Position& start, const Position& end);
   
    // Returns true if the designated player is in check
    bool in_check(const bool& white);
   
    // Returns true if the designated player has any legal moves left
    bool any_moves_left(const bool& white);

    // Returns true if the designated player is in mate
    bool in_mate(const bool& white);
    
    // Returns true if the designated player is in mate
    bool in_stalemate(const bool& white);
    
  private:
    // The board
    Board board;
    
    // Is it white's turn?
    bool is_white_turn;

    // Writes the board out to a stream
    friend std::ostream& operator<< (std::ostream& os, const Game& game);
    
    // Reads the board in from a stream
    friend std::istream& operator>> (std::istream& is, Game& game);
  };
}
#endif // GAME_H
