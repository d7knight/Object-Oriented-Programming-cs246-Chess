#ifndef __PAWN_H__
#define __PAWN_H__
#include <string>
#include "piece.h"

class Pawn: public Piece {
bool moved;
bool empassen;
int empassenc;
 public:
bool canmove(int r, int c); //seeing if a pawn can move to a desired location.
explicit Pawn(char l);
~Pawn(); //dtor
void pawnexchange();
void setempassen(int c); //sets the location of the empassen pawn
void unsetempassen(); //turns empassen off
int getempassen();
bool isempassen();
void draw();//draws a pawn
};

#endif
