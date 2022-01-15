#include "King.h"
#include <cmath>

namespace Chess
{
  bool King::legal_move_shape(const Position& start, const Position& end) const {
    char start_col = start.first;
    char start_row = start.second;
    char end_col = end.first;
    char end_row = end.second;
    int vert_dis = std::abs(start_row - end_row);
    int hor_dis = std::abs(start_col - end_col);
  
    //only valid coordinates are a 1-square perimeter around piece
    if(vert_dis <= 1 && hor_dis <= 1 && (hor_dis != 0 && vert_dis != 0)) {
      return true;
    }
    return false;
  }
}
