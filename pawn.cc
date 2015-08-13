#include <iostream>
#include "pawn.h"
#include "player.h"

using namespace std;
//these are incomplete just wrote the constructors to do testing
Pawn::Pawn(char l):Piece(l),empassenc(0) {}
Pawn::~Pawn() {}

bool Pawn::canmove(int r, int c)
{


    if (istype("white"))
    {


        if((c==col+1)&&(r==row+1)&&c<BoardSize&&r<BoardSize&&
                (allthepieces[r][c]->istype("black")||
                 (empassen&&allthepieces[r][c]->istype("empty")&&empassenc==c)))
        {
//capture to right
            return true;
        }
        else if((c==col)&&(r==row+1)&&r<BoardSize&&allthepieces[r][c]->istype("empty"))
        {
//forward
            return true;

        }
        else if((c==col-1)&&(r==row+1)&&c>=0&&r<BoardSize&&
                (allthepieces[r][c]->istype("black")||
                 (empassen&&allthepieces[r][c]->istype("empty")&&empassenc==c)))
        {
//capture to left
            return true;
        }
        else if((c==col)&&(r==row+2)&&row==1&&allthepieces[r][c]->istype("empty")&&allthepieces[r-1][c]->istype("empty"))
        {
//double jump if and only if at row 1 and have not moved and no pieces in two spaces infront of pawn
            return true;
        }


    }
    else
    {
        if((c==col-1)&&(r==row-1)&&c>=0&&r>=0&&
                (allthepieces[r][c]->istype("white")||
                 (empassen&&allthepieces[r][c]->istype("empty")&&empassenc==c)))
        {
//capture to right
            return true;
        }

        else if((c==col)&&(r==row-1)&&r>=0&&allthepieces[r][c]->istype("empty"))
        {
//forward
            return true;
        }
        else if((c==col+1)&&(r==row-1)&&c>=0&&r>=0&&
                (allthepieces[r][c]->istype("white")||
                 (empassen&&allthepieces[r][c]->istype("empty")&&empassenc==c)))
        {
//capture to left
            return true;
        }


        else if((c==col)&&(r==row-2)&&row==6&&allthepieces[r][c]->istype("empty")&&allthepieces[r+1][c]->istype("empty"))
        {
//passant



            return true;
        }


    }

    return false;
}

void Pawn::pawnexchange()
{
    if (type=="white")
    {
        whiteplayer->setpawnexchange();

    }
    else
    {

        blackplayer->setpawnexchange();

    }
}

void Pawn::setempassen(int c)
{

    empassenc=c;
    empassen=true;
}
int Pawn::getempassen()
{
    return empassenc;
}

bool Pawn::isempassen()
{
    return empassen;
}

void Pawn::unsetempassen()
{
    empassen=false;
}

void Pawn::draw()
{
    int winwidth=500/BoardSize;
    int winheight=500/BoardSize;
    int xcoord=col*winwidth+rightshift;
    int ycoord=(BoardSize-1-row)*winheight+downshift;

    int finalcirclewidth=winwidth/3;
    int finalcircleheight=2*winheight/3;
    int circlexcoord=xcoord+winwidth/3;
    int circleycoord=ycoord+winheight/3+winheight/3 - winheight/8;
    int angle1=0;
    int angle2=180*64;




    if (type=="white")
    {
        usleep(1000);
        xwin->fillArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, wcolour);
        usleep(1000);
        xwin->drawArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, Xwindow::Black);
        usleep(1000);
        xwin->drawLine(circlexcoord, circleycoord+finalcircleheight/2+1,circlexcoord+finalcirclewidth,circleycoord+finalcircleheight/2+1);
    }
    else
    {
        usleep(1000);
        xwin->fillArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, bcolour);
        usleep(1000);
        xwin->drawArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, Xwindow::Black);
        usleep(1000);
        xwin->drawLine(circlexcoord, circleycoord+finalcircleheight/2+1,circlexcoord+finalcirclewidth,circleycoord+finalcircleheight/2+1);

    }



    int finalcircle2width=winwidth/5;
    int finalcircle2height=winheight/5;
    int circle2xcoord=xcoord+winwidth/3+finalcirclewidth*2/10;
    int circle2ycoord=ycoord+winheight*3/8;
    int angle3=0;
    int angle4=360*64;

    usleep(5000);


    if (type=="white")
    {
        xwin->fillArc(circle2xcoord, circle2ycoord, finalcircle2width, finalcircle2height,angle3,angle4, wcolour);
        angle3=-60*64;
        angle4=300*64;
        xwin->drawArc(circle2xcoord, circle2ycoord, finalcircle2width, finalcircle2height,angle3,angle4, Xwindow::Black);
    }
    else
    {
        xwin->fillArc(circle2xcoord, circle2ycoord, finalcircle2width, finalcircle2height,angle3,angle4, bcolour);
        angle3=-60*64;
        angle4=300*64;
        xwin->drawArc(circle2xcoord, circle2ycoord, finalcircle2width, finalcircle2height,angle3,angle4, Xwindow::Black);
    }
    xwin->drawRectangle(rightshift, downshift, winwidth*8, winheight*8);

}


