#include <iostream>
#include "knight.h"
using namespace std;
//these are incomplete just wrote the constructors to do testing
Knight::Knight(char l):Piece(l) {}
Knight::~Knight() {}

bool Knight::canmove(int r, int c)
{   
    if (r>=BoardSize||c>=BoardSize||c<0 ||r<0)return false;
    bool enemyorempty=(type=="white")?(allthepieces[r][c]->istype("black")||allthepieces[r][c]->istype("empty")):
                      (allthepieces[r][c]->istype("white")||allthepieces[r][c]->istype("empty"));

    if((c==col+1)&&(r==row+2)
            &&c<BoardSize&&r<BoardSize
            &&enemyorempty)
    {
        return true;
    }
    else if((c==col+2)&&(r==row+1)
            &&c<BoardSize&&r<BoardSize
            &&enemyorempty)
    {
        return true;
    }
    else if((c==col-1)&&(r==row-2)
            &&r>=0&&c>=0
            &&enemyorempty)
    {
        return true;
    }
    else if((c==col-2)&&(r==row-1)
            &&r>=0&&c>=0
            &&enemyorempty)
    {
        return true;
    }
    else if((c==col-1)&&(r==row+2)
            &&c>=0&&r<BoardSize
            &&enemyorempty)
    {
        return true;
    }
    else if((c==col+2)&&(r==row-1)
            &&r>=0&&c<BoardSize
            &&enemyorempty)
    {
        return true;
    }
    else if((c==col+1)&&(r==row-2)
            &&r>=0&&c<BoardSize
            &&enemyorempty)
    {
        return true;
    }
    else if((c==col-2)&&(r==row+1)
            &&r<BoardSize&&c>=0
            &&enemyorempty)
    {
        return true;
    }

    return false;


}


void Knight::draw()
{



    int winwidth=500/BoardSize;
    int winheight=500/BoardSize;
    int xcoord=col*winwidth+rightshift;
    int ycoord=(BoardSize -1 - row)*winheight+downshift;


    XPoint points[14];

    XPoint p1;
    p1.x=xcoord+winwidth*1/2+5;
    p1.y=ycoord+winheight*1/2;
    XPoint p2;
    p2.x=0;
    p2.y=winwidth/3;
    XPoint p3;
    p3.x=8;
    p3.y=0;
    XPoint p4;
    p4.x=0;
    p4.y=5;
    XPoint p5;
    p5.x=-(winwidth*2/10 + 14);
    p5.y=0;
    XPoint p6;
    p6.x=0;
    p6.y=-5;
    XPoint p7;
    p7.x=5;
    p7.y=0;
    XPoint p8;
    p8.x=3;
    p8.y=-winwidth/3;
    XPoint p9;
    p9.x=-5;
    p9.y=5;
    XPoint p10;
    p10.x=-5;
    p10.y=-5;
    XPoint p11;
    p11.x=0;
    p11.y=-5;
    XPoint p12;
    p12.x=5;
    p12.y=-3;
    XPoint p13;
    p13.x=10;
    p13.y=-5;
    XPoint p14;
    p14.x=5;
    p14.y=13;




    points[0]=p1;
    points[1]=p2;
    points[2]=p3;
    points[3]=p4;
    points[4]=p5;
    points[5]=p6;
    points[6]=p7;
    points[7]=p8;
    points[8]=p9;
    points[9]=p10;
    points[10]=p11;
    points[11]=p12;
    points[12]=p13;
    points[13]=p14;






    if (type=="white")
    {
        xwin->fillPolygon(points,14, Complex, wcolour);
        xwin->drawLines(points,14, Xwindow::Black);
    }
    else
    {
        xwin->fillPolygon(points, 14,Complex, bcolour);
        xwin->drawLines(points,14, Xwindow::Black);
    }

         xwin->drawRectangle(rightshift, downshift, winwidth*8, winheight*8); 
    
}









