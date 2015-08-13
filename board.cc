#include <iostream>
#include <iomanip>
#include "board.h"
#include "piece.h"
#include "textdisplay.h"
#include "empty.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "pawn.h"
#include "player.h"

using namespace std;

void Board::putpiece(char opp, char piece, string coords)
{
    int c=coords[0]- 'a'; //e1 refers to column e row 1
    int r=coords[1]- '0' - 1; //subtract one since rows are from 1-8
    //and need to store in array from 0-7
    if (opp=='+')
    {
        pieces[r][c]->undraw();
        delete pieces[r][c]; //since I initialize pieces to have all empty spaces

        // it will be deleting an empty piece if no piece exists which is safe

        if (piece=='K')
        {
            if (wking!=NULL)
            {
                string oldcoords=wking->getcoords();
                if(oldcoords!=coords)
                {
                    putpiece('-',' ',oldcoords);
                }
            }
            pieces[r][c]=new King(piece);
            updateking(pieces[r][c],NULL);
            pieces[r][c]->setcoords(r,c);
            pieces[r][c]->notify(thedisplay);
            pieces[r][c]->draw();
            Piece::setKing("white", pieces[r][c]);
            wking=static_cast<King *>(pieces[r][c]);


        }
        else if(piece=='k')
        {
            if (bking!=NULL)
            {
                string oldcoords=bking->getcoords();
                if(oldcoords!=coords)
                {
                    putpiece('-',' ',oldcoords);
                }
            }
            pieces[r][c]=new King(piece);
            pieces[r][c]->setcoords(r,c);
            updateking(pieces[r][c],NULL); //need this incase you replace a black king with a white one
            pieces[r][c]->notify(thedisplay);
            pieces[r][c]->draw();
            Piece::setKing("black", pieces[r][c]);
            bking=static_cast<King *>(pieces[r][c]);
        }


        else if (piece=='Q'||piece=='q')
        {
            pieces[r][c]=new Queen(piece);
            updateking(pieces[r][c],NULL);
            pieces[r][c]->setcoords(r,c);
            pieces[r][c]->notify(thedisplay);
            pieces[r][c]->draw();
        }
        else if (piece=='B'||piece=='b')
        {
            pieces[r][c]=new Bishop(piece);
            updateking(pieces[r][c],NULL);
            pieces[r][c]->setcoords(r,c);
            pieces[r][c]->notify(thedisplay);
            pieces[r][c]->draw();
        }
        else if (piece=='R'||piece=='r')
        {
            pieces[r][c]=new Rook(piece);
            updateking(pieces[r][c],NULL);
            pieces[r][c]->setcoords(r,c);
            pieces[r][c]->notify(thedisplay);
            pieces[r][c]->draw();
        }
        else if (piece=='N'||piece=='n')
        {
            pieces[r][c]=new Knight(piece);
            updateking(pieces[r][c],NULL);
            pieces[r][c]->setcoords(r,c);
            pieces[r][c]->notify(thedisplay);
            pieces[r][c]->draw();

        }
        else if (piece=='P'||piece=='p')
        {
            pieces[r][c]=new Pawn(piece);
            updateking(pieces[r][c],NULL);
            pieces[r][c]->setcoords(r,c);
            pieces[r][c]->notify(thedisplay);
            pieces[r][c]->draw();
        }
    }
    else if (opp=='-')
    {
        pieces[r][c]->undraw();
        delete pieces[r][c]; //again this is safe see above
        updateking(pieces[r][c],NULL);
        pieces[r][c]=new Empty; //no matter what the piece is were removing it.
        pieces[r][c]->setcoords(r,c);
        pieces[r][c]->notify(thedisplay);

    }



}

void Board::makemove(string start, string final, int level )
{
    if(level==0||level==1||level==2||level==3)
    {
        int c=start[0]- 'a'; //e1 refers to column e row 1
        int r=start[1]- '0' - 1; //subtract one since rows are from 1-8
        int finalc=final[0]- 'a'; //e1 refers to column e row 1
        int finalr=final[1]- '0' - 1; //subtract one since rows are from 1-8
        string whosturn=Player::whosturn();

        bool blackkingincheck=false;
        bool whitekingincheck=false;
        bool white=pieces[r][c]->istype("white");
        bool black=pieces[r][c]->istype("black");
        char theletter=pieces[r][c]->getletter();




        if (((whosturn=="white"&&pieces[r][c]->istype("white"))
                ||(whosturn=="black"&&pieces[r][c]->istype("black"))))
        {
            if ((start=="e1"&&theletter=='K'&&(final=="g1"||final=="c1"))||
                    (start=="e8"&&theletter=='k'&&(final=="g8"||final=="c8")))
            {
                bool toleft=finalc<c;
                makemovecastle(finalr,finalc,toleft);
            }
            else if(pieces[r][c]->canmove(finalr,finalc))
            {


                Piece* temp=pieces[finalr][finalc];

                pieces[r][c]->setcoords(finalr,finalc);

                pieces[finalr][finalc]=pieces[r][c];

                //update king checks whether your moving a king then updates it
                updateking(pieces[finalr][finalc],pieces[r][c]);

                pieces[r][c]=new Empty;

                pieces[r][c]->setcoords(r,c);

                blackkingincheck=bking->incheck();

                whitekingincheck=wking->incheck();

                if ((white&&whitekingincheck)||(black&&blackkingincheck))
                {
                    pieces[finalr][finalc]->setcoords(r,c);

                    delete pieces[r][c];

                    pieces[r][c]=pieces[finalr][finalc];
                    updateking(pieces[finalr][finalc],pieces[r][c]);

                    pieces[finalr][finalc]=temp;

                }
                else
                {
                    if (whosturn=="white")
                    {
                        Player::setturn("black");
                        if(blackkingincheck)bking->setincheck();
                        else bking->unsetincheck();
                    }

                    else
                    {
                        Player::setturn("white");
                        if(whitekingincheck)wking->setincheck();
                        else wking->unsetincheck();

                    }
                    if (((theletter=='P'&&r==6)||(theletter=='p'&&r==1)))
                    {

                        static_cast<Pawn *>(pieces[finalr][finalc])->pawnexchange();
                    }
                    else if (((theletter=='R')||(theletter=='r')))
                    {

                        static_cast<Rook *>(pieces[finalr][finalc])->setmoved();
                    }
                    else if (((theletter=='K')||(theletter=='k')))
                    {
                        static_cast<King *>(pieces[finalr][finalc])->setmoved();
                    }
                    makemovepassant(r, c, finalr, finalc,theletter);
                    unsetpassant();

                    cerr<< whosturn << (level?" computer":" player") << " moved " << theletter << " from " << start << " to " << final << " It's "<< Player::whosturn() <<" turn now" << endl;
                    delete temp;
                    pieces[r][c]->notify(thedisplay);
                    pieces[r][c]->undraw();
                    pieces[r][c]->draw();

                    pieces[finalr][finalc]->notify(thedisplay);
                    pieces[finalr][finalc]->undraw();
                    pieces[finalr][finalc]->draw();

                }



            }

        }


    }
    else if (level==2)
    {



        


                    }

                }























void Board::makemovecastle(int r, int c, bool toleft)
        {

            int initialrookcol;
            int endingrookcol;
            int initialkingc=4;
            int kingc=initialkingc;
            bool piecewhite=pieces[r][kingc]->istype("white");
            bool movingwhite=false;

            if(r==0)
            {
                movingwhite=true;
            }


            if((piecewhite&&movingwhite&&!wking->incheck())||(!bking->incheck()&&!piecewhite&&!movingwhite))
            {
                if(toleft)
                {
                    initialrookcol=0;
                    endingrookcol=c+1;

                }
                else
                {
                    initialrookcol=7;
                    endingrookcol=c-1;

                }
                King* king=dynamic_cast<King*>(pieces[r][kingc]);
                Rook* rook=dynamic_cast<Rook*>(pieces[r][initialrookcol]);


                if ( (king!=NULL)&&(rook!=NULL)&&!king->hasmoved()&&!rook->hasmoved()
                        && pieces[r][initialrookcol]->canmove(r,endingrookcol))
                {
                    movingking(movingwhite,toleft,r,kingc);
                    if(toleft)kingc--;
                    else kingc++;

                    if((movingwhite&&wking->incheck())||(!movingwhite&&bking->incheck()))
                    {

                        movingking(movingwhite,!toleft,r,kingc);

                    }
                    else
                    {

                        movingking(movingwhite,toleft,r,kingc);
                        if(toleft)kingc--;
                        else kingc++;

                        if((movingwhite&&wking->incheck())||(!movingwhite&&bking->incheck()))
                        {

                            movingking(movingwhite,!toleft,r,kingc);
                            if(toleft)kingc++;
                            else kingc--;
                            movingking(movingwhite,!toleft,r,kingc);

                        }
                        else
                        {
                            if(movingwhite)
                            {
                                pieces[r][initialkingc]->undraw();
                                wking->draw();
                            }
                            else
                            {
                                pieces[r][initialkingc]->undraw();
                                bking->draw();
                            }


                            Piece* temp=pieces[r][endingrookcol];
                            pieces[r][endingrookcol]=pieces[r][initialrookcol];
                            pieces[r][endingrookcol]->setcoords(r,endingrookcol);
                            pieces[r][endingrookcol]->notify(thedisplay);
                            pieces[r][initialrookcol]=temp;
                            pieces[r][initialrookcol]->setcoords(r,initialrookcol);
                            pieces[r][initialrookcol]->notify(thedisplay);
                            pieces[r][initialrookcol]->undraw();
                            pieces[r][endingrookcol]->draw();


                            string whosturn=Player::whosturn();
                            if (whosturn=="white")
                            {
                                Player::setturn("black");
                            }
                            else
                            {
                                Player::setturn("white");
                            }
                            cerr<< whosturn << " player did a special move castle from " << (piecewhite?"e1":"e8") << " to "
                                <<(char)(c+'a') <<(char)(r + '1') << " It's "<< Player::whosturn() <<"players turn now" << endl;
                        }


                    }


                }
            }
        }

        void Board::movingking(bool white, bool left,int r ,int c)
        {
            int newc=c;
            if (left)newc--;
            else newc++;
            Piece* bk=pieces[r][newc];
            pieces[r][newc]=pieces[r][c];
            pieces[r][newc]->setcoords(r,newc);
            pieces[r][newc]->notify(thedisplay);
            pieces[r][c]=bk;
            pieces[r][c]->setcoords(r,c);
            pieces[r][c]->notify(thedisplay);
            updateking(pieces[r][c],pieces[r][newc]);
        }

        bool Board::nomoremoves()
        {
            Piece * temp;
            string whosturn=Player::whosturn();
            for (int r=0; r<BoardSize; r++)
            {
                for (int c=0; c<BoardSize; c++)
                {

                    for (int r2=0; r2< BoardSize; r2++)
                    {
                        for (int c2=0; c2< BoardSize; c2++)
                        {
                            if((pieces[r][c]->istype(whosturn))&&
                                    (pieces[r][c]->canmove(r2,c2)))
                            {

                                temp=pieces[r2][c2];
                                pieces[r2][c2]=pieces[r][c];
                                pieces[r2][c2]->setcoords(r2,c2);
                                pieces[r][c]=new Empty;
                                pieces[r][c]->setcoords(r,c);

                                if((whosturn=="white"&&wking->incheck())||
                                        (whosturn=="black"&&bking->incheck()))
                                {

                                    delete pieces[r][c];
                                    pieces[r][c]=pieces[r2][c2];
                                    pieces[r][c]->setcoords(r,c);
                                    pieces[r2][c2]=temp;
                                }
                                else
                                {
                                    cerr << (char)(c+'a') << (char)(r+'1') << " to "  << (char)(c2+'a') << (char)(r2+'1') << " still available move" << endl;
                                    delete pieces[r][c];
                                    pieces[r][c]=pieces[r2][c2];
                                    pieces[r][c]->setcoords(r,c);
                                    pieces[r2][c2]=temp;
                                    return false;
                                }


                            }

                        }

                    }

                }


            }
            return true;
        }

        void Board::makemovepassant(int r , int c, int finalr, int finalc,char theletter)
        {
            bool white=pieces[finalr][finalc]->istype("white");
            Pawn* pawn=dynamic_cast<Pawn*>(pieces[finalr][finalc]);
            bool empassen;
            if (pawn!=NULL)empassen=pawn->isempassen();
            if(empassen)
            {

                int empassencol=static_cast<Pawn*>(pieces[finalr][finalc])->getempassen();
                if(empassencol==finalc)
                {
                    int empassenrow;
                    if (white)empassenrow=finalr-1;
                    else empassenrow=finalr+1;
                    pieces[empassenrow][empassencol]->undraw();
                    cerr<< (white?"white":"black") << " player did passant " << (char)(c+'a') <<(char)(r + '1') << " removed  "
                        <<(char)(empassenrow+'a') <<(char)(empassenrow + '1')  << endl;
                    delete pieces[empassenrow][empassencol];
                    pieces[empassenrow][empassencol]= new Empty;
                    pieces[empassenrow][empassencol]->setcoords(empassenrow,empassencol);
                    pieces[empassenrow][empassencol]->notify(thedisplay);

                    Pawn* neighbour=NULL;
                    if(finalc<c&&(c-1)>=0)
                    {
                        neighbour=dynamic_cast<Pawn*>(pieces[empassenrow][empassencol-1]);
                    }
                    else if(finalc>c&&(c+1)<BoardSize)
                    {
                        neighbour=dynamic_cast<Pawn*>(pieces[empassenrow][empassencol+1]);
                    }
                    if (neighbour!=NULL)neighbour->unsetempassen();
                }
                static_cast<Pawn*>(pieces[finalr][finalc])->unsetempassen();


            }
            else if((theletter=='P'&&r==1&&finalr==3)||(theletter=='p'&&r==6&&finalr==4))
            {

                if(finalc-1>=0)
                {
                    Pawn* neighbour=dynamic_cast<Pawn*>(pieces[finalr][finalc-1]);
                    if (neighbour!=NULL&&isyourpiece(finalr,finalc-1))neighbour->setempassen(finalc);

                }

                if(finalc+1>=0)
                {
                    Pawn* neighbour=dynamic_cast<Pawn*>(pieces[finalr][finalc+1]);
                    if (neighbour!=NULL&&isyourpiece(finalr,finalc+1))neighbour->setempassen(finalc);

                }

            }


        }

        void Board::unsetpassant()
        {

            for (int r=0; r<BoardSize; r++)
            {
                for (int c=0; c<BoardSize; c++)
                {

                    if (!isyourpiece(r,c))
                    {

                        Pawn* pawn=dynamic_cast<Pawn*>(pieces[r][c]);
                        if (pawn!=NULL)pawn->unsetempassen();


                    }

                }


            }
        }

        Board::~Board()
        {

            for (int r=0; r<BoardSize; r++)
            {
                for (int c=0; c<BoardSize; c++)
                {
                    delete pieces[r][c];

                }
            }
            for (int i=0; i<BoardSize; i++)
            {
                delete [] pieces[i];

            }
            delete [] pieces;

            delete thedisplay;
            delete xwin;
            wking=NULL;
            bking=NULL;
            Piece::setKing("black", NULL);
            Piece::setKing("white", NULL);

        }

        Board::Board()
        {
            thedisplay= new TextDisplay;
            pieces=new Piece**[BoardSize];
            for (int i=0; i<BoardSize; i++)
            {
                pieces[i]=new Piece*[BoardSize];
            }
            xwin=new Xwindow(600,600);
            Piece::setdisplay(xwin);
            for (int r=0; r<BoardSize; r++) //sets all the coords after creating the empty board
            {
                //btw Boardsize is from textdisplay its 8
                for (int c=0; c<BoardSize; c++)
                {

                    pieces[r][c]=new Empty;
                    pieces[r][c]->setcoords(r,c);
                    pieces[r][c]->draw();
                    pieces[r][c]->notify(thedisplay);


                }

            }
            Piece::setPieces(pieces);
            Piece::redraw();
            Piece::drawletters();


        }


        ostream &operator<<(std::ostream &out, const Board &brd)
        {

            out << *(brd.thedisplay);

            return out;
        }

        void Board::updateking(Piece* oldking,Piece* newking)
        {

            if(wking==static_cast<King *>(oldking))
            {
                Piece::setKing("white", newking);
                wking=static_cast<King *>(newking);

            }
            else if(bking==static_cast<King *>(newking))
            {
                Piece::setKing("black", newking);
                bking=static_cast<King *>(newking);

            }



        }

        bool Board::cansetupexit()
        {
            int firstrow=0;
            int lastrow=7;
            char letter;
            for (int i=0; i<BoardSize; i++)
            {
                letter=pieces[firstrow][i]->getletter();
                if (letter=='p')return false;
            }
            for (int i=0; i<BoardSize; i++)
            {
                letter=pieces[lastrow][i]->getletter();
                if (letter=='P')return false;
            }
            if((wking==NULL)||(bking==NULL))return false;
            return !(wking->incheck()||bking->incheck());
        }



        bool Board::isyourpiece(int r, int c)
        {


            return pieces[r][c]->istype(Player::whosturn());

        }

        void Board::notifyaftermoveboard(string dest, string colour)
        {
            int c=dest[0]- 'a'; //e1 refers to column e row 1
            int r=dest[1]- '0' - 1; //subtract one since rows are from 1-8


            for(int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    if(pieces[r][c]->canmove(i,j) && pieces[i][j]->istype(colour))
                    {
                        pieces[i][j]->incdanger();

                    }
                }
            }
        }


        void Board::notifybeforemoveboard(string dest, string colour)
        {
            int c= dest[0]- 'a'; //e1 refers to column e row 1
            int r= dest[1]- '0' - 1; //subtract one since rows are from 1-8
            for(int k = 0; k < 8; k++)
            {
                for(int j = 0; j < 8; j++)
                {

                    if(pieces[r][c]->canmove(k,j) && pieces[k][j]->istype(colour))
                    {
                        pieces[k][j]->dimdanger();
                    }
                }
            }
        }

        Piece*** Board::getpieces()
        {
            return pieces;
        }





