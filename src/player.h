#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>



class Scoreboard;
class Board;
class Player
{
    std::string colour;
    static std::string turn;
    int level;
    bool pawnexch;
    bool incheck;
    std::string lastcoords;
    static Scoreboard* TheScoreboard;
    static Board *Theboard;
    static Player* whiteplayer;
    static Player* blackplayer;
    bool ischeckmate;
    bool isstalemate;
    explicit Player(std::string clr);
   
public:
    static Player* getPlayer(std::string clr);
    void setlevel(int lvl); //sets the level of the player 
    static Scoreboard* getScoreBoard();
    static void CleanUpScoreboard(); 
    static void CleanUpPlayers();
    static void placepiece(char opp, char piece, std::string coords); //places a piece on the board.
    void Endgame(std::string winner);
    void makemove(std::string cur, std::string dest);
    void checkstate();//checks whether state of game is stalemate or checkmate
    void makemove(); //makes a computer move
    bool pawnexchange();
    void computerpawnexchange(); //pawnexchanges a pawn for the computers
    void setpawnexchange();
    void unsetpawnexchange();
    bool checkmate();
    bool stalemate();
    static void Printboard(); //prints the board
    static std::string whosturn();
    static void setturn(std::string clr);
    void setincheck();
    void unsetincheck();
    static void printresults(); //prints the final results
    bool iscomputer();
    static bool cansetupexit(); //checks whether setup can exit
    void notifybeforemoveplayer(std::string coords, std::string colour);
    void notifyaftermoveplayer(std::string dest, std::string colour);
    void notifyalloppieces(std::string dest, std::string colour);
    void reset(); //resets the board textdisplay and xwindow
    ~Player();
};

#endif

