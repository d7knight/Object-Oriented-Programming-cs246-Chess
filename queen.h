#ifndef __QUEEN_H__
#define __QUEEN_H__
#include <string>
#include "piece.h"

class Queen: public Piece
{

public:
    bool canmove(int r, int c);//determines where a queen can move
    explicit Queen( char l);
    ~Queen();
    void draw(); //draws a queen
};

#endif

