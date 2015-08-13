#include <iostream>
#include "bishop.h"
using namespace std;


Bishop::Bishop( char l):Piece(l) {}

Bishop::~Bishop(){}

bool Bishop::canmove(int r, int c)
{

    int tmprow=row;
    int tmpcol=col;
    int vd=abs(tmprow-r);
    int hd=abs(tmpcol-c); 
    int tmpvd=vd-1;
    bool cancapture=r<BoardSize&&c<BoardSize&&r>=0&&c>=0&&
                    (allthepieces[r][c]->istype("empty")
                     ||(allthepieces[r][c]->istype("white")&&type=="black")
                     ||(allthepieces[r][c]->istype("black")&&type=="white"));
    if((vd==0)||vd!=hd||!cancapture)return false;
    if (col<c&&row<r)
    {
        while (true)
        {


            tmpcol++;
            tmprow++;
           
            if(tmpvd==0)
            {
                return true;

            }
            if(allthepieces[tmprow][tmpcol]->istype("piece"))
            {
                break;
            }
            tmpvd--;




        }
    }
    else if (col>c&&row>r)
    {
        while (true)
        {   
            tmpcol--;
            tmprow--;
                      if(tmpvd==0)
            {

                return true;

            }
           
            if(allthepieces[tmprow][tmpcol]->istype("piece"))
            {
                break;
            }
            tmpvd--;





        }
    }
    else if (col<c&&row>r)
    {
        while (true)
        {
            tmpcol++;
            tmprow--;
          if(tmpvd==0)
            {
                return true;

            }
            if(allthepieces[tmprow][tmpcol]->istype("piece"))
            {
                break;
            }
            tmpvd--;





        }
    }
    else if (col>c&&row<r)
    {
        while (true)
        {
            tmpcol--;
            tmprow++;
          
            if(tmpvd==0){


                return true;

            }
            if(allthepieces[tmprow][tmpcol]->istype("piece"))
            {
          

                break;
            }
            tmpvd--;





        }
    }





    return false;
}

void Bishop::draw()
{




    int winwidth=500/BoardSize;
    int winheight=500/BoardSize;
    int xcoord=col*winwidth+rightshift;
    int ycoord=(BoardSize -1 - row)*winheight+downshift;


    XPoint points[8];

    XPoint p1;
    p1.x=xcoord+winwidth*1/2+2;
    p1.y=ycoord+winheight*1/2;
    XPoint p2;
    p2.x=winwidth*1/10;
    p2.y=winwidth/3;
    XPoint p3;
    p3.x=6;
    p3.y=0;
    XPoint p4;
    p4.x=0;
    p4.y=5;
    XPoint p5;
    p5.x=-(winwidth*2/10 + 18);
    p5.y=0;
    XPoint p6;
    p6.x=0;
    p6.y=-5;
    XPoint p7;
    p7.x=6;
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
        xwin->fillPolygon(points,8, Convex, wcolour);
        xwin->drawLines(points,8, Xwindow::Black);
    }
    else
    {
        xwin->fillPolygon(points, 8,Convex, bcolour);
        xwin->drawLines(points,8, Xwindow::Black);
    }

    int finalcirclewidth=winwidth/4;
    int finalcircleheight=winheight/12;
    int circlexcoord=xcoord+winwidth/2-finalcirclewidth/2-1;
    int circleycoord=ycoord+winheight/2-finalcircleheight/2;
    int angle1=0;
    int angle2=360*64;

   

    if (type=="white")
    {
        xwin->fillArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, wcolour);
        xwin->drawArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, Xwindow::Black);
    }
    else
    {
        xwin->fillArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, bcolour);
        xwin->drawArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, Xwindow::Black);
    }

    finalcirclewidth=winwidth/6;
    finalcircleheight=winheight/3;
    circlexcoord=xcoord+winwidth/2-finalcirclewidth/2;
    circleycoord=ycoord+winheight/2-finalcircleheight/2-6;
    angle1=0;
    angle2=360*64;




    if (type=="white")
    {
        xwin->fillArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, wcolour);
        angle1=-30*64;
        angle2=250*64;
        xwin->drawArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, Xwindow::Black);
    }
    else
    {
        xwin->fillArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, bcolour);
        angle1=-30*64;
        angle2=250*64;
        xwin->drawArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, Xwindow::Black);
    }


    finalcirclewidth=winwidth/12;
    finalcircleheight=winheight/12;
    circlexcoord=xcoord+winwidth/2-finalcirclewidth/2;
    circleycoord=ycoord+winheight/2-finalcircleheight/2-18;
    angle1=0;
    angle2=360*64;




    if (type=="white")
    {
        xwin->fillArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, wcolour);
        angle1=-30*64;
        angle2=250*64;
        xwin->drawArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, Xwindow::Black);

    }
    else
    {
        xwin->fillArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, bcolour);
        angle1=-30*64;
        angle2=250*64;
        xwin->drawArc(circlexcoord, circleycoord, finalcirclewidth, finalcircleheight,angle1,angle2, Xwindow::Black);
    }



     xwin->drawRectangle(rightshift, downshift, winwidth*8, winheight*8); 
    


}

