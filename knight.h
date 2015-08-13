#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include <string>
#include "piece.h"

class Knight: public Piece
{

public:
    bool canmove(int r,int c);//determines where a knight can move
    explicit Knight(char l);
    ~Knight();
    void draw(); //draws a knight
};

#endif

