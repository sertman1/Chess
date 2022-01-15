#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"

using std::cout;
using std::endl;
using std::stringstream;

namespace Chess
{
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  /* Copy constructor
   */
  Board:: Board(const Board& rhs) {
 
    board rhs_map = rhs.get_map();   // get the map of the board to copy
    for (board_itr it = rhs_map.begin(); it != rhs_map.end(); it++) {// iterate through map
      add_piece(it->first, it->second->to_ascii());
    }
  }

  /* Destructor
   */
  Board::~Board() {

    for (board_itr it = occ.begin(); it != occ.end(); it++) {  // iterate through map
      delete it->second;    // delete the piece
    }
    occ.clear();
  }

  /* Overloaded assignment operator
   */
  Board& Board::operator=(const Board& rhs) {

    for (board_itr it = occ.begin(); it != occ.end(); it++) {  // iterate through map
      delete it->second;    // delete the piece
    }
    occ.clear();
    
    board rhs_map = rhs.get_map();   // get the map of the board to copy
    for (board_itr it = rhs_map.begin(); it != rhs_map.end(); it++) { // iterate through map
      add_piece(it->first, it->second->to_ascii());
    }
    return *this;
  }
  
  /* Overloaded () operator for accessing pieces on the board
   */
  const Piece* Board::operator()(const Position& position) const {

    try {
      return occ.at(position);
    }
    catch (std::out_of_range& e) {
      return nullptr;
    }
  }

  /* Function for adding a piece to the board
   */
  void Board::add_piece(const Position& position, const char& piece_designator) {  

    bool valid_add = true;     // initialize logic check variable

    /*
    std::string valid_pieces = "KkQqBbRrNnPpMm";     // string of valid piece chars
    bool piece_is_valid = false;
    for (int i=0; i < 12; i++) {           
      if (valid_pieces[i] == piece_designator) {
	piece_is_valid = true;  // true if piece designator matches one of the valid chars 
      }
    }
    if (piece_is_valid) {
    */
  
    if ( !((piece_designator >= 'A' && piece_designator <= 'Z') || (piece_designator >= 'a'
         && piece_designator <= 'z')) ) {   // check if piece designator is a real piece
      throw Exception("Could not add piece: invalid piece designator");
      valid_add = false;
    }

    char col = position.first;     // initialize row and column
    char row = position.second;   // check if position is within board dimensions
    if ( !((row >= '1' && row <= '8') && (col >= 'A' && col <= 'H')) ) {
      throw Exception("Could not add piece: invalid position");
      valid_add = false;
    }  				  
    
    if (occ.count(position) == 1) {     // check if position is already taken 
      throw Exception("Could not add piece: position is occupied");
      valid_add = false;
    }
    
    if (valid_add) {      // add piece to board
      occ[position] = create_piece(piece_designator);
    }
  }

  /* Function for finding a piece on the board
   */
  const Position* Board::search(const char& piece_designator) const {

    for (board_citr it = occ.cbegin(); it != occ.cend(); it++) {  // iterate through map
      if (piece_designator == it->second->to_ascii()) {  // compare piece designators   
	return &(it->first);  
      }
    }
    return nullptr;
  }
 
  /* Moves a piece from given start position to end position
   */
  void Board::move_piece(const Position& start, const Position& end) {

    board_itr start_itr = occ.find(start);   // get iterator to start position
    board_itr end_itr = occ.find(end);   // get iterator to start position
    char piece_designator = start_itr->second->to_ascii();    // store piece type

    occ.erase(start_itr);         // remove piece from start position
    if (end_itr->second == nullptr) {
      occ.erase(end_itr);
    }
    add_piece(end, piece_designator);   // add piece to end position
  }
  
  /* Function to print custom colored board
   */
  void Board::display() const {

    stringstream board_state;   // get all of the characters representing the current game
    board_state << *this;

    char row_marker = '8';       // initialize variables
    bool square_color = true;
    char current_piece;
    
    for (int i = 0; i < 8; i++) {    // loop 8 rows

      Terminal::set_default();
      cout << " " << row_marker << " ";       // print row number along left side of board
      row_marker--;

      square_color = !square_color;   // switch the board color for the next row
      
      for (int j = 0; j < 8; j++) {                 // loop 8 columns

	if (square_color) {                         // set board color for current square
	  Terminal::color_bg(Terminal::RED);
	}
	else {
	  Terminal::color_bg(Terminal::BLUE);
	}

	board_state >> current_piece;    // get the next piece
	if (current_piece == '-') {      // for empty squares 
	  cout << "   ";
	}
	else {                           // for squares with pieces
	  if (current_piece >= 'A' && current_piece <= 'Z') {   // for white pieces
	    Terminal::color_fg(false, Terminal::WHITE);
	  }
	  else {      // for black pieces
	    Terminal::color_fg(false, Terminal::BLACK);
	  }
	  cout << " " << current_piece << " ";  
	}

	square_color = !square_color;   // switch the board color for the next square
      }
      Terminal::set_default();
      cout << endl;    // move on to next row
    }
	
    Terminal::set_default();
    cout << "    A  B  C  D  E  F  G  H " << endl;// print column letters at bottom of board
    
  }

  /* Function to check if current board state contains both kings
   * - Returns true if both kings present
   * - Returns false if king missing
   */
  bool Board::has_valid_kings() const {

    int white_kings = 0;     // initializing counter variables  
    int black_kings = 0;        
    
    for (board_citr it =  occ.cbegin(); it != occ.cend(); it++) {  // iterating through map
      if (it->second->to_ascii() == 'K') {         // check for white king
	white_kings++;                  
      }
      else if (it->second->to_ascii() == 'k') {    // check for black king
	black_kings++;
      }
    }
    if (white_kings == 1 && black_kings == 1) {    // check king count
      return true;
    }
    else {
      return false;
    }
  }
  
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
	const Piece* piece = board(Position(c, r));
	if (piece) {
	  os << piece->to_ascii();
	} else {
	  os << '-';
	}
      }
      os << std::endl;
    }
    return os;
  }
  
  
} // END_FILE
