#ifndef __KING_H__
#define __KING_H__
#include <string>
#include "piece.h"

class King: public Piece
{
    bool moved;
public:
//canmove(r,c) determines if the king can move to row r and coloumn
//c without checking if it becomes in check when doing so.
    bool canmove(int r, int c);

    explicit King(char l);//ctor
    ~King();
    bool incheck();


//hasmoved() determines whether a king has moved.

    bool hasmoved();


//setmovede() determines if the king can move to r and c without checking if it becomes
//in check.
    void setmoved();
    
//setincheck() sets the corresponding player incheck.   
    void setincheck();
//unsetincheck() unsets the corresponding player incheck.      
    void unsetincheck();
 
    void draw(); //draws the king
    std::string getcoords(); //gets the kings coords
};

#endif

