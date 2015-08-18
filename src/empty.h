#ifndef __EMPTY_H__
#define __EMPTY_H__
#include <string>
#include "piece.h"

class Empty: public Piece {

 public:
 //determines whether an empty space can move to a desired location
bool canmove(int r, int c); 
Empty();
~Empty();
void draw(); //draws an empty space

};

#endif
