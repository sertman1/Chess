#include "Knight.h"
#include <cmath>

namespace Chess
{
  bool Knight::legal_move_shape(const Position& start, const Position& end) const {
    char start_col = start.first;
    char start_row = start.second;
    char end_col = end.first;
    char end_row = end.second;
    int vert_dis = std::abs(start_row - end_row);
    int hor_dis = std::abs(start_col - end_col);
    
    //'L' shape can be modeled as displacement by 1 horizontally and 2 vertically
    if(hor_dis == 1 && vert_dis == 2) {
      return true;
    }
    //'L' shape can be modeled as displacement by 2 horizontally and 1 vertically
    if(hor_dis == 2 && vert_dis == 1) {
      return true;
    }
    return false;
  }
}
