#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>

class King;
class Piece;
class TextDisplay;
class Xwindow;

class Board {
  Piece ***pieces; 
  //so the reason we need triple pointers is because Piece is an abstract class so we can't make any 
  //piece objects however we can create piece pointers so basically the board is a a board of piece pointers.
  King * wking;    
  King * bking;
  TextDisplay * thedisplay;
  Xwindow * xwin;
  //a helper function for makemove, does the castle moves.
  void makemovecastle(int r, int c, bool toleft); 
  //a helper function for makemove, does the passant moves.
  void makemovepassant(int r , int c, int finalr, int finalc,char theletter); 
 //movingking a helper function for makemovecastle, moves the king one square 
 //left if left is true one square right otherwise..
  void movingking(bool white, bool left, int r ,int c); 
 //updateking(oldking,newking) checks whether oldking points to a king then 
 // updates the corresponding king pointer simutaneously in
 //both the Piece and Board class. 
  void updateking(Piece* oldking,Piece* newking); 
  //unsetpassant() unsets passant of all pawns on the board which the players whos turn it is owns.
  void unsetpassant();
  //checks whether the player whos turn it is owns the piece at r,c 
  bool isyourpiece(int r, int c);
 public:
  //if opp is + puts a piece on the board if - removes one.
  void putpiece(char opp, char piece, std::string coords); 
  //makemove makes a move, if it is a valid move and updates the players turn
  //and makes the move if not a valid move undoes the move and does not change thplayers turn.
  void makemove(std::string start, std::string final, int level); 
  bool cansetupexit();//checks whether setup can exit
  bool nomoremoves();//checks if there are no available moves for the player whos turn it is.
  Piece*** getpieces();
  void notifybeforemoveboard(std::string coords, std::string colour);
  void notifyaftermoveboard(std::string dest, std::string colour); 
  ~Board();
   Board();
    friend std::ostream &operator<<(std::ostream &out, const Board &brd);
};

#endif
