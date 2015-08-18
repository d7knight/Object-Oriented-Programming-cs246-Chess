#include <iostream>
#include "player.h"
#include <cstdlib>
#include "scoreboard.h"
#include "board.h"
#include "piece.h"
#include <stdlib.h>


using namespace std;
Board * Player::Theboard=NULL;
Scoreboard* Player::TheScoreboard=NULL;
Player* Player::whiteplayer=NULL;
Player* Player::blackplayer=NULL;
string Player::turn="";
//see player.h for details

Player::Player(string clr):colour(clr)
{
    ischeckmate=false;
    isstalemate=false;
    incheck=false;
    pawnexch=false;
    
}



//see player.h for details

Player::~Player()
{
    delete Theboard;
    Theboard=NULL; //Protects from deleting it a second time
}

//see player.h for details;
Player  *Player::getPlayer(std::string clr)
{
    
    if (clr=="white")
    {
        if (!whiteplayer)
        {
            whiteplayer = new Player(clr);
            Piece::setPlayer("white",whiteplayer);
        }
        
        return whiteplayer;
    }
    
    else if (clr=="black")
    {
        if (!Theboard)
        {
            Theboard = new Board;
            atexit(CleanUpPlayers);
        }
        Player::getScoreBoard();
        if (!blackplayer)
        {
            blackplayer = new Player(clr);
            Piece::setPlayer("black",blackplayer);
            
        }
        return blackplayer;
    }
    else return blackplayer; //returning blackplayer if clr is neither white or black.
    
}


//see player.h for details

void Player::CleanUpScoreboard()
{
    
    delete TheScoreboard;
    
}

//see player.h for details

void Player::CleanUpPlayers()
{
    delete whiteplayer;
    delete blackplayer;
}


//see player.h for details;

Scoreboard *Player::getScoreBoard()
{
    if (!TheScoreboard)
    {
        TheScoreboard = new Scoreboard;
        atexit(CleanUpScoreboard);
    }
    return TheScoreboard;
}

//see player.h for details;

void Player::setlevel(int lvl)
{
    level=lvl;
}

//see player.h for details

void Player::Endgame(std::string winner)
{
    TheScoreboard->Endgame(winner);
    delete Theboard;
    Theboard = new Board;
    whiteplayer->reset();
    blackplayer->reset();
    
    
}

//see player.h for details

bool Player::checkmate()
{
    
    return ischeckmate;
    
}

//see player.h for details

bool Player::stalemate()
{
    return isstalemate;
}

//see player.h
void Player::makemove(std::string cur, std::string dest)
{   Theboard->makemove(cur, dest, level);
    if (colour==turn){
        cerr<<"Invalid move: " << cur << " to " << dest << endl <<" It's still " << colour <<"'s turn." <<endl;
    }
}

//see player.h for details
void  Player::makemove()
{
    Piece ***all = Theboard->getpieces();
    Piece* mine[63];
    Piece* theirs[63];
    int numpieces = 0;
    int oppieces = 0;
    int move_piece = 0;
    bool otherscanreach;
    bool takenmove = false;
    string cur="";
    string dest="";
    string oppturn;
    string originalturn;
    Piece *otherking;
    if(turn == "white"){
        oppturn = "black";
        originalturn = "white";
    }
    else{
        oppturn = "white";
        originalturn = "black";
    }
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            if(all[i][j]->istype(turn)){
                mine[numpieces] = all[i][j];
                numpieces++;
                //cout << "putting pieces in temp array" << endl;
            }
        }
    }
    //putting my pieces in array mine
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            if(all[i][j]->istype(oppturn)){
                theirs[oppieces] = all[i][j];
                oppieces++;
            }
            if(oppieces > 0 && (theirs[oppieces-1]->getletter() == 'k'
                                || theirs[oppieces-1]->getletter() == 'K')){
                otherking = theirs[oppieces-1];
            }
        }
    }
    //putting their pieces in array theirs
    /////////////////////////////////////////// LEVEL 1 /////////////////////////////////////
    if(level == 1){
       
        int movedpieces[numpieces];
        for(int i = 0; i < numpieces; ++i){
            movedpieces[i] = 0;
        }
        
        for(int k = 0; k < numpieces; ++k){
            while(movedpieces[move_piece] == 1){
                move_piece = rand() % numpieces;
            }
            cur = mine[move_piece]->getcoords();
        	for(int i = 0; i < 1000; ++i){
                int r2 = rand() % 8;
                int c2 = rand() % 8;
                    dest+=static_cast<char>(c2+'a');
                    dest+=static_cast<char>(r2+'1');
                    if(mine[move_piece]->canmove(r2, c2)){
                        Theboard->notifybeforemoveboard(cur,oppturn);
                        Theboard->makemove(cur,dest,level-1);
                        if ((colour=="white"&&turn=="black") ||
                            (colour=="black"&&turn=="white")){
                            lastcoords = dest;
                            Theboard->notifyaftermoveboard(dest, turn);
                            for(int i = 0; i < oppieces; ++i){
                                Theboard->notifyaftermoveboard(dest, originalturn);
                            }
                            return;
                        }
                        else{
                            Theboard->notifyaftermoveboard(cur, oppturn);
                            Theboard->notifyaftermoveboard(dest, turn);
                        }
                    }
                    dest="";
            }
            movedpieces[move_piece] = 1;
        }
        
         for(int k = 0; k < numpieces; ++k){
            cur = mine[k]->getcoords();
            for (int r2=0; r2< 8; r2++){
                for (int c2=0; c2< 8; c2++){
                    dest+=static_cast<char>(c2+'a');
                    dest+=static_cast<char>(r2+'1');
                    if(mine[k]->canmove(r2, c2)){
                        Theboard->notifybeforemoveboard(cur,oppturn);
                        Theboard->makemove(cur,dest,level-1);
                        if ((colour=="white"&&turn=="black") ||
                            (colour=="black"&&turn=="white")){
                            lastcoords = dest;
                            Theboard->notifyaftermoveboard(dest, turn);
                            for(int i = 0; i < oppieces; ++i){
                                Theboard->notifyaftermoveboard(dest, originalturn);
                            }
                            return;
                        }
                        else{
                            Theboard->notifyaftermoveboard(cur, oppturn);
                            Theboard->notifyaftermoveboard(dest, turn);
                        }
                    }
                    dest="";
                }
            }
         }
    }
    /////////////////////////////////////////// LEVEL 2 /////////////////////////////////////
    else if(level == 2){
        if(!takenmove){
            int captures[oppieces];
            for(int i = 0; i < oppieces; ++i){
                captures[i] = 0;
            }
            // ^ declaring a new array to store the reward of capturing pieces.
            
            for(int i = 0; i < numpieces; ++i){
                for(int j = 0; j < oppieces; ++j){
                    if(mine[i]->canmove(theirs[j]->getrow(),theirs[j]->getcol())){
                        if(theirs[j]->getletter() == 'p' || theirs[j]->getletter() == 'P'){
                            captures[j] = 1;
                            //cout << "pawn can be captured by " << turn << endl;
                        }
                        else if(theirs[j]->getletter() == 'r' || theirs[j]->getletter() == 'R'){
                            captures[j] = 6;
                            //cout << "rook can be captured by " << turn << endl;
                        }
                        else if(theirs[j]->getletter() == 'n' || theirs[j]->getletter() == 'N'){
                            captures[j] = 5;
                            //cout << "knight can be captured by " << turn << endl;
                        }
                        else if(theirs[j]->getletter() == 'b' || theirs[j]->getletter() == 'B'){
                            captures[j] = 5;
                            //cout << "bishop can be captured by " << turn << endl;
                        }
                        else if(theirs[j]->getletter() == 'q' || theirs[j]->getletter() == 'Q'){
                            captures[j] = 8;
                            //cout << "queen can be captured by " << turn << endl;
                        }
                        else if(theirs[j]->getletter() == 'k' || theirs[j]->getletter() == 'K'){
                            captures[j] = 10;
                            //cout << "king can be captured by " << turn << endl;
                        }
                        
                    }
                }
            }
            //^ ranking the opponents pieces by capture reward
            // in the array captures[].
            
            int maxcapture = 0;
            int maxcapind = 0;
            int nocaptures = 0;
            for(int i = 0; i < oppieces; ++i){
                //cout << "captures[i] is " << captures[i] << endl;
                if(captures[i] > maxcapture){
                    maxcapind = i;
                }
                if(captures[i] == 0){
                    nocaptures++;
                }
            }
            // ^ finding max capture value and storing index in maxcapind.
                     
            int indexsave = 0;
            if(nocaptures != oppieces){
                for(int i = 0 ; i < numpieces; ++i){
                    cur = "";
                    for(int z = 0; z < numpieces; ++z){
                        if(mine[z]->canmove(theirs[maxcapind]->getrow(),theirs[maxcapind]->getcol())){
                            cur = mine[z]->getcoords();
                            dest = theirs[maxcapind]->getcoords();
                            indexsave = z;
                            break;
                        }
                    }
                    
                    //cout << "reached" << endl; marker
                    //^ finding which piece can capture the enemy.
                    //The piece index for mine is saved in indexsave
                    
                    if(cur != ""){
                        Theboard->notifybeforemoveboard(cur,oppturn);
                        Theboard->notifybeforemoveboard(dest, turn);
                        Theboard->makemove(cur,dest, level);
                        if ((colour=="white"&&turn=="black") ||
                            (colour=="black"&&turn=="white")){
                            lastcoords = dest;
                            for(int l = 0; l < oppieces; ++l){
                                Theboard->notifyaftermoveboard(theirs[l]->getcoords(), originalturn);
                            }
                            return;
                        }
                        else{
                            Theboard->notifyaftermoveboard(cur, oppturn);
                            Theboard->notifyaftermoveboard(dest, turn);
                            maxcapture = 0;
                            captures[maxcapind] = 0;
                            nocaptures = 0;
                            for(int q = 0; q < oppieces; ++q){
                                //cout << "captures[i] is " << captures[i] << endl;
                                if(captures[q] > maxcapture){
                                    maxcapind = q;
                                }
                                if(captures[q] == 0) nocaptures++;
                            }
                            if(nocaptures == oppieces) break;
                            
                        }
                    }
                    else break;
                    //^ moves the piece
                }
            }
        }
        //capturing^
        if(!takenmove){
            int kingcol = otherking->getcol();
            int kingrow = otherking->getrow();
       	    for(int l = 0; l < numpieces; ++l){
                /////////////////////////////// PAWN CHECKKING TO CHECK KING ////////////////////////
        	    if(mine[l]->getletter() == 'p'){
                	if((kingcol == mine[l]->getcol() - 1 && kingrow == mine[l]->getrow()-2) ||
                       (kingcol == mine[l]->getcol() + 1 && kingrow == mine[l]->getrow()-2)){
                        if(mine[l]->canmove(mine[l]->getrow()+1, mine[l]->getcol())){
                            dest+=static_cast<char>(mine[l]->getcol()+'a');
                            dest+=static_cast<char>(mine[l]->getrow()+ 1 + '0');
                            cur = mine[l]->getcoords();
                            Theboard->notifybeforemoveboard(cur,oppturn);
                            Theboard->makemove(cur,dest,level-1);
                            if ((colour=="white"&&turn=="black") ||
                                (colour=="black"&&turn=="white")){
                                lastcoords = dest;
                                Theboard->notifyaftermoveboard(dest, turn);
                                for(int i = 0; i < oppieces; ++i){
                                    Theboard->notifyaftermoveboard(dest, originalturn);
                                }
                                return;
                            }
                            else{
                                Theboard->notifyaftermoveboard(cur, oppturn);
                                Theboard->notifyaftermoveboard(dest, turn);
                            }
                        }
                        
                    }
                }
                if(takenmove) break;
                else if(mine[l]->getletter() == 'P'){
                	if((kingcol == mine[l]->getcol() - 1 && kingrow == mine[l]->getrow()+2) ||
                   	   (kingcol == mine[l]->getcol() + 1 && kingrow == mine[l]->getrow()+2)){
                        if(mine[l]->canmove(mine[l]->getrow()+1, mine[l]->getcol())){
                            dest+=static_cast<char>(mine[l]->getcol()+'a');
                            dest+=static_cast<char>(mine[l]->getrow()+ 1 + '0');
                            cur = mine[l]->getcoords();
                            Theboard->notifybeforemoveboard(cur,oppturn);
                            Theboard->makemove(cur,dest,level-1);
                            if ((colour=="white"&&turn=="black") ||
                                (colour=="black"&&turn=="white")){
                                lastcoords = dest;
                                Theboard->notifyaftermoveboard(dest, turn);
                                for(int i = 0; i < oppieces; ++i){
                                    Theboard->notifyaftermoveboard(dest, originalturn);
                                }
                                return;
                            }
                            else{
                                Theboard->notifyaftermoveboard(cur, oppturn);
                                Theboard->notifyaftermoveboard(dest, turn);
                            }
                        }
                        
                	}
                }
                ////////////////////////////// ROOK CHECKKING TO CHECK KING ////////////////////////
                else if(mine[l]->getletter() == 'r' || mine[l]->getletter() == 'R'){
                    int waystocheck[32];
                    int waysind = 0;
                    for(int i = 2; i < 8; i++){
                        if(kingcol + i > 7 || kingcol + 1 > 7){
                            break;
                        }
                        else if(all[kingrow][kingcol + i]->istype("empty") && all[kingrow][kingcol + 1]->istype("empty")){
                            waystocheck[waysind] = kingrow;
                            waysind++;
                            waystocheck[waysind] = kingcol + i;
                            waysind++;
                        }
                        else break;
                        
                    }
                    //checks going to the right only
                    for(int i = 2; i < 8; i++){
                        if(kingcol - i < 0 || kingcol - 1 < 0){
                            break;
                        }
                        else if(all[kingrow][kingcol - i]->istype("empty") && all[kingrow][kingcol - 1]->istype("empty")){
                            waystocheck[waysind] = kingrow;
                            waysind++;
                            waystocheck[waysind] = kingcol - i;
                            waysind++;
                        }
                        else break;
                        
                    }
                    //checks going to the left only
                    for(int i = 2; i < 8; i++){
                        if(kingrow - i < 0 || kingrow - 1 < 0){
                            break;
                        }
                        else if(all[kingrow - i][kingcol]->istype("empty") && all[kingrow - 1][kingcol]->istype("empty")){
                            waystocheck[waysind] = kingrow - i;
                            waysind++;
                            waystocheck[waysind] = kingcol;
                            waysind++;
                        }
                        else break;
                        
                    }
                    //checks going down only
                    for(int i = 2; i < 8; i++){
                        if(kingrow + i > 7 || kingrow + 1 > 7){
                            break;
                        }
                        else if(all[kingrow + i][kingcol]->istype("empty") && all[kingrow + 1][kingcol]->istype("empty")){
                            waystocheck[waysind] = kingrow + i;
                            waysind++;
                            waystocheck[waysind] = kingcol;
                            waysind++;
                        }
                        else break;
                        
                    }
                    //checks going up only
                    for(int i = 0; i < waysind; i = i + 2){
                        if(mine[l]->canmove(waystocheck[i], waystocheck[i+1])){
                            for(int w = 0; w < oppieces; ++w){
                                if(theirs[w]->canmove(waystocheck[i], waystocheck[i+1])){
                                    otherscanreach = true;
                                    break;
                                }
                            }
                            if(!otherscanreach){
                                //cout << waystocheck[i] << " " << waystocheck[i+1] << endl;
                                dest+=static_cast<char>(waystocheck[i + 1] + 'a');
                                dest+=static_cast<char>(waystocheck[i]+1+'0');
                                cur = mine[l]->getcoords();
                                //cout << "cur is " << cur << " dest is " << dest << endl;
                                Theboard->notifybeforemoveboard(cur,oppturn);
                                Theboard->notifybeforemoveboard(dest, turn);
                                Theboard->makemove(cur,dest,level-1);
                                if ((colour=="white"&&turn=="black") ||
                                    (colour=="black"&&turn=="white")){
                                    lastcoords = dest;
                                    Theboard->notifyaftermoveboard(dest, turn);
                                    
                                    for(int i = 0; i < oppieces; ++i){
                                        Theboard->notifyaftermoveboard(dest, originalturn);
                                    }
                                    return;
                                }
                                else{
                                    Theboard->notifyaftermoveboard(cur, oppturn);
                                    Theboard->notifyaftermoveboard(dest, turn);
                                }
                            }
                        }
                    }
                    if(takenmove) break;
                }
                
                //////////////////////////// Knight CHECKKING TO CHECK KING ////////////////////////
                else if(mine[l]->getletter() == 'n' || mine[l]->getletter() == 'N'){
                    int toking[16];
                    toking[0] = kingrow + 2;
                    toking[1] = kingcol - 1;
                    toking[2] = kingrow + 1;
                    toking[3] = kingcol - 2;
                    toking[4] = kingrow - 1;
                    toking[5] = kingcol - 2;
                    toking[6] = kingrow - 2;
                    toking[7] = kingcol - 1;
                    toking[8] = kingrow - 2;
                    toking[9] = kingcol + 1;
                    toking[10] = kingrow - 1;
                    toking[11] = kingcol + 2;
                    toking[12] = kingrow + 1;
                    toking[13] = kingcol + 2;
                    toking[14] = kingrow + 2;
                    toking[15] = kingcol + 1;
                    for(int i = 0;i < 16; i = i + 2){
                        //cout << "checking toking i = " << i << endl;
                        //cout << "toking[" << i <<"] is " << toking[i] << endl;
                        //cout << "toking[" << (i + 1) <<"+1] is " << toking[i+1] << endl;
                        //cout << "mine[l] row is " << mine[l]->getrow() <<
                        //" col is " << mine[l]->getcol() << endl;
                        if(mine[l]->canmove(toking[i], toking[i+1])){
                            for(int w = 0; w < oppieces; ++w){
                                if(theirs[w]->canmove(toking[i], toking[i+1])){
                                    otherscanreach = true;
                                    break;
                                }
                            }
                            if(!otherscanreach){
                                //cout << waystocheck[i] << " " << waystocheck[i+1] << endl;
                                dest+=static_cast<char>(toking[i + 1] + 'a');
                                dest+=static_cast<char>(toking[i]+1+'0');
                                cur = mine[l]->getcoords();
                                //cout << "cur is " << cur << " dest is " << dest << endl;
                                Theboard->notifybeforemoveboard(cur,oppturn);
                                Theboard->makemove(cur,dest,level-1);
                                if ((colour=="white"&&turn=="black") ||
                                    (colour=="black"&&turn=="white")){
                                    lastcoords = dest;
                                    Theboard->notifyaftermoveboard(dest, turn);
                                    for(int i = 0; i < oppieces; ++i){
                                        Theboard->notifyaftermoveboard(dest, originalturn);
                                    }
                                    return;
                                }
                                else{
                                    Theboard->notifyaftermoveboard(cur, oppturn);
                                }
                            }
                        }
                    }
                }
                
                //////////////////////////// Bishop CHECKKING TO CHECK KING ////////////////////////
                else if(mine[l]->getletter() == 'b' || mine[l]->getletter() == 'B'){
                    int kingdiag1[32];
                    int kingdiag1index = 0;
                    
                    for(int i = 2; i < 8; i++){
                        if(kingcol + i > 7 || kingrow + i > 7 || kingcol + 1 > 7 || kingrow + 1 > 7){
                            break;
                        }
                        else if(all[kingrow + i][kingcol + i]->istype("empty") && all[kingrow + 1][kingcol + 1]->istype("empty")){
                            kingdiag1[kingdiag1index] = kingrow + i;
                            kingdiag1index++;
                            kingdiag1[kingdiag1index] = kingcol + i;
                            kingdiag1index++;
                        }
                        else break;
                        
                    }
                    //checks going up and to the right
                    for(int i = 2; i < 8; i++){
                        if(kingcol + i > 7 || kingrow - i < 0 || kingcol + 1 > 7 || kingrow - 1 < 0){
                            break;
                        }
                        else if(all[kingrow - i][kingcol + i]->istype("empty") && all[kingrow - 1][kingcol + 1]->istype("empty")){
                            kingdiag1[kingdiag1index] = kingrow - i;
                            kingdiag1index++;
                            kingdiag1[kingdiag1index] = kingcol + i;
                            kingdiag1index++;
                        }
                        else break;
                        
                    }
                    //checks going down and to the right
                    for(int i = 2; i < 8; i++){
                        if(kingcol - i < 0 || kingrow - i < 0 || kingcol - 1 < 0 || kingrow - 1 < 0){
                            break;
                        }
                        else if(all[kingrow - i][kingcol - i]->istype("empty") && all[kingrow - 1][kingcol - 1]->istype("empty")){
                            kingdiag1[kingdiag1index] = kingrow - i;
                            kingdiag1index++;
                            kingdiag1[kingdiag1index] = kingcol - i;
                            kingdiag1index++;
                        }
                        else break;
                        
                    }
                    //checks going down and to the left
                    for(int i = 2; i < 8; i++){
                        if(kingcol - i < 0 || kingrow + i > 7 || kingcol - 1 < 0 || kingrow + 1 > 7){
                            break;
                        }
                        else if(all[kingrow + i][kingcol - i]->istype("empty") && all[kingrow + 1][kingcol - 1]->istype("empty")){
                            kingdiag1[kingdiag1index] = kingrow + i;
                            kingdiag1index++;
                            kingdiag1[kingdiag1index] = kingcol - i;
                            kingdiag1index++;
                        }
                        else break;
                        
                    }
                    //checks going up and to the left
                    for(int i = 0; i < kingdiag1index; i = i + 2){
                        if(mine[l]->canmove(kingdiag1[i], kingdiag1[i+1])){
                            for(int w = 0; w < oppieces; ++w){
                                if(theirs[w]->canmove(kingdiag1[i], kingdiag1[i+1])){
                                    otherscanreach = true;
                                    break;
                                }
                            }
                            if(!otherscanreach){
                                //cout << waystocheck[i] << " " << waystocheck[i+1] << endl;
                                dest+=static_cast<char>(kingdiag1[i + 1] + 'a');
                                dest+=static_cast<char>(kingdiag1[i]+1+'0');
                                cur = mine[l]->getcoords();
                                //cout << "cur is " << cur << " dest is " << dest << endl;
                                Theboard->notifybeforemoveboard(cur,oppturn);
                                Theboard->makemove(cur,dest,level-1);
                                if ((colour=="white"&&turn=="black") ||
                                    (colour=="black"&&turn=="white")){
                                    lastcoords = dest;
                                    Theboard->notifyaftermoveboard(dest, turn);
                                    for(int i = 0; i < oppieces; ++i){
                                        Theboard->notifyaftermoveboard(dest, originalturn);
                                    }
                                    return;
                                }
                                else{
                                    Theboard->notifyaftermoveboard(cur, oppturn);
                                }
                            }
                        }
                    }
                    
                }
                
                //////////////////////////// Queen CHECKKING TO CHECK KING ////////////////////////
                else if(mine[l]->getletter() == 'q' || mine[l]->getletter() == 'Q'){
                    int waystocheck[128];
                    int waysind = 0;
                    if(true){
                        for(int i = 2; i < 8; i++){
                            if(kingcol + i > 7 || kingrow + i > 7 || kingcol + 1 > 7 || kingrow + 1 > 7){
                                break;
                            }
                            else if(all[kingrow + i][kingcol + i]->istype("empty") && all[kingrow + 1][kingcol + 1]->istype("empty")){
                                waystocheck[waysind] = kingrow + i;
                                waysind++;
                                waystocheck[waysind] = kingcol + i;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going up and to the right
                        for(int i = 2; i < 8; i++){
                            if(kingcol + i > 7 || kingrow - i < 0 || kingcol + 1 > 7 || kingrow - 1 < 0){
                                break;
                            }
                            else if(all[kingrow - i][kingcol + i]->istype("empty") && all[kingrow - 1][kingcol + 1]->istype("empty")){
                                waystocheck[waysind] = kingrow - i;
                                waysind++;
                                waystocheck[waysind] = kingcol + i;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going down and to the right
                        for(int i = 2; i < 8; i++){
                            if(kingcol - i < 0 || kingrow - i < 0 || kingcol - 1 < 0 || kingrow - 1 < 0){
                                break;
                            }
                            else if(all[kingrow - i][kingcol - i]->istype("empty") && all[kingrow - 1][kingcol - 1]->istype("empty")){
                                waystocheck[waysind] = kingrow - i;
                                waysind++;
                                waystocheck[waysind] = kingcol - i;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going down and to the left
                        for(int i = 2; i < 8; i++){
                            if(kingcol - i < 0 || kingrow + i > 7 || kingcol - 1 < 0 || kingrow + 1 > 7){
                                break;
                            }
                            else if(all[kingrow + i][kingcol - i]->istype("empty") && all[kingrow + 1][kingcol - 1]->istype("empty")){
                                waystocheck[waysind] = kingrow + i;
                                waysind++;
                                waystocheck[waysind] = kingcol - i;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going up and to the left
                        for(int i = 2; i < 8; i++){
                            if(kingcol + i > 7 || kingcol + 1 > 7){
                                break;
                            }
                            else if(all[kingrow][kingcol + i]->istype("empty") && all[kingrow][kingcol + 1]->istype("empty")){
                                waystocheck[waysind] = kingrow;
                                waysind++;
                                waystocheck[waysind] = kingcol + i;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going to the right only
                        for(int i = 2; i < 8; i++){
                            if(kingcol - i < 0 || kingcol - 1 < 0){
                                break;
                            }
                            else if(all[kingrow][kingcol - i]->istype("empty") && all[kingrow][kingcol - 1]->istype("empty")){
                                waystocheck[waysind] = kingrow;
                                waysind++;
                                waystocheck[waysind] = kingcol - i;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going to the left only
                        for(int i = 2; i < 8; i++){
                            if(kingrow - i < 0 || kingrow - 1 < 0){
                                break;
                            }
                            else if(all[kingrow - i][kingcol]->istype("empty") && all[kingrow - 1][kingcol]->istype("empty")){
                                waystocheck[waysind] = kingrow - i;
                                waysind++;
                                waystocheck[waysind] = kingcol;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going down only
                        for(int i = 2; i < 8; i++){
                            if(kingrow + i > 7 || kingrow + 1 > 7){
                                break;
                            }
                            else if(all[kingrow + i][kingcol]->istype("empty") && all[kingrow + 1][kingcol]->istype("empty")){
                                waystocheck[waysind] = kingrow + i;
                                waysind++;
                                waystocheck[waysind] = kingcol;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going up only
                    }
                    for(int i = 0; i < waysind; i = i + 2){
                        if(mine[l]->canmove(waystocheck[i], waystocheck[i+1])){
                            for(int w = 0; w < oppieces; ++w){
                                if(theirs[w]->canmove(waystocheck[i], waystocheck[i+1])){
                                    otherscanreach = true;
                                    break;
                                }
                            }
                            if(!otherscanreach){
                                //cout << waystocheck[i] << " " << waystocheck[i+1] << endl;
                                dest+=static_cast<char>(waystocheck[i + 1] + 'a');
                                dest+=static_cast<char>(waystocheck[i]+1+'0');
                                cur = mine[l]->getcoords();
                                //cout << "cur is " << cur << " dest is " << dest << endl;
                                Theboard->notifybeforemoveboard(cur,oppturn);
                                Theboard->makemove(cur,dest,level-1);
                                if ((colour=="white"&&turn=="black") ||
                                    (colour=="black"&&turn=="white")){
                                    lastcoords = dest;
                                    Theboard->notifyaftermoveboard(dest, turn);
                                    for(int i = 0; i < oppieces; ++i){
                                        Theboard->notifyaftermoveboard(dest, originalturn);
                                    }
                                    return;
                                }
                                else{
                                    Theboard->notifyaftermoveboard(cur, oppturn);
                                }
                            }
                        }
                    }
                }
                //////////////////////////// Done with doing the checkking ////////////////////////
            }
        }
        //^ checkking the king
        
        if(!takenmove){
        int movedpieces[numpieces];
        for(int i = 0; i < numpieces; ++i){
            movedpieces[i] = 0;
        }
        
        for(int k = 0; k < numpieces; ++k){
            while(movedpieces[move_piece] == 1){
                move_piece = rand() % numpieces;
            }
            cur = mine[move_piece]->getcoords();
        	for(int i = 0; i < 1000; ++i){
                int r2 = rand() % 8;
                int c2 = rand() % 8;
                dest+=static_cast<char>(c2+'a');
                dest+=static_cast<char>(r2+'1');
                if(mine[move_piece]->canmove(r2, c2)){
                    Theboard->notifybeforemoveboard(cur,oppturn);
                    Theboard->makemove(cur,dest,level-1);
                    if ((colour=="white"&&turn=="black") ||
                        (colour=="black"&&turn=="white")){
                        lastcoords = dest;
                        Theboard->notifyaftermoveboard(dest, turn);
                        for(int i = 0; i < oppieces; ++i){
                            Theboard->notifyaftermoveboard(dest, originalturn);
                        }
                        return;
                    }
                    else{
                        Theboard->notifyaftermoveboard(cur, oppturn);
                        Theboard->notifyaftermoveboard(dest, turn);
                    }
                }
                dest="";
            }
            movedpieces[move_piece] = 1;
        }
        
        for(int k = 0; k < numpieces; ++k){
            cur = mine[k]->getcoords();
            for (int r2=0; r2< 8; r2++){
                for (int c2=0; c2< 8; c2++){
                    dest+=static_cast<char>(c2+'a');
                    dest+=static_cast<char>(r2+'1');
                    if(mine[k]->canmove(r2, c2)){
                        Theboard->notifybeforemoveboard(cur,oppturn);
                        Theboard->makemove(cur,dest,level-1);
                        if ((colour=="white"&&turn=="black") ||
                            (colour=="black"&&turn=="white")){
                            lastcoords = dest;
                            Theboard->notifyaftermoveboard(dest, turn);
                            for(int i = 0; i < oppieces; ++i){
                                Theboard->notifyaftermoveboard(dest, originalturn);
                            }
                            return;
                        }
                        else{
                            Theboard->notifyaftermoveboard(cur, oppturn);
                            Theboard->notifyaftermoveboard(dest, turn);
                        }
                    }
                    dest="";
                }
            }
        }
        // ^ defending -> the random moves -> then brute force
    }
    }
    /////////////////////////////////////////// LEVEL 3 ///////////////////////////////////
    else if(level == 3){
        
        //^ Putting their pieces in theirs.
        //setting pointer to other king *otherking
        
        if(!takenmove){
            int dangers[numpieces];
            for(int i = 0; i < numpieces; i++){
                if(mine[i]->indanger() > 0 &&
                   (mine[i]->getletter() == 'p' || mine[i]->getletter() == 'P'))
                {
                    dangers[i] = 1;
                }
                else if(mine[i]->indanger() > 0 &&
                        (mine[i]->getletter() == 'R' || mine[i]->getletter() == 'r')){
                    dangers[i] = 5;
                }
                else if(mine[i]->indanger() > 0 &&
                        (mine[i]->getletter() == 'N' || mine[i]->getletter() == 'n'))
                {
                    dangers[i] = 4;
                }
                else if(mine[i]->indanger() > 0 &&
                        (mine[i]->getletter() == 'B' || mine[i]->getletter() == 'b'))
                {
                    dangers[i] = 4;
                }
                else if(mine[i]->indanger() > 0 &&
                        (mine[i]->getletter() == 'K' || mine[i]->getletter() == 'k'))
                {
                    dangers[i] = 10;
                }
                else if(mine[i]->indanger() > 0 &&
                        (mine[i]->getletter() == 'Q' || mine[i]->getletter() == 'q'))
                {
                    dangers[i] = 8;
                }
                else dangers[i] = 0;
                
            }
            //^ setting dangers in dangers array
            
            
            int max = 0;
            int maxindex = 0;
            int nodangers = 0;
            for(int i = 0; i < numpieces; ++i){
                if(max <= dangers[i]){
                    max = dangers[i];
                    maxindex = i;
                }
                if(dangers[i] == 0) nodangers++;
            }
            cout << "nodangers is " << nodangers << endl;
            cout << "numpieces is " << numpieces << endl;
            if(nodangers != numpieces){
                for(int k = 0; k < numpieces; ++k){
                    cur = mine[maxindex]->getcoords();
                    cerr << "Trying to move " << mine[maxindex]->getletter() << endl;
                    for(int i = 0; i < 200; ++i){
                        int r2 = rand() % 8;
                        int c2 = rand() % 8;
                        dest+=static_cast<char>(c2+'a');
                        dest+=static_cast<char>(r2+'1');
                        if(mine[move_piece]->canmove(r2, c2)){
                            Theboard->notifybeforemoveboard(cur, oppturn);
                            Theboard->notifybeforemoveboard(dest, turn);
                            Theboard->makemove(cur, dest, level);
                            if ((colour=="white"&&turn=="black") ||
                                (colour=="black"&&turn=="white")){
                                Theboard->notifyaftermoveboard(dest, turn);
                                lastcoords = dest;
                                for(int i = 0; i < oppieces; ++i){
                                    Theboard->notifyaftermoveboard(theirs[i]->getcoords(),originalturn);
                                }
                                return;
                            }
                            else{
                                Theboard->notifyaftermoveboard(cur, oppturn);
                                Theboard->notifyaftermoveboard(dest, turn);
                            }
                        }
                        dest="";
                    }
                    nodangers = 0;
                    dangers[maxindex] = 0;
                    max = 0;
                    for(int i = 0; i < numpieces; ++i){
                        if(max <= dangers[i]){
                            max = dangers[i];
                            maxindex = i;
                        }
                        if(dangers[i] == 0) nodangers++;
                    }
                    if(nodangers == numpieces) break;
                }
            }
            int movedpieces[numpieces];
            for(int i = 0; i < numpieces; ++i){
                movedpieces[i] = 0;
            }
            move_piece = rand() % numpieces;
            for(int k = 0; k < numpieces; ++k){
                while(movedpieces[move_piece] != 0){
                    move_piece = rand() % numpieces;
                }
                cur = mine[move_piece]->getcoords();
                cout << "Trying to randomly move " << mine[move_piece]->getletter() << endl;
                for(int i = 0; i < 1000; i++){
                    int r2 = rand()%8;
                    int c2 = rand()%8;
                    dest+=static_cast<char>(c2+'a');
                    dest+=static_cast<char>(r2+'1');
                    if(mine[move_piece]->canmove(r2, c2)){
                        Theboard->notifybeforemoveboard(cur, oppturn);
                        Theboard->notifybeforemoveboard(dest, turn);
                        Theboard->makemove(cur, dest, level);
                        if ((colour=="white"&&turn=="black") ||
                            (colour=="black"&&turn=="white")){
                            Theboard->notifyaftermoveboard(dest, turn);
                            lastcoords = dest;
                            for(int i = 0; i < oppieces; ++i){
                                Theboard->notifyaftermoveboard(theirs[i]->getcoords(),originalturn);
                            }
                            return;
                        }
                        else{
                            Theboard->notifyaftermoveboard(cur, oppturn);
                            Theboard->notifyaftermoveboard(dest, turn);
                        }
                    }
                    dest = "";
                }
            }
            for(int k = 0; k < numpieces; ++k){
                cur = mine[k]->getcoords();
                for (int r2=0; r2< 8; r2++){
                    for (int c2=0; c2< 8; c2++){
                        dest+=static_cast<char>(c2+'a');
                        dest+=static_cast<char>(r2+'1');
                        if(mine[k]->canmove(r2, c2)){
                            Theboard->notifybeforemoveboard(cur,oppturn);
                            Theboard->makemove(cur,dest,level-1);
                            if ((colour=="white"&&turn=="black") ||
                                (colour=="black"&&turn=="white")){
                                lastcoords = dest;
                                Theboard->notifyaftermoveboard(dest, turn);
                                for(int i = 0; i < oppieces; ++i){
                                    Theboard->notifyaftermoveboard(dest, originalturn);
                                }
                                return;
                            }
                            else{
                                Theboard->notifyaftermoveboard(cur, oppturn);
                                Theboard->notifyaftermoveboard(dest, turn);
                            }
                        }
                        dest="";
                    }
                }
            }
        }
        cout << "passed defending" << endl;
        if(!takenmove){
                    //cout << "oppieces is " << oppieces << endl;
                    int captures[oppieces];
                    for(int i = 0; i < oppieces; ++i){
                        captures[i] = 0;
                    }
                    // ^ declaring a new array to store the reward of capturing pieces.
                    
                    for(int i = 0; i < numpieces; ++i){
                        for(int j = 0; j < oppieces; ++j){
                            if(mine[i]->canmove(theirs[j]->getrow(),theirs[j]->getcol())){
                                if(theirs[j]->getletter() == 'p' || theirs[j]->getletter() == 'P'){
                                    captures[j] = 1;
                                    //cout << "pawn can be captured by " << turn << endl;
                                }
                                else if(theirs[j]->getletter() == 'r' || theirs[j]->getletter() == 'R'){
                                    captures[j] = 6;
                                    //cout << "rook can be captured by " << turn << endl;
                                }
                                else if(theirs[j]->getletter() == 'n' || theirs[j]->getletter() == 'N'){
                                    captures[j] = 5;
                                    //cout << "knight can be captured by " << turn << endl;
                                }
                                else if(theirs[j]->getletter() == 'b' || theirs[j]->getletter() == 'B'){
                                    captures[j] = 5;
                                    //cout << "bishop can be captured by " << turn << endl;
                                }
                                else if(theirs[j]->getletter() == 'q' || theirs[j]->getletter() == 'Q'){
                                    captures[j] = 8;
                                    //cout << "queen can be captured by " << turn << endl;
                                }
                                else if(theirs[j]->getletter() == 'k' || theirs[j]->getletter() == 'K'){
                                    captures[j] = 10;
                                    //cout << "king can be captured by " << turn << endl;
                                }
                            }
                            
                        }
                    }
                    //^ ranking the opponents pieces by capture reward
                    // in the array captures[].
                    
                    int maxcapture = 0;
                    int maxcapind = 0;
                    int nocaptures = 0;
                    for(int i = 0; i < oppieces; ++i){
                        //cout << "captures[i] is " << captures[i] << endl;
                        if(captures[i] > maxcapture){
                            maxcapind = i;
                        }
                        if(captures[i] == 0){
                            nocaptures++;
                        }
                    }
                    // ^ finding max capture value and storing index in maxcapind.
                    
                    
                    int indexsave = 0;
                    if(nocaptures != oppieces){
                        for(int i = 0 ; i < numpieces; ++i){
                            cur = "";
                            for(int w = 0; w < numpieces; ++w){
                                if(mine[w]->canmove(theirs[maxcapind]->getrow(),theirs[maxcapind]->getcol())){
                                    cur = mine[w]->getcoords();
                                    dest = theirs[maxcapind]->getcoords();
                                    indexsave = w;
                                    break;
                                }
                            }
                    //cout << "reached" << endl; marker
                    //^ finding which piece can capture the enemy.
                    //The piece index for mine is saved in indexsave
                    
                            if(cur != ""){
                                 for(int w = 0; w < oppieces; ++w){
                                    if(theirs[w]->canmove(theirs[maxcapind]->getrow(), theirs[maxcapind]->getcol())){
                                    otherscanreach = true;
                                    break;
                                    }
                                 }
                                 if(!otherscanreach){
                                    //cout << "cur is " << cur << " dest is " << dest << endl;
                                    Theboard->notifybeforemoveboard(cur,oppturn);
                                    Theboard->makemove(cur,dest,level-1);
                                    if ((colour=="white"&&turn=="black") ||
                                        (colour=="black"&&turn=="white")){
                                        lastcoords = dest;
                                        Theboard->notifyaftermoveboard(dest, turn);
                                        for(int i = 0; i < oppieces; ++i){
                                            Theboard->notifyaftermoveboard(dest, originalturn);
                                        }
                                        return;
                                    }
                                    else{
                                        Theboard->notifyaftermoveboard(cur, oppturn);
                                        Theboard->notifyaftermoveboard(dest, turn);
                                        maxcapture = 0;
                                        captures[maxcapind] = 0;
                                        nocaptures = 0;
                                        for(int i = 0; i < oppieces; ++i){
                                            if(captures[i] > maxcapture){
                                                maxcapind = i;
                                            }
                                            if(captures[i] == 0) nocaptures++;
                                        }
                                        if(nocaptures == oppieces) break;
                                     }
                                 }
                            }
                            else break;
                        }
                    }
                }
        cout << "passed capturing" << endl;
        if(!takenmove){
            int kingcol = otherking->getcol();
            int kingrow = otherking->getrow();
       	    for(int l = 0; l < numpieces; ++l){
                /////////////////////////////// PAWN CHECKKING TO CHECK KING ////////////////////////
        	    if(mine[l]->getletter() == 'p'){
                	if((kingcol == mine[l]->getcol() - 1 && kingrow == mine[l]->getrow()-2) ||
                       (kingcol == mine[l]->getcol() + 1 && kingrow == mine[l]->getrow()-2)){
                        if(mine[l]->canmove(mine[l]->getrow()+1, mine[l]->getcol())){
                            dest+=static_cast<char>(mine[l]->getcol()+'a');
                            dest+=static_cast<char>(mine[l]->getrow()+ 1 + '0');
                            cur = mine[l]->getcoords();
                            Theboard->notifybeforemoveboard(cur,oppturn);
                            Theboard->makemove(cur,dest,level-1);
                            if ((colour=="white"&&turn=="black") ||
                                (colour=="black"&&turn=="white")){
                                lastcoords = dest;
                                Theboard->notifyaftermoveboard(dest, turn);
                                for(int i = 0; i < oppieces; ++i){
                                    Theboard->notifyaftermoveboard(dest, originalturn);
                                }
                                return;
                            }
                            else{
                                Theboard->notifyaftermoveboard(cur, oppturn);
                                Theboard->notifyaftermoveboard(dest, turn);
                            }
                        }
                        
                    }
                }
                if(takenmove) break;
                else if(mine[l]->getletter() == 'P'){
                	if((kingcol == mine[l]->getcol() - 1 && kingrow == mine[l]->getrow()+2) ||
                   	   (kingcol == mine[l]->getcol() + 1 && kingrow == mine[l]->getrow()+2)){
                        if(mine[l]->canmove(mine[l]->getrow()+1, mine[l]->getcol())){
                            dest+=static_cast<char>(mine[l]->getcol()+'a');
                            dest+=static_cast<char>(mine[l]->getrow()+ 1 + '0');
                            cur = mine[l]->getcoords();
                            Theboard->notifybeforemoveboard(cur,oppturn);
                            Theboard->makemove(cur,dest,level-1);
                            if ((colour=="white"&&turn=="black") ||
                                (colour=="black"&&turn=="white")){
                                lastcoords = dest;
                                Theboard->notifyaftermoveboard(dest, turn);
                                for(int i = 0; i < oppieces; ++i){
                                    Theboard->notifyaftermoveboard(dest, originalturn);
                                }
                                return;
                            }
                            else{
                                Theboard->notifyaftermoveboard(cur, oppturn);
                                Theboard->notifyaftermoveboard(dest, turn);
                            }
                        }
                        
                	}
                }
                ////////////////////////////// ROOK CHECKKING TO CHECK KING ////////////////////////
                else if(mine[l]->getletter() == 'r' || mine[l]->getletter() == 'R'){
                    int waystocheck[32];
                    int waysind = 0;
                    for(int i = 2; i < 8; i++){
                        if(kingcol + i > 7 || kingcol + 1 > 7){
                            break;
                        }
                        else if(all[kingrow][kingcol + i]->istype("empty") && all[kingrow][kingcol + 1]->istype("empty")){
                            waystocheck[waysind] = kingrow;
                            waysind++;
                            waystocheck[waysind] = kingcol + i;
                            waysind++;
                        }
                        else break;
                        
                    }
                    //checks going to the right only
                    for(int i = 2; i < 8; i++){
                        if(kingcol - i < 0 || kingcol - 1 < 0){
                            break;
                        }
                        else if(all[kingrow][kingcol - i]->istype("empty") && all[kingrow][kingcol - 1]->istype("empty")){
                            waystocheck[waysind] = kingrow;
                            waysind++;
                            waystocheck[waysind] = kingcol - i;
                            waysind++;
                        }
                        else break;
                        
                    }
                    //checks going to the left only
                    for(int i = 2; i < 8; i++){
                        if(kingrow - i < 0 || kingrow - 1 < 0){
                            break;
                        }
                        else if(all[kingrow - i][kingcol]->istype("empty") && all[kingrow - 1][kingcol]->istype("empty")){
                            waystocheck[waysind] = kingrow - i;
                            waysind++;
                            waystocheck[waysind] = kingcol;
                            waysind++;
                        }
                        else break;
                        
                    }
                    //checks going down only
                    for(int i = 2; i < 8; i++){
                        if(kingrow + i > 7 || kingrow + 1 > 7){
                            break;
                        }
                        else if(all[kingrow + i][kingcol]->istype("empty") && all[kingrow + 1][kingcol]->istype("empty")){
                            waystocheck[waysind] = kingrow + i;
                            waysind++;
                            waystocheck[waysind] = kingcol;
                            waysind++;
                        }
                        else break;
                        
                    }
                    //checks going up only
                    for(int i = 0; i < waysind; i = i + 2){
                        if(mine[l]->canmove(waystocheck[i], waystocheck[i+1])){
                            for(int w = 0; w < oppieces; ++w){
                                if(theirs[w]->canmove(waystocheck[i], waystocheck[i+1])){
                                    otherscanreach = true;
                                    break;
                                }
                            }
                            if(!otherscanreach){
                                //cout << waystocheck[i] << " " << waystocheck[i+1] << endl;
                                dest+=static_cast<char>(waystocheck[i + 1] + 'a');
                                dest+=static_cast<char>(waystocheck[i]+1+'0');
                                cur = mine[l]->getcoords();
                                //cout << "cur is " << cur << " dest is " << dest << endl;
                                Theboard->notifybeforemoveboard(cur,oppturn);
                                Theboard->notifybeforemoveboard(dest, turn);
                                Theboard->makemove(cur,dest,level-1);
                                if ((colour=="white"&&turn=="black") ||
                                    (colour=="black"&&turn=="white")){
                                    lastcoords = dest;
                                    Theboard->notifyaftermoveboard(dest, turn);
                                    
                                    for(int i = 0; i < oppieces; ++i){
                                        Theboard->notifyaftermoveboard(dest, originalturn);
                                    }
                                    return;
                                }
                                else{
                                    Theboard->notifyaftermoveboard(cur, oppturn);
                                    Theboard->notifyaftermoveboard(dest, turn);
                                }
                            }
                        }
                    }
                    if(takenmove) break;
                }
                
                //////////////////////////// Knight CHECKKING TO CHECK KING ////////////////////////
                else if(mine[l]->getletter() == 'n' || mine[l]->getletter() == 'N'){
                    int toking[16];
                    toking[0] = kingrow + 2;
                    toking[1] = kingcol - 1;
                    toking[2] = kingrow + 1;
                    toking[3] = kingcol - 2;
                    toking[4] = kingrow - 1;
                    toking[5] = kingcol - 2;
                    toking[6] = kingrow - 2;
                    toking[7] = kingcol - 1;
                    toking[8] = kingrow - 2;
                    toking[9] = kingcol + 1;
                    toking[10] = kingrow - 1;
                    toking[11] = kingcol + 2;
                    toking[12] = kingrow + 1;
                    toking[13] = kingcol + 2;
                    toking[14] = kingrow + 2;
                    toking[15] = kingcol + 1;
                    for(int i = 0;i < 16; i = i + 2){
                        //cout << "checking toking i = " << i << endl;
                        //cout << "toking[" << i <<"] is " << toking[i] << endl;
                        //cout << "toking[" << (i + 1) <<"+1] is " << toking[i+1] << endl;
                        //cout << "mine[l] row is " << mine[l]->getrow() <<
                        //" col is " << mine[l]->getcol() << endl;
                        if(mine[l]->canmove(toking[i], toking[i+1])){
                            for(int w = 0; w < oppieces; ++w){
                                if(theirs[w]->canmove(toking[i], toking[i+1])){
                                    otherscanreach = true;
                                    break;
                                }
                            }
                            if(!otherscanreach){
                                //cout << waystocheck[i] << " " << waystocheck[i+1] << endl;
                                dest+=static_cast<char>(toking[i + 1] + 'a');
                                dest+=static_cast<char>(toking[i]+1+'0');
                                cur = mine[l]->getcoords();
                                //cout << "cur is " << cur << " dest is " << dest << endl;
                                Theboard->notifybeforemoveboard(cur,oppturn);
                                Theboard->makemove(cur,dest,level-1);
                                if ((colour=="white"&&turn=="black") ||
                                    (colour=="black"&&turn=="white")){
                                    lastcoords = dest;
                                    Theboard->notifyaftermoveboard(dest, turn);
                                    for(int i = 0; i < oppieces; ++i){
                                        Theboard->notifyaftermoveboard(dest, originalturn);
                                    }
                                    return;
                                }
                                else{
                                    Theboard->notifyaftermoveboard(cur, oppturn);
                                }
                            }
                        }
                    }
                }
                
                //////////////////////////// Bishop CHECKKING TO CHECK KING ////////////////////////
                else if(mine[l]->getletter() == 'b' || mine[l]->getletter() == 'B'){
                    int kingdiag1[32];
                    int kingdiag1index = 0;
                    
                    for(int i = 2; i < 8; i++){
                        if(kingcol + i > 7 || kingrow + i > 7 || kingcol + 1 > 7 || kingrow + 1 > 7){
                            break;
                        }
                        else if(all[kingrow + i][kingcol + i]->istype("empty") && all[kingrow + 1][kingcol + 1]->istype("empty")){
                            kingdiag1[kingdiag1index] = kingrow + i;
                            kingdiag1index++;
                            kingdiag1[kingdiag1index] = kingcol + i;
                            kingdiag1index++;
                        }
                        else break;
                        
                    }
                    //checks going up and to the right
                    for(int i = 2; i < 8; i++){
                        if(kingcol + i > 7 || kingrow - i < 0 || kingcol + 1 > 7 || kingrow - 1 < 0){
                            break;
                        }
                        else if(all[kingrow - i][kingcol + i]->istype("empty") && all[kingrow - 1][kingcol + 1]->istype("empty")){
                            kingdiag1[kingdiag1index] = kingrow - i;
                            kingdiag1index++;
                            kingdiag1[kingdiag1index] = kingcol + i;
                            kingdiag1index++;
                        }
                        else break;
                        
                    }
                    //checks going down and to the right
                    for(int i = 2; i < 8; i++){
                        if(kingcol - i < 0 || kingrow - i < 0 || kingcol - 1 < 0 || kingrow - 1 < 0){
                            break;
                        }
                        else if(all[kingrow - i][kingcol - i]->istype("empty") && all[kingrow - 1][kingcol - 1]->istype("empty")){
                            kingdiag1[kingdiag1index] = kingrow - i;
                            kingdiag1index++;
                            kingdiag1[kingdiag1index] = kingcol - i;
                            kingdiag1index++;
                        }
                        else break;
                        
                    }
                    //checks going down and to the left
                    for(int i = 2; i < 8; i++){
                        if(kingcol - i < 0 || kingrow + i > 7 || kingcol - 1 < 0 || kingrow + 1 > 7){
                            break;
                        }
                        else if(all[kingrow + i][kingcol - i]->istype("empty") && all[kingrow + 1][kingcol - 1]->istype("empty")){
                            kingdiag1[kingdiag1index] = kingrow + i;
                            kingdiag1index++;
                            kingdiag1[kingdiag1index] = kingcol - i;
                            kingdiag1index++;
                        }
                        else break;
                        
                    }
                    //checks going up and to the left
                    for(int i = 0; i < kingdiag1index; i = i + 2){
                        if(mine[l]->canmove(kingdiag1[i], kingdiag1[i+1])){
                            for(int w = 0; w < oppieces; ++w){
                                if(theirs[w]->canmove(kingdiag1[i], kingdiag1[i+1])){
                                    otherscanreach = true;
                                    break;
                                }
                            }
                            if(!otherscanreach){
                                //cout << waystocheck[i] << " " << waystocheck[i+1] << endl;
                                dest+=static_cast<char>(kingdiag1[i + 1] + 'a');
                                dest+=static_cast<char>(kingdiag1[i]+1+'0');
                                cur = mine[l]->getcoords();
                                //cout << "cur is " << cur << " dest is " << dest << endl;
                                Theboard->notifybeforemoveboard(cur,oppturn);
                                Theboard->makemove(cur,dest,level-1);
                                if ((colour=="white"&&turn=="black") ||
                                    (colour=="black"&&turn=="white")){
                                    lastcoords = dest;
                                    Theboard->notifyaftermoveboard(dest, turn);
                                    for(int i = 0; i < oppieces; ++i){
                                        Theboard->notifyaftermoveboard(dest, originalturn);
                                    }
                                    return;
                                }
                                else{
                                    Theboard->notifyaftermoveboard(cur, oppturn);
                                }
                            }
                        }
                    }
                    
                }
                
                //////////////////////////// Queen CHECKKING TO CHECK KING ////////////////////////
                else if(mine[l]->getletter() == 'q' || mine[l]->getletter() == 'Q'){
                    int waystocheck[128];
                    int waysind = 0;
                    if(true){
                        for(int i = 2; i < 8; i++){
                            if(kingcol + i > 7 || kingrow + i > 7 || kingcol + 1 > 7 || kingrow + 1 > 7){
                                break;
                            }
                            else if(all[kingrow + i][kingcol + i]->istype("empty") && all[kingrow + 1][kingcol + 1]->istype("empty")){
                                waystocheck[waysind] = kingrow + i;
                                waysind++;
                                waystocheck[waysind] = kingcol + i;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going up and to the right
                        for(int i = 2; i < 8; i++){
                            if(kingcol + i > 7 || kingrow - i < 0 || kingcol + 1 > 7 || kingrow - 1 < 0){
                                break;
                            }
                            else if(all[kingrow - i][kingcol + i]->istype("empty") && all[kingrow - 1][kingcol + 1]->istype("empty")){
                                waystocheck[waysind] = kingrow - i;
                                waysind++;
                                waystocheck[waysind] = kingcol + i;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going down and to the right
                        for(int i = 2; i < 8; i++){
                            if(kingcol - i < 0 || kingrow - i < 0 || kingcol - 1 < 0 || kingrow - 1 < 0){
                                break;
                            }
                            else if(all[kingrow - i][kingcol - i]->istype("empty") && all[kingrow - 1][kingcol - 1]->istype("empty")){
                                waystocheck[waysind] = kingrow - i;
                                waysind++;
                                waystocheck[waysind] = kingcol - i;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going down and to the left
                        for(int i = 2; i < 8; i++){
                            if(kingcol - i < 0 || kingrow + i > 7 || kingcol - 1 < 0 || kingrow + 1 > 7){
                                break;
                            }
                            else if(all[kingrow + i][kingcol - i]->istype("empty") && all[kingrow + 1][kingcol - 1]->istype("empty")){
                                waystocheck[waysind] = kingrow + i;
                                waysind++;
                                waystocheck[waysind] = kingcol - i;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going up and to the left
                        for(int i = 2; i < 8; i++){
                            if(kingcol + i > 7 || kingcol + 1 > 7){
                                break;
                            }
                            else if(all[kingrow][kingcol + i]->istype("empty") && all[kingrow][kingcol + 1]->istype("empty")){
                                waystocheck[waysind] = kingrow;
                                waysind++;
                                waystocheck[waysind] = kingcol + i;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going to the right only
                        for(int i = 2; i < 8; i++){
                            if(kingcol - i < 0 || kingcol - 1 < 0){
                                break;
                            }
                            else if(all[kingrow][kingcol - i]->istype("empty") && all[kingrow][kingcol - 1]->istype("empty")){
                                waystocheck[waysind] = kingrow;
                                waysind++;
                                waystocheck[waysind] = kingcol - i;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going to the left only
                        for(int i = 2; i < 8; i++){
                            if(kingrow - i < 0 || kingrow - 1 < 0){
                                break;
                            }
                            else if(all[kingrow - i][kingcol]->istype("empty") && all[kingrow - 1][kingcol]->istype("empty")){
                                waystocheck[waysind] = kingrow - i;
                                waysind++;
                                waystocheck[waysind] = kingcol;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going down only
                        for(int i = 2; i < 8; i++){
                            if(kingrow + i > 7 || kingrow + 1 > 7){
                                break;
                            }
                            else if(all[kingrow + i][kingcol]->istype("empty") && all[kingrow + 1][kingcol]->istype("empty")){
                                waystocheck[waysind] = kingrow + i;
                                waysind++;
                                waystocheck[waysind] = kingcol;
                                waysind++;
                            }
                            else break;
                            
                        }
                        //checks going up only
                    }
                    for(int i = 0; i < waysind; i = i + 2){
                        if(mine[l]->canmove(waystocheck[i], waystocheck[i+1])){
                            for(int w = 0; w < oppieces; ++w){
                                if(theirs[w]->canmove(waystocheck[i], waystocheck[i+1])){
                                    otherscanreach = true;
                                    break;
                                }
                            }
                            if(!otherscanreach){
                                //cout << waystocheck[i] << " " << waystocheck[i+1] << endl;
                                dest+=static_cast<char>(waystocheck[i + 1] + 'a');
                                dest+=static_cast<char>(waystocheck[i]+1+'0');
                                cur = mine[l]->getcoords();
                                //cout << "cur is " << cur << " dest is " << dest << endl;
                                Theboard->notifybeforemoveboard(cur,oppturn);
                                Theboard->makemove(cur,dest,level-1);
                                if ((colour=="white"&&turn=="black") ||
                                    (colour=="black"&&turn=="white")){
                                    lastcoords = dest;
                                    Theboard->notifyaftermoveboard(dest, turn);
                                    for(int i = 0; i < oppieces; ++i){
                                        Theboard->notifyaftermoveboard(dest, originalturn);
                                    }
                                    return;
                                }
                                else{
                                    Theboard->notifyaftermoveboard(cur, oppturn);
                                }
                            }
                        }
                    }
                }
                //////////////////////////// Done with doing the checkking ////////////////////////
            }
        }
        cout << "passed checkking" << endl;
        if(!takenmove){
            int movedpieces[numpieces];
            for(int i = 0; i < numpieces; ++i){
                movedpieces[i] = 0;
            }
            
            for(int k = 0; k < numpieces; ++k){
                while(movedpieces[move_piece] == 1){
                    move_piece = rand() % numpieces;
                }
                cur = mine[move_piece]->getcoords();
                for(int i = 0; i < 1000; ++i){
                    int r2 = rand() % 8;
                    int c2 = rand() % 8;
                    dest+=static_cast<char>(c2+'a');
                    dest+=static_cast<char>(r2+'1');
                    if(mine[move_piece]->canmove(r2, c2)){
                        Theboard->notifybeforemoveboard(cur,oppturn);
                        Theboard->makemove(cur,dest,level-1);
                        if ((colour=="white"&&turn=="black") ||
                            (colour=="black"&&turn=="white")){
                            lastcoords = dest;
                            Theboard->notifyaftermoveboard(dest, turn);
                            for(int i = 0; i < oppieces; ++i){
                                Theboard->notifyaftermoveboard(dest, originalturn);
                            }
                            return;
                        }
                        else{
                            Theboard->notifyaftermoveboard(cur, oppturn);
                            Theboard->notifyaftermoveboard(dest, turn);
                        }
                    }
                    dest="";
                }
                movedpieces[move_piece] = 1;
            }
            
            for(int k = 0; k < numpieces; ++k){
                cur = mine[k]->getcoords();
                for (int r2=0; r2< 8; r2++){
                    for (int c2=0; c2< 8; c2++){
                        dest+=static_cast<char>(c2+'a');
                        dest+=static_cast<char>(r2+'1');
                        if(mine[k]->canmove(r2, c2)){
                            Theboard->notifybeforemoveboard(cur,oppturn);
                            Theboard->makemove(cur,dest,level-1);
                            if ((colour=="white"&&turn=="black") ||
                                (colour=="black"&&turn=="white")){
                                lastcoords = dest;
                                Theboard->notifyaftermoveboard(dest, turn);
                                for(int i = 0; i < oppieces; ++i){
                                    Theboard->notifyaftermoveboard(dest, originalturn);
                                }
                                return;
                            }
                            else{
                                Theboard->notifyaftermoveboard(cur, oppturn);
                                Theboard->notifyaftermoveboard(dest, turn);
                            }
                        }
                        dest="";
                    }
                }
            }
            // ^ defending -> the random moves -> then brute force
        }
                //////////////////////////// Move if in danger or can take a piece ////////////////
                //cout << "reaching for loop for random moves" << endl;
       
     }
}

//end of player make move
//see player.h for details

bool Player::pawnexchange()
{
    return pawnexch;
}

//see player.h for details

void Player::computerpawnexchange()
{
    char pawnexchangepiece;
    bool white=colour=="white";
    if (level==1)
    {
        if (white)pawnexchangepiece='N';
        else pawnexchangepiece='n';
    }
    else if (level==2)
    {
        if (white)pawnexchangepiece='B';
        else pawnexchangepiece='b';
    }
    else if (level==3)
    {
        if (white)pawnexchangepiece='R';
        else pawnexchangepiece='r';
    }
    else if (level==4)
    {
        if (white)pawnexchangepiece='Q';
        else pawnexchangepiece='q';
    }
    placepiece('+',pawnexchangepiece, lastcoords);
    unsetpawnexchange();
}



//see player.h for details

void Player::setpawnexchange()
{
    pawnexch=true;
}

//see player.h for details

void Player::unsetpawnexchange()
{
    pawnexch=false;
}

//see player.h for details

void Player::placepiece(char opp, char piece, std::string coords)
{
    Theboard->putpiece(opp, piece ,coords);
}

//see player.h for details

void Player::Printboard()
{
    cout << *Theboard;
}

//see player.h for details

string Player::whosturn()
{
    return turn;
}

//see player.h for details
void Player::setturn(string clr)
{
    turn=clr;
}

//see player.h for details
void Player::printresults()
{
    TheScoreboard->PrintResults();
}

//see player.h for details
bool Player::iscomputer()
{
    if (level==0)return false;
    else return true;
}



void Player::setincheck(){
    incheck=true;
}

void Player::unsetincheck(){
    incheck=false;
}



bool Player::cansetupexit(){
    
    return Theboard->cansetupexit();
    
    
}


void Player::checkstate(){
    
    bool endofgame=Theboard->nomoremoves();
    if(endofgame&&incheck)ischeckmate=true;
    else if(endofgame&&!incheck)isstalemate=true;
    
}
void Player::reset(){
    
    incheck=false;
    ischeckmate=false;
    isstalemate=false;
    
}

void Player::notifybeforemoveplayer(string coords, string colour){
    Theboard->notifybeforemoveboard(coords, colour);
    
}

void Player::notifyaftermoveplayer(string dest, string colour){
    Theboard->notifyaftermoveboard(dest, colour);
}

void Player::notifyalloppieces(string dest,string colour){
    Piece ***all = Theboard->getpieces();
    string oppturn;
    if(Player::whosturn() == "white") oppturn = "black";
    else oppturn = "white";
    for(int i = 0; i < 8; ++i){
        for(int j = 0; j < 8; ++j){
            if(all[i][j]->istype(oppturn)){
                Theboard->notifyaftermoveboard(all[i][j]->getcoords(), oppturn);
            }
        }
    }
    delete [] all;
}




