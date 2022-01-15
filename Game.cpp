#include <cassert>
#include <cmath>
#include "Game.h"
namespace Chess
{
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Game::Game() : is_white_turn(true) {
    // Add the pawns
    for (int i = 0; i < 8; i++) {
      board.add_piece(Position('A' + i, '1' + 1), 'P');
      board.add_piece(Position('A' + i, '1' + 6), 'p');
    }
    
    // Add the rooks
    board.add_piece(Position( 'A'+0 , '1'+0 ) , 'R' );
    board.add_piece(Position( 'A'+7 , '1'+0 ) , 'R' );
    board.add_piece(Position( 'A'+0 , '1'+7 ) , 'r' );
    board.add_piece(Position( 'A'+7 , '1'+7 ) , 'r' );
    
    // Add the knights
    board.add_piece(Position( 'A'+1 , '1'+0 ) , 'N' );
    board.add_piece(Position( 'A'+6 , '1'+0 ) , 'N' );
    board.add_piece(Position( 'A'+1 , '1'+7 ) , 'n' );
    board.add_piece(Position( 'A'+6 , '1'+7 ) , 'n' );
    
    // Add the bishops
    board.add_piece(Position( 'A'+2 , '1'+0 ) , 'B' );
    board.add_piece(Position( 'A'+5 , '1'+0 ) , 'B' );
    board.add_piece(Position( 'A'+2 , '1'+7 ) , 'b' );
    board.add_piece(Position( 'A'+5 , '1'+7 ) , 'b' );
    
    // Add the kings and queens
    board.add_piece(Position( 'A'+3 , '1'+0 ) , 'Q' );
    board.add_piece(Position( 'A'+4 , '1'+0 ) , 'K' );
    board.add_piece(Position( 'A'+3 , '1'+7 ) , 'q' );
    board.add_piece(Position( 'A'+4 , '1'+7 ) , 'k' );
  }

  // STILL NEED TO DECLARE AND COMMENY  IN HEADER FILE:
  
  bool Game::straight(const Position& start, const Position& end) {
    if (start.first == end.first) { // check first if piece went vertical or horizontal
      if ((start.second - end.second) < 0) { // vertical, check if it went up or down
	for (int i=0; i<(end.second-start.second); i++) { // went up, check for any pieces in its way
	  if ((board(Position(start.first, start.second+i))) != nullptr) // there was a peice, so path is illegal 
	    return false;
	}
      }
      else {
	for (int i = 0; i<(start.second-end.second); i++) {
	  if ((board(Position(start.first, start.second-i))) != nullptr)
	    return false;
	}
      }
    }
    else { // horizontal, check left or right
      if ((start.first - end.first) < 0) { 
	for (int i=0; i<(end.first-start.first); i++) { // went to the right
	  if((board(Position(start.first+i, start.second))) != nullptr)
	    return false;
	}			
      }
      else {  // went to the left
	for (int i=0; i<(start.first-end.first); i++) {
	  if((board(Position(start.first-i, start.second))) != nullptr)
	    return false;
	}
      }
    }
    return true; 
  }
  
  //test function to determine if space between start end movement is empty diagonally
  bool Game::diagonal(const Position& start, const Position& end) {
    char start_col = start.first;
    char start_row = start.second;
    char end_col = end.first;
    char end_row = end.second;
    int vert_dis = std::abs(start_row - end_row);
    int hor_dis = std::abs(start_col - end_col);
    for (int col = 1; col < vert_dis; ++col) {
      for (int row = 1; row < hor_dis; ++ row) {
        if (col == row) {
          if (start_col < end_col && start_row < end_row) {
            if (board(Position(col, row)) != nullptr)
	      return false; // is a piece, so path is illegal
          }
          if (start_col < end_col && start_row > end_row) {
            if (board(Position(col, -row)) != nullptr) 
	      return false; // is a piece, so path is illegal
          }
          if (start_col > end_col && start_row < end_row) {
            if (board(Position(-col, row)) != nullptr) 
	      return false; // is a piece, so path is illegal
          }
          if (start_col > end_col && start_row > end_row) {
            if (board(Position(-col, -row)) != nullptr) 
	      return false; // is a piece, so path is illegal
          }
        }
      }
    }   
    return true;
  }

  //check to see if start and and end pieces are same color
  bool Game::same_color(const Position& start, const Position& end) {
    if ((board(start)) == nullptr || (board(end)) == nullptr) return false; // square(s) missing piece
    else {
      char start_ascii = (*(board(start))).to_ascii();
      char end_ascii  = (*(board(start))).to_ascii();
      if (start_ascii > 96 && end_ascii > 96) return true; // range for lower case (black) designators
      else if (start_ascii < 96 && end_ascii < 96) return true; 
    }  
    return false; 
  }
  
  bool Game::clear_path(const Position& start, const Position& end) {
      char designator = (*(board(start))).to_ascii();
      // next, check that no piece's path is blocked by another's (exception: knight)
      switch (designator) {  
      case 'P':
      case 'p': 
	if (start.second == end.second +1) { // see if pawn moved two or one square
        	if (board(end) == nullptr) // pawn can't be in its way 
		  return true;
		else return false;
	}
	else { 
		if (board(end) == nullptr && board(Position(start.first,start.second+1)) == nullptr)
	       	  return true;	
		else return false;
	}
      case 'R':
      case 'r':
	return straight(start, end);
      case 'N':
      case 'n':
	return true;
      case 'B':
      case 'b':
	return diagonal(start, end);
      case 'Q':
      case 'q':
	// determine whether queen went straight or diagonal
	if (start.first == end.first || start.second == end.second)
	  return straight(start, end);
	else
	  return diagonal(start, end);
      case 'K':
      case 'k': 
	return true;
      default:
	return false;
	break;
      }
    }
 
  // check if board square exists within A-H and 1-8
  bool Game::legal_square(const Position& pos) {
    char col = pos.first;
    char row = pos.second;
    if (col < 'A' || col > ('A'+7) || row < '1' || row > ('1'+7)) {
      return false;
    }
    return true;
  }
   
  void Game::make_move(const Position& start, const Position& end) {
    const Piece* cur_square = board(start);
    char designator = (*cur_square).to_ascii();
    if (!legal_square(start))
      throw Exception("start position is not on board");
    else if (!legal_square(end))
      throw Exception("end position is not on board");
    else if (cur_square == nullptr) 
      throw Exception("no piece at start position");
    else if (designator > 96 && is_white_turn)  // ascii values >96 are lower case
      throw Exception("piece color and turn do not match");
    else if (designator < 96 && !is_white_turn)	
      throw Exception("piece color and turn do not match");
    else if ((designator == 'p' || designator == 'P') && start.first != end.first) { // special capture pawn case
      if (same_color(start,end))
        throw Exception("cannot capture own piece");
      else if(!(*cur_square).legal_capture_shape(start,end) || board(Position(end)) == nullptr) // make sure there's a piece to capture
        throw Exception("illegal capture shape");
    } // not a capture pawn
    else if (!(*cur_square).legal_move_shape(start,end))
      throw Exception("illegal move shape");
    else if ((board(Position(end))) != nullptr && same_color(start, end))
      throw Exception("cannot capture own piece");   
    else if ((board(Position(end))) != nullptr && !(*cur_square).legal_capture_shape(start,end))
      throw Exception("illegal capture shape");
    else if (!clear_path(start,end))
      throw Exception("path is not clear");
    else { // check if move exposes check
      Board temp_board = board;
      board.move_piece(start,end);
      if (in_check(is_white_turn)) {
        throw Exception("move exposes check");
	board = temp_board; // reset board
      }
      else {
	// switch turns
	if (is_white_turn) is_white_turn = false;
	else is_white_turn = true;
        // check for pawn promotion
	if (designator == 'P' && end.second == '1'+7) { 
	  board.add_piece(end,'Q');
	}
	else if (designator == 'p' && end.second == '1') {
      	  board.add_piece(end,'q');
	}
      }
    }
  } 

  // determines if moving piece at start to end would be legal.
  // Only ever called in any_moves_left, where start and end are
  // ensured to be legal and start has the desired color's piece on it
  bool Game::make_pseudomove(const Position& start, const Position& end) {
    const Piece* cur_square = board(start);
    char designator = (*cur_square).to_ascii();
    if ((designator == 'p' || designator == 'P') && start.first != end.first) { // special capture pawn case
      if (same_color(start,end))
        return false;
      else if(!(*cur_square).legal_capture_shape(start,end) || (board(Position(end)) == nullptr)) // make sure there's a piece to capture
        return false;
    } // not a capture pawn
    else if (!(*cur_square).legal_move_shape(start,end))
      return false;
    else if ((board(Position(end))) != nullptr && same_color(start, end))
      return false;
    else if ((board(Position(end))) != nullptr && !(*cur_square).legal_capture_shape(start,end))
      return false;
    else if (!clear_path(start,end))
      return false;
    // check if move exposes check
    Board temp_board = board;
    board.move_piece(start,end);
    if (in_check(is_white_turn)) {
      board = temp_board; // reset board
      return false;
    }
    else {
      board = temp_board;
      return true; // move can legally be made
    }
    return false;
  }

  
  bool Game::in_check(const bool& white) {
   Position kings_pos; 
   bool not_found = true;
   for (int r=0; r<8 && not_found; r++) { // loop through the board to find the kings position
      for (int c=0; c<8; c++) {
	if (board(Position('A'+r,'1'+c)) != nullptr) {      
          char des = (*(board(Position('A'+r,'1'+c)))).to_ascii();
	  if ((des == 'K' && white) || (des == 'k' && !white)) {
	    kings_pos.first = 'A'+r;
	    kings_pos.second = '1'+c;
	    not_found = false;
	    break;
          }
        }
      }
    }
    // locate all of opponent's remaining pieces and see if they put king in check
    for (int i=0; i<8; i++) {
      for (int j=0; j<8; j++) {
	Position pos('A'+i, '1'+j);
	const Piece* cur_square = board(pos);
	if (cur_square != nullptr) {
	  // check if piece belongs to opposing color
	  if ((white == true && (*cur_square).is_white() == false) || (white == false && (*cur_square).is_white() == true)) {
	    char des = (*cur_square).to_ascii();
	    // check for pawn capture exception
	    if ((des == 'p' || des == 'P') && 'A'+i != kings_pos.second && (*cur_square).legal_capture_shape(pos,kings_pos))
	      return true;
	    else if ((*cur_square).legal_capture_shape(pos,kings_pos) && clear_path(pos,kings_pos))
	      return true;
	  }
	}
      }
    }
    return false;
  }
 
  bool Game::any_moves_left(const bool& white)  {

   for (int row=0; row<8; row++) {
     for (int col=0; col<8; col++) {
       const Piece* cur = board(Position('A'+row, '1'+col));
       if (cur != nullptr && (((*cur).to_ascii() > 96 && !white) || ((*cur).to_ascii() < 96 && white))) { // make sure square has a friendly piece on it
         for (int r=0; r<8; r++) {
	   for (int c=0; c<8; c++) { // try to move the friendly piece to any of the 64 squares on board. If it can make a legal move, return true immediately
	       if (make_pseudomove(Position('A'+row, '1'+col), Position('A'+r, '1'+c)))
	         return true;
	    }
       	  }
        } 
      } 
    }
    return false;
  }   

  bool Game::in_mate(const bool& white) {	
    if (in_check(white) && !any_moves_left(white))
      return true;
    return false;
  }
  
  bool Game::in_stalemate(const bool& white)  {
    if (!in_check(white) && !any_moves_left(white))
      return true;
    return false;
  }
  
  std::istream& operator>> (std::istream& is, Game& game) { 
   // clear board
   Board temp;
   game.board = temp;
   for (int row=0; row<8; row++) {
     for (int col=0; col<8; col++) { // go through all 64 squares
	char c = is.get();
      	if (c == '\n') 
          c = is.get(); // get rid of newline character
      	if (c != '-')
      	  game.board.add_piece(Position('A'+col, '8'-row), c); // reads board from A8 to H1
      }
    }
    is.get(); // get rid of last newline character
    char turn = is.get();
    if (turn == 'w') game.is_white_turn = true;
    else game.is_white_turn = false;
    return is;
  }
  
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<< (std::ostream& os, const Game& game) {
    // Write the board out and then either the character 'w' or the character 'b',
    // depending on whose turn it is
    return os << game.board << (game.turn_white() ? 'w' : 'b');
  }
}
