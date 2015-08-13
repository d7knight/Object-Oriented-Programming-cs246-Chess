#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <string>
#include "piece.h"

class Bishop: public Piece
{

public:
    bool canmove(int r, int c);//determines where a bishop can move
    explicit Bishop(char l);
    ~Bishop();
    void draw();//draws a bishop

};

#endif

