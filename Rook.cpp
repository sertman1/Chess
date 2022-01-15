#include "Rook.h"
#include <cmath>

namespace Chess
{
  bool Rook::legal_move_shape(const Position& start, const Position& end) const {
    char start_col = start.first;
    char start_row = start.second;
    char end_col = end.first;
    char end_row = end.second;
    int vert_dis = std::abs(start_row - end_row);
    int hor_dis = std::abs(start_col - end_col);

    //horizontal movement test (vertical movement should be 0)
    if(vert_dis == 0 && hor_dis != 0) {
      return true;
    }
    //vertical movement test (horizontal movement should be 0)
    if(hor_dis == 0 && vert_dis != 0) {
      return true;
    }
    return false;
  }
}


