#include <iostream>
#include "queen.h"
using namespace std;
//these are incomplete just wrote the constructors to do testing
Queen::Queen(char l):Piece(l) {}
Queen::~Queen() {}
bool Queen::canmove(int r, int c)
{
    int tmprow=row;
    int tmpcol=col;
    int vd=abs(tmprow-r);
    int hd=abs(tmpcol-c);
    bool cancapture=r<BoardSize&&c<BoardSize&&r>=0&&c>=0&&
                    (allthepieces[r][c]->istype("empty")
                     ||(allthepieces[r][c]->istype("white")&&type=="black")
                     ||(allthepieces[r][c]->istype("black")&&type=="white"));
    if((vd==0&&hd==0)||!cancapture)return false;
    int tmphd=hd-1;
    int tmpvd=vd-1;
    if(vd==0||hd==0)
    {
        if(vd==0)
        {
            if (col<c)
            {
                while (true)
                {

                    tmpcol++;
                    if(tmphd==0)
                    {


                        return true;

                    }
                    if(allthepieces[r][tmpcol]->istype("piece"))
                    {
                        break;
                    }
                    tmphd--;




                }
            }
            else if(col>c)
            {
                while (true)
                {
                    tmpcol--;
                    if(tmphd==0)
                    {
                        return true;
                    }

                    if(allthepieces[r][tmpcol]->istype("piece"))
                    {
                        break;
                    }
                    tmphd--;



                }

            }
        }

        else if(hd==0)
        {

            if (row<r)
            {
                while (true)
                {
                    tmprow++;
                    if(tmpvd==0)
                    {
                        return true;

                    }
                    if(allthepieces[tmprow][c]->istype("piece"))
                    {
                        break;
                    }
                    tmpvd--;



                }
            }
            else if(row>r)
            {
                while (true)
                {
                    tmprow--;
                    if(tmpvd==0)
                    {
                        return true;

                    }
                    if(allthepieces[tmprow][c]->istype("piece"))
                        break;

                    tmpvd--;

                }


            }

        }

    }
    else if(vd==hd)
    {
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
    }




    return false;

}

void Queen::draw()
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
        xwin->fillPolygon(points,8, Convex, wcolour);
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
    p2.y=-3;
    p3.x=5;
    p3.y=-5;
    p4.x=-3;
    p4.y=-10;
    p5.x=1;
    p5.y=0;
    p6.x=2;
    p6.y=1;
    p7.x=2;
    p7.y=-2;
    p8.x=2;
    p8.y=2;
    XPoint p9;
    p9.x=2;
    p9.y=-2;
    XPoint p10;
    p10.x=2;
    p10.y=2;
    XPoint p11;
    p11.x=2;
    p11.y=-1;
    XPoint p12;
    p12.x=1;
    p12.y=0;
    XPoint p13;
    p13.x=-3;
    p13.y=10;
    XPoint p14;
    p14.x=5;
    p14.y=5;
    XPoint p15;
    p15.x=-5;
    p15.y=3;

    XPoint points2[15];
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



    if (type=="white")
    {
        xwin->fillPolygon(points2,15,Nonconvex, wcolour);
        xwin->drawLines(points2,15, Xwindow::Black);
    }
    else
    {
        xwin->fillPolygon(points2, 15,Nonconvex, bcolour);
        xwin->drawLines(points2,15, Xwindow::Black);
    }
     xwin->drawRectangle(rightshift, downshift, winwidth*8, winheight*8); 
    
}






