#include "Bishop.h"
#include <cmath>

namespace Chess
{
  bool Bishop::legal_move_shape(const Position& start, const Position& end) const {
    char start_col = start.first;
    char start_row = start.second;
    char end_col = end.first;
    char end_row = end.second;
    int vert_dis = std::abs(start_row - end_row);
    int hor_dis = std::abs(start_col - end_col);
  
    //diagonal movement test (vertical and horizontal movement should be equal
    if(vert_dis == hor_dis && vert_dis != 0) {
      return true;
    }
    return false;
  }
}
