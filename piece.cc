#include <iostream>
#include "piece.h"
#include <unistd.h>


using namespace std;
Piece* Piece::blackking=NULL;
Piece* Piece::whiteking=NULL;
Player* Piece::whiteplayer=NULL;
Player* Piece::blackplayer=NULL;
Piece*** Piece::allthepieces=NULL;
Xwindow* Piece::xwin=NULL;
int Piece::wcolour=Xwindow::White;
int Piece::bcolour=Xwindow::Black;
int Piece::tile1colour=Xwindow::White;
int Piece::tile2colour=Xwindow::Gray; //note: black cannot be chosen as colour for tiles
int Piece::rightshift=50;
int Piece::downshift=50;

//see piece.h for details
int abs(int x)
{
    if (x < 0)
        return -x;
    else
        return x;
}


Piece::Piece(char l)
{


    letter=l;


    if (l==' ')
    {
        type="empty";
    }
    else
    {
        if (l=='K'||l=='Q'||l=='R'||l=='B'||l=='N'||l=='K'||l=='P')
        {
            type="white";
        }
        else type="black";
    }
}

Piece::~Piece() {}

void Piece::notify(TextDisplay *td)
{
    td->notify(letter, row, col);
}

void Piece::setcoords(int r, int c)
{
    row=r;
    col=c;      
}

void Piece::setPlayer(string clr, Player* player)
{
    if (clr=="white")
    {
        whiteplayer=player;
    }
    else if (clr == "black")
    {
        blackplayer=player;
    }

}

void Piece::setKing(string clr, Piece* king)
{
    if (clr=="white")
    {
        whiteking=king;
    }
    else if (clr == "black")
    {
        blackking=king;
    }
}

bool Piece::istype(string str)
{
    if (str=="piece")
    {
        return (type=="black")||(type=="white");
    }
    return (type==str);
}


void Piece::setPieces(Piece*** allpieces)
{
    allthepieces=allpieces;
}

char Piece::getletter()
{
    return letter;
}

void Piece::setdisplay(Xwindow *w)
{

    xwin=w;
}

void Piece::undraw()
{

    int winwidth=500/BoardSize;
    int winheight=500/BoardSize;
    int xcoord=col*winwidth+rightshift;
    int ycoord=(BoardSize -1 - row)*winheight+downshift;
    if ((row%2==0&&col%2==0)||(row%2!=0&&col%2!=0))xwin->fillRectangle(xcoord, ycoord, winwidth, winheight, tile2colour);
    else xwin->fillRectangle(xcoord, ycoord, winwidth, winheight, tile1colour);
    
     xwin->drawRectangle(rightshift, downshift, winwidth*8, winheight*8); 
    
}

void Piece::setpiececolours(string white, string black)
{
    if (white!=black)
    {
        if(white=="white")wcolour=Xwindow::White;
        else if (white=="black")wcolour=Xwindow::Black;
        else if (white=="red")wcolour=Xwindow::Red;
        else if (white=="blue")wcolour=Xwindow::Blue;
        else if (white=="green")wcolour=Xwindow::Green;
        else if (white=="cyan")wcolour=Xwindow::Cyan;
        else if (white=="yellow")wcolour=Xwindow::Yellow;
        else if (white=="orange")wcolour=Xwindow::Orange;
        else if (white=="brown")wcolour=Xwindow::Brown;
        else if (white=="gray")wcolour=Xwindow::Gray;
        if(black=="white")bcolour=Xwindow::White;
        else if (black=="black")bcolour=Xwindow::Black;
        else if (black=="red")bcolour=Xwindow::Red;
        else if (black=="blue")bcolour=Xwindow::Blue;
        else if (black=="green")bcolour=Xwindow::Green;
        else if (black=="cyan")bcolour=Xwindow::Cyan;
        else if (black=="yellow")bcolour=Xwindow::Yellow;
        else if (black=="orange")bcolour=Xwindow::Orange;
        else if (black=="brown")bcolour=Xwindow::Brown;
        else if (black=="gray")bcolour=Xwindow::Gray;
    }
}
void Piece::settilecolours(string tile1, string tile2)
{
    if (tile1!=tile2)
    {
        if(tile1=="white")tile1colour=Xwindow::White;
        else if (tile1=="red")tile1colour=Xwindow::Red;
        else if (tile1=="blue")tile1colour=Xwindow::Blue;
        else if (tile1=="green")tile1colour=Xwindow::Green;
        else if (tile1=="cyan")tile1colour=Xwindow::Cyan;
        else if (tile1=="yellow")tile1colour=Xwindow::Yellow;
        else if (tile1=="orange")tile1colour=Xwindow::Orange;
        else if (tile1=="brown")tile1colour=Xwindow::Brown;
        else if (tile1=="gray")tile1colour=Xwindow::Gray;
        if(tile2=="white")tile2colour=Xwindow::White;
        else if (tile2=="red")tile2colour=Xwindow::Red;
        else if (tile2=="blue")tile2colour=Xwindow::Blue;
        else if (tile2=="green")tile2colour=Xwindow::Green;
        else if (tile2=="cyan")tile2colour=Xwindow::Cyan;
        else if (tile2=="yellow")tile2colour=Xwindow::Yellow;
        else if (tile2=="orange")tile2colour=Xwindow::Orange;
        else if (tile2=="brown")tile2colour=Xwindow::Brown;
        else if (tile2=="gray")tile2colour=Xwindow::Gray;
    }
}

void Piece::redraw()
{
    for (int r=0; r<BoardSize; r++)
    {

        for (int c=0; c<BoardSize; c++)
        {

            allthepieces[r][c]->undraw();
            allthepieces[r][c]->draw();

        }

    }
}

void Piece::drawletters()
{   int winwidth=500/BoardSize;
    int winheight=500/BoardSize;
    int xcoord;
    int ycoord;
    int r=0;
        for (int c=0; c<BoardSize; c++)
        {    xcoord=(c+1)*winwidth+rightshift/3;
             ycoord=(BoardSize - r +1 )*winheight+downshift/3;
             string msg;
             msg+=(char)'a'+c;
            xwin->drawString(xcoord, ycoord, msg);
            msg="";
        }
   
    r=7;
        for (int c=0; c<BoardSize; c++)
        {    xcoord=(c+1)*winwidth+rightshift/3;
             ycoord=(BoardSize - r - 1 )*winheight+downshift/2;
             string msg;
             msg+=(char)'a'+c;
            xwin->drawString(xcoord, ycoord, msg);
            msg="";
        }
    r=0;
    int c=0;
        for (; r<BoardSize; r++)
        {    xcoord=(c)*winwidth+rightshift/3;
             ycoord=(BoardSize - r )*winheight+downshift/3;
             string msg;
             msg+=(char)'1'+r;
           
            xwin->drawString(xcoord, ycoord, msg);
            msg="";
        }
    r=0;    
    c=7;
        for (; r<BoardSize; r++)
        {    xcoord=(c+2)*winwidth+rightshift/3;
             ycoord=(BoardSize - r  )*winheight+downshift/3;
             string msg;
             msg+=(char)'1'+r;
            xwin->drawString(xcoord, ycoord, msg);
            msg="";
        }

     xwin->drawRectangle(rightshift, downshift, winwidth*8, winheight*8); 
    
}

string Piece::getcoords(){
    string s1="";
    s1+=(char)(col+'a');
    s1+=(char)(row+'1');
    return s1;
}

int Piece::getrow(){
    return row;
}
int Piece::getcol(){
    return col;
}

int Piece::indanger(){
    return danger;
}

void Piece::incdanger(){
  
    danger++;
}
void Piece::dimdanger(){
    if(danger == 0){}
    else danger--;
   
}

void Piece::resetdanger(){
    if(danger == 0){}
    else danger = 0;
}

