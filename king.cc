#include <iostream>
#include "king.h"
#include "player.h"


using namespace std;

King::King(char l):Piece(l),moved(false) {}

King::~King() {}

bool King::canmove(int r, int c)
{


    bool enemyorempty;
    if (type=="white")enemyorempty=(allthepieces[r][c]->istype("black")||allthepieces[r][c]->istype("empty"));
    else enemyorempty=(allthepieces[r][c]->istype("white")||allthepieces[r][c]->istype("empty"));

    if((c==col+1)&&(r==row+1)
            &&c<BoardSize&&r<BoardSize
            &&enemyorempty)
    {
        return true;
    }
    else if((c==col+1)&&(r==row)
            &&c<BoardSize
            &&enemyorempty)
    {
        return true;
    }
    else if((c==col+1)&&(r==row-1)
            &&c<BoardSize&&r>=0
            &&enemyorempty)
    {
        return true;
    }
    else if((c==col)&&(r==row-1)
            &&r>=0
            &&enemyorempty)
    {
        return true;
    }
    else if((c==col-1)&&(r==row-1)
            &&c>=0&&r>=0
            &&enemyorempty)
    {
        return true;
    }
    else if((c==col-1)&&(r==row)
            &&c>=0
            &&enemyorempty)
    {
        return true;
    }
    else if((c==col-1)&&(r==row+1)
            &&c>=0&&r<BoardSize
            &&enemyorempty)
    {
        return true;
    }
    else if((c==col)&&(r==row+1)
            &&r<BoardSize
            &&enemyorempty)
    {
        return true;
    }

    return false;
}

bool King::incheck()
{
    if (type=="white")
    {
        for (int r=0; r<BoardSize; r++)
        {
           
            for (int c=0; c<BoardSize; c++)
            {
               
                if (allthepieces[r][c]->istype("black")&&allthepieces[r][c]->canmove(row,col))
                {
                   
                    return true;
                }
            }

        }
        return false;
    }
    else
    {
        for (int r=0; r<BoardSize; r++)
        {
            
            for (int c=0; c<BoardSize; c++)
            {
               
                if (allthepieces[r][c]->istype("white")&&allthepieces[r][c]->canmove(row,col))
                {
                     return true;
                }
            }

        }
        return false;
    }
}

bool King::hasmoved()
{
    return moved;
}

void King::setmoved()
{
   
    moved=true;

}

void King::setincheck()
{
    if(type=="white")
    {
        whiteplayer->setincheck();
    }
    else blackplayer->setincheck();
}

void King::unsetincheck()
{
    if(type=="white")
    {
        whiteplayer->unsetincheck();
    }
    else blackplayer->unsetincheck();
}

string King::getcoords()
{
    return Piece::getcoords();
}


void King::draw()
{


    int winwidth=500/BoardSize;
    int winheight=500/BoardSize;
    int xcoord=col*winwidth+rightshift;
    int ycoord=(BoardSize -1 - row)*winheight+downshift;



    XPoint points[8];

    XPoint p1;
    p1.x=xcoord+winwidth*1/2;
    p1.y=ycoord+winheight*1/2;
    XPoint p2;
    p2.x=winwidth*1/6;
    p2.y=winwidth/3;
    XPoint p3;
    p3.x=5;
    p3.y=0;
    XPoint p4;
    p4.x=0;
    p4.y=5;
    XPoint p5;
    p5.x=-(winwidth*2/6+10);
    p5.y=0;
    XPoint p6;
    p6.x=0;
    p6.y=-5;
    XPoint p7;
    p7.x=5;
    p7.y=0;
    XPoint p8;
    p8.x=winwidth*1/6;
    p8.y=-winwidth/3;


    points[0]=p1;
    points[1]=p2;
    points[2]=p3;
    points[3]=p4;
    points[4]=p5;
    points[5]=p6;
    points[6]=p7;
    points[7]=p8;

    if (type=="white")
    {
        xwin->fillPolygon(points,8,Convex, wcolour);
        xwin->drawLines(points,8, Xwindow::Black);
    }
    else
    {
        xwin->fillPolygon(points, 8,Convex, bcolour);
        xwin->drawLines(points,8, Xwindow::Black);
    }
    int finalcirclewidth=winwidth/3;
    int finalcircleheight=winheight/10;
    int circlexcoord=xcoord+winwidth/2-finalcirclewidth/2;
    int circleycoord=ycoord+winheight/2-finalcircleheight/2;
    int angle1=0;
    int angle2=360*64;




    if (type=="white")
    {
        xwin->fillArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, wcolour);
        angle1=-70*64;
        angle2=140*64;
        xwin->drawArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, Xwindow::Black);
        angle1=-100*64;
        angle2=-150*64;
        xwin->drawArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, Xwindow::Black);
    }
    else
    {
        xwin->fillArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, bcolour);
        angle1=-70*64;
        angle2=140*64;
        xwin->drawArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, Xwindow::Black);
        angle1=-100*64;
        angle2=-150*64;
        xwin->drawArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, Xwindow::Black);
    }
    p1.x=xcoord+winwidth/2-3;
    p1.y=ycoord+winheight/2-finalcircleheight/2+1;
    p2.x=-5;
    p2.y=-5;
    p3.x=5;
    p3.y=-5;
    p4.x=0;
    p4.y=-5;
    p5.x=-5;
    p5.y=0;
    p6.x=0;
    p6.y=-5;
    p7.x=5;
    p7.y=0;
    p8.x=0;
    p8.y=-5;
    XPoint p9;
    p9.x=5;
    p9.y=0;
    XPoint p10;
    p10.x=0;
    p10.y=5;
    XPoint p11;
    p11.x=5;
    p11.y=0;
    XPoint p12;
    p12.x=0;
    p12.y=5;
    XPoint p13;
    p13.x=-5;
    p13.y=0;
    XPoint p14;
    p14.x=0;
    p14.y=5;
    XPoint p15;
    p15.x=5;
    p15.y=5;
    XPoint p16;
    p16.x=-5;
    p16.y=5;

    XPoint points2[16];
    points2[0]=p1;
    points2[1]=p2;
    points2[2]=p3;
    points2[3]=p4;
    points2[4]=p5;
    points2[5]=p6;
    points2[6]=p7;
    points2[7]=p8;
    points2[8]=p9;
    points2[9]=p10;
    points2[10]=p11;
    points2[11]=p12;
    points2[12]=p13;
    points2[13]=p14;
    points2[14]=p15;
    points2[15]=p16;


    if (type=="white")
    {
        xwin->fillPolygon(points2,16, Convex,wcolour);
        xwin->drawLines(points2,16, Xwindow::Black);
    }
    else
    {
        xwin->fillPolygon(points2, 16,Convex, bcolour);
        xwin->drawLines(points2,16, Xwindow::Black);
    }
    xwin->drawRectangle(rightshift, downshift, winwidth*8, winheight*8);

}


