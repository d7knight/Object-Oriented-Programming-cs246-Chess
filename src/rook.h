#ifndef __ROOK_H__
#define __ROOK_H__
#include <string>
#include "piece.h"

class Rook: public Piece {
bool moved;
 public:
bool canmove(int r, int c);//seeing if a rook can move to a desired location.
explicit Rook( char l);
~Rook(); //dtor
bool hasmoved();
void setmoved();
void draw(); //draws a rook
};

#endif
