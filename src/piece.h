#ifndef __PIECE_H__
#define __PIECE_H__
#include <string>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "textdisplay.h"
#include "window.h"
class Player;
class Board; 
class King;


class Piece
{

protected:
    int row;
    int col;
    
    char letter;
    std::string type;
    bool cancheckking;
    int danger;
    static Piece*** allthepieces;
    static Piece* blackking;
    static Piece* whiteking;
    static Player* whiteplayer;
    static Player* blackplayer;
    static int wcolour;
    static int bcolour;
    static int tile1colour; //The following are used for the display
    static int tile2colour;
    static int rightshift;
    static int downshift;
    static Xwindow * xwin;
public:
    virtual void draw()=0;  //for drawing a piece
    virtual bool canmove(int r, int c)=0; //seeing if a piece can move to a desired location.
    virtual ~Piece();
    void undraw(); //for undrawing the piece
    void notify(TextDisplay *td);//notifying the textdisplay
    void setcoords(int r, int c); //setting coords
    explicit Piece(char l); //ctor
    static void setPlayer(std::string clr, Player* player);
    static void setKing(std::string clr, Piece* king);
    static void setPieces(Piece*** allpieces);
    // istype(str) checks wether a piece is of type empty, white or black.
    bool istype(std::string str);  
    char getletter();
    static void drawletters(); //drwas the row numbers and column letters around the board.
    static void setdisplay(Xwindow *w);//sets the static pointer to the display
    static void setpiececolours(std::string white, std::string black); //sets the piece colours
    static void settilecolours(std::string tile1, std::string tile2);//sets the tile colours
    static void redraw(); //redraws the board.
    std::string getcoords();
    int indanger(); //returns value of danger level
    void incdanger();//increments the danger level
    void dimdanger();//deminishes the danger level
    void resetdanger();//resets the danger level
    int getrow();
    int getcol();

};
//abs(x) returns the absolute value of x
//PRE: TRUE
//POST: returns the absolute value of x.
int abs(int x); 
#endif


