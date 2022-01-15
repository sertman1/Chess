#include "Pawn.h"
#include <cmath>

namespace Chess
{
  bool Pawn::legal_move_shape(const Position& start, const Position& end) const {
    char start_col = start.first;
    char start_row = start.second;
    char end_col = end.first;
    char end_row = end.second;
    int vert_dis = std::abs(start_row - end_row);
    int hor_dis = std::abs(start_col - end_col);
    
    //pawn can only move vertically 1 forward
    if(vert_dis == 1 && hor_dis == 0) {
      //forward check for white pawn
      if(Pawn::is_white() && start_row < end_row) {
        return true;
      }
      //forward check for black pawn
      else if(!Pawn::is_white() && start_row > end_row) {
        return true;
      }
    }
    
    //pawn can move vertically 2 only as first move
    if(vert_dis == 2 && hor_dis == 0) {
      //start check for white pawn
      if(Pawn::is_white() && start_row == 2 && end_row == 4) {
        return true;
      }
      //start check for black pawn
      else if(!Pawn::is_white() && start_row == 7 && end_row == 5) {
        return true;
      }
    }
    return false;
  }
    
  bool Pawn::legal_capture_shape(const Position& start, const Position& end) const {
    char start_col = start.first;
    char start_row = start.second;
    char end_col = end.first;
    char end_row = end.second;
    int vert_dis = std::abs(start_row - end_row);
    int hor_dis = std::abs(start_col - end_col);
    
    //legal capture for pawn is one forward-diagonal
    if(vert_dis == 1 && hor_dis == 1) {
      //diagonal check for white pawn
      if(Pawn::is_white() && start_row < end_row) {
        return true;
      }
      //diagonal check for black pawn
      else if(!Pawn::is_white() && start_row > end_row) {
        return true;
      }
    }
    return false;
  }
}
