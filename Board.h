#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Mystery.h"


namespace Chess
{
  class Board {
    
    /* Throughout, we will be accessing board positions using Position defined in Piece.h.
     * The assumption is that the first value is the column with values in
     * {'A','B','C','D','E','F','G','H'} (all caps)
     * and the second is the row, with values in {'1','2','3','4','5','6','7','8'}
     */
  public:

    /* typedefs for simplifying Board iterator code
     */
    typedef std::map<Position, Piece*> board;
    typedef board::iterator board_itr;
    typedef board::const_iterator board_citr;

    /* Default constructor
     */    
    Board();

    /* Copy constructor
     */
    Board(const Board& rhs);
    
    /* Destructor
     */
    ~Board();

    /* Getter method for map
     */
    board get_map() const {return occ;}
    
    /* Overloaded assignment operator
     */
    Board& operator=(const Board& rhs);
    
    /* Returns a const pointer to the piece at a prescribed location if it exists,
     * or nullptr if there is nothing there.
     */    
    const Piece* operator() (const Position& position) const;
    
    /* Attempts to add a new piece with the specified designator, at the given position.
     * Throw exception for the following cases:
     * -- the designator is invalid, throw exception with error message "invalid designator"
     * -- the specified position is not on the board, throw exception with error message 
     * "invalid position"
     * -- if the specified position is occupied, throw exception with error message 
     * "position is occupied"
     */    
    void add_piece(const Position& position, const char& piece_designator);
    
    /* Searches the board for a given piece and returns a pointer to its position if it
     * exists, or a nullptr if there is nothing there
     */
    const Position* search(const char& piece_designator) const;
    
    /* Removes a given piece from the board
     */
    void move_piece(const Position& start, const Position& end);
    
    /* Displays the board by printing it to stdout
     */    
    void display() const;
    
    /* Returns true if the board has the right number of kings on it 
     */    
    bool has_valid_kings() const;
    
  private:

    /* The sparse map storing the pieces, keyed off locations 
     */    
    std::map<Position, Piece*> occ;
    
    /* Write the board state to an output stream
     */    
    friend std::ostream& operator<< (std::ostream& os, const Board& board);

  };
}

#endif // BOARD_H
