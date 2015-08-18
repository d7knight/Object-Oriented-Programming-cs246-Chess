#include <iostream>
#include "player.h"
#include "piece.h"
#include <sstream>
#include <unistd.h>
using namespace std;

int level(string l){ 

if(l=="computer[1]"){
return 1;
}
else if(l=="computer[2]"){
return 2;
}
else if(l=="computer[3]"){
return 3;
}
else if (l=="computer[4]"){
return 4;
}
else return 0;
}



int main()
{
   
    
  



        string command;
        string current;
        string destination;
        char pawnch;
        Player * wplayer= Player::getPlayer("white");
        Player * bplayer= Player::getPlayer("black");
       
        Player::setturn("white");
       
        string setup;
        while (!cin.eof())
        {
            cin >> command;
            if (command=="setup")
            {
                char piece;
                string colour;
                string coords;
                while (cin >> setup){
                if (setup[0]=='+')
                {   cin >> piece >> coords;
                  if (coords[0]>='a' && coords[0] <= 'z' && coords[1]>='1'&& coords[1]<='8'){
                    Player::placepiece(setup[0], piece, coords);
                    Player::Printboard();
                    }
                }
                else if(setup == "default"){
                    Player::placepiece('+','P',"a2");
                    Player::placepiece('+','P',"b2");
                    Player::placepiece('+','P',"c2");
                    Player::placepiece('+','P',"d2");
                    Player::placepiece('+','P',"e2");
                    Player::placepiece('+','P',"f2");
                    Player::placepiece('+','P',"g2");
                    Player::placepiece('+','P',"h2");
                    Player::placepiece('+','R',"a1");
                    Player::placepiece('+','N',"b1");
                    Player::placepiece('+','B',"c1");
                    Player::placepiece('+','Q',"d1");
                    Player::placepiece('+','K',"e1");
                    Player::placepiece('+','B',"f1");
                    Player::placepiece('+','N',"g1");
                    Player::placepiece('+','R',"h1");
                    //blackspieces
                    Player::placepiece('+','p',"a7");
                    Player::placepiece('+','p',"b7");
                    Player::placepiece('+','p',"c7");
                    Player::placepiece('+','p',"d7");
                    Player::placepiece('+','p',"e7");
                    Player::placepiece('+','p',"f7");
                    Player::placepiece('+','p',"g7");
                    Player::placepiece('+','p',"h7");
                    Player::placepiece('+','r',"a8");
                    Player::placepiece('+','n',"b8");
                    Player::placepiece('+','b',"c8");
                    Player::placepiece('+','q',"d8");
                    Player::placepiece('+','k',"e8");
                    Player::placepiece('+','b',"f8");
                    Player::placepiece('+','n',"g8");
                    Player::placepiece('+','r',"h8");
                    Player::Printboard();
                }
                else if(setup == "pawns"){
                    Player::placepiece('+','P',"a5");
                    Player::placepiece('+','P',"b2");
                    Player::placepiece('+','P',"c5");
                    Player::placepiece('+','P',"d4");
                    Player::placepiece('+','P',"e2");
                    Player::placepiece('+','P',"f2");
                    Player::placepiece('+','P',"g2");
                    Player::placepiece('+','P',"h2");
                    Player::placepiece('+','P',"a1");
                    Player::placepiece('+','P',"b1");
                    Player::placepiece('+','P',"c1");
                    Player::placepiece('+','P',"d1");
                    Player::placepiece('+','K',"e1");
                    Player::placepiece('+','P',"f5");
                    Player::placepiece('+','P',"g1");
                    Player::placepiece('+','P',"h5");
                    //blackspieces
                    Player::placepiece('+','P',"a4");
                    Player::placepiece('+','p',"b7");
                    Player::placepiece('+','p',"c4");
                    Player::placepiece('+','p',"d5");
                    Player::placepiece('+','p',"e7");
                    Player::placepiece('+','p',"f7");
                    Player::placepiece('+','p',"g7");
                    Player::placepiece('+','p',"h7");
                    Player::placepiece('+','p',"a8");
                    Player::placepiece('+','p',"b8");
                    Player::placepiece('+','p',"c8");
                    Player::placepiece('+','p',"d8");
                    Player::placepiece('+','k',"e8");
                    Player::placepiece('+','p',"f4");
                    Player::placepiece('+','p',"g8");
                    Player::placepiece('+','p',"h4");
                    Player::Printboard();
                }
              
                 else if(setup == "easyblackcheckmate"){
                    Player::placepiece('+','N',"a5");
                    Player::placepiece('+','N',"b2");
                    Player::placepiece('+','N',"c5");
                    Player::placepiece('+','N',"d4");
                    Player::placepiece('+','N',"e2");
                    Player::placepiece('+','N',"f2");
                    Player::placepiece('+','N',"g2");
                    Player::placepiece('+','N',"h2");
                    Player::placepiece('+','N',"a1");
                    Player::placepiece('+','N',"b1");
                    Player::placepiece('+','N',"c1");
                    Player::placepiece('+','N',"d1");
                    Player::placepiece('+','K',"e1");
                    Player::placepiece('+','N',"f5");
                    Player::placepiece('+','N',"g1");
                    Player::placepiece('+','N',"h5");
                    //blackspieces
                    Player::placepiece('+','q',"a4");
                    Player::placepiece('+','q',"b7");
                    Player::placepiece('+','q',"c4");
                    Player::placepiece('+','q',"d5");
                    Player::placepiece('+','q',"e7");
                    Player::placepiece('+','q',"f7");
                    Player::placepiece('+','q',"g7");
                    Player::placepiece('+','q',"h7");
                    Player::placepiece('+','q',"a8");
                    Player::placepiece('+','q',"b8");
                    Player::placepiece('+','q',"c8");
                    Player::placepiece('+','q',"d8");
                    Player::placepiece('+','k',"e8");
                    Player::placepiece('+','q',"f4");
                    Player::placepiece('+','q',"g8");
                    Player::placepiece('+','q',"h4");
                    Player::Printboard();
                }
                       else if(setup == "easywhitecheckmate"){
                    Player::placepiece('+','Q',"a5");
                    Player::placepiece('+','Q',"b2");
                    Player::placepiece('+','Q',"c5");
                    Player::placepiece('+','Q',"d4");
                    Player::placepiece('+','Q',"e2");
                    Player::placepiece('+','Q',"f2");
                    Player::placepiece('+','Q',"g2");
                    Player::placepiece('+','Q',"h2");
                    Player::placepiece('+','Q',"a1");
                    Player::placepiece('+','Q',"b1");
                    Player::placepiece('+','Q',"c1");
                    Player::placepiece('+','Q',"d1");
                    Player::placepiece('+','K',"e1");
                    Player::placepiece('+','Q',"f5");
                    Player::placepiece('+','Q',"g1");
                    Player::placepiece('+','Q',"h5");
                    //blackspieces
                    Player::placepiece('+','P',"a4");
                    Player::placepiece('+','p',"b7");
                    Player::placepiece('+','p',"c4");
                    Player::placepiece('+','p',"d5");
                    Player::placepiece('+','p',"e7");
                    Player::placepiece('+','p',"f7");
                    Player::placepiece('+','p',"g7");
                    Player::placepiece('+','p',"h7");
                    Player::placepiece('+','p',"a8");
                    Player::placepiece('+','p',"b8");
                    Player::placepiece('+','p',"c8");
                    Player::placepiece('+','p',"d8");
                    Player::placepiece('+','k',"e8");
                    Player::placepiece('+','p',"f4");
                    Player::placepiece('+','p',"g8");
                    Player::placepiece('+','p',"h4");
                    Player::Printboard();
                }
                 else if(setup == "instantwhitestalemate"){

                    Player::placepiece('+','K',"a1");
                
                    //blackspieces
                    Player::placepiece('+','r',"c2");
                    Player::placepiece('+','k',"c1");
                  
                    Player::Printboard();
                }
                else if(setup == "instantblackstalemate"){

                    Player::placepiece('+','k',"a1");
                
                    //blackspieces
                    Player::placepiece('+','Q',"c4");
                    Player::placepiece('+','K',"c1");
                  
                    Player::Printboard();
                }
                  else if(setup == "redraw"){
                    Piece::redraw();  
                }


                else if (setup[0]=='=')
                {
                    cin >>colour; //needed a string
                    Player::setturn(colour);
                }
                else if (setup[0]=='-')
                {
                    cin >> coords;
                    if (coords[0]>='a' && coords[0] <= 'z' && coords[1]>='1'&& coords[1]<='8'){
                    Player::placepiece(setup[0],' ', coords); //removing the piece at coords
                    Player::Printboard();
                    }
                }
                //new options for graphics display 
                 else if (setup=="tilecolour"){
                 string tile1colour;
                 string tile2colour;
                 cin >> tile1colour >> tile2colour;
                 //same selection as in xwindow.h
                 Piece::settilecolours(tile1colour,tile2colour);
                 Piece::redraw();    
                }
                else if (setup=="piececolour"){
                 string whitecolour="white";
                 string blackcolour="black";
                 cin >> whitecolour >> blackcolour;
                 //same selection as in xwindow.h
                 Piece::setpiececolours(whitecolour,blackcolour);  
                 Piece::redraw();
                }
                else if (setup=="done"&&Player::cansetupexit()){
                setup="complete";
                cerr<<"exiting setup" <<endl;
                break;
                
                }
            

              }
            }
            else if (command == "game"&&setup=="complete")
            {
                
                string wlvl;
                string blvl;
                cin >> wlvl >> blvl;  
     
                wplayer->setlevel(level(wlvl));
                bplayer->setlevel(level(blvl));
                Player* thecurplayer;
                string oppturn;
                string originalturn;
                while (true)
                {  

                   if(Player::whosturn() == "white"){
                      
  	              oppturn = "black";
                      originalturn = "white";
                      thecurplayer=wplayer;
                      }
                  else{
                      oppturn = "white";
                      originalturn = "black";
                      thecurplayer=bplayer;
                       } 
                   thecurplayer->checkstate();
                   if (thecurplayer->checkmate()||thecurplayer->stalemate()||cin.eof())break;
                    cin >> command;

                    if (command=="move")
                    {   
                       
                         if (thecurplayer->iscomputer()){
                       
                        
                                thecurplayer->makemove();
                               if (thecurplayer->pawnexchange())
                               {
                                thecurplayer->computerpawnexchange();
                               }
                                Player::Printboard();
                                
                             
                              }
                           else{
                              
                          
                            cin >> current >> destination;
                            if(wplayer->iscomputer()||bplayer->iscomputer()){
                            thecurplayer->notifybeforemoveplayer(current, oppturn);
                            }
                            thecurplayer->makemove(current, destination);
                          
                            if (thecurplayer->pawnexchange())
                            {
                                cin >> pawnch;
                              
                                Player::placepiece('+',pawnch, destination);
                                thecurplayer->unsetpawnexchange();
                            }
                           
                            if(wplayer->iscomputer()||bplayer->iscomputer()){
                            
                        	thecurplayer->notifyaftermoveplayer(destination, originalturn);
                            }
                            
                            Player::Printboard();
                           
                           
                            }
                            }
                    else if (wplayer->iscomputer()&&bplayer->iscomputer()&&command == "moves"){
                    int amount;
                    int speed;
                    cin>>amount>> speed;
                    while (amount > 0){                  
                    amount--;
                    if (Player::whosturn() == "white")thecurplayer=wplayer;
                    else thecurplayer=bplayer;
                    thecurplayer->checkstate();
                    if (thecurplayer->checkmate()||thecurplayer->stalemate()||cin.eof())break;
                    thecurplayer->makemove();
                               if (thecurplayer->pawnexchange())
                               {
                                thecurplayer->computerpawnexchange();
                               }
                                Player::Printboard();
                    usleep(9999999/speed);
                    }
                    
    
                    }
                    
                    else if (command == "resign")
                    {
                        if(Player::whosturn() == "white")
                        {
                            cout << "Black wins!"<< endl;
                            wplayer->Endgame("black");
                        }
                        else
                        {
                            cout << "White wins!"<< endl;
                            wplayer->Endgame("white");
                        }
                        break;
                    }
                    }
                    if (wplayer->checkmate())
                    {
                        cout << "Checkmate! ";
                        cout << "Black wins!" << endl;
                        usleep(9999999);
                        wplayer->Endgame("black");
                    }
                    else if (bplayer->checkmate())
                    {
                        cout << "Checkmate! ";
                        cout << "White wins!" << endl;
                        usleep(9999999);
                        wplayer->Endgame("white");
                    }
                    else if (wplayer->stalemate()||bplayer->stalemate())
                    {
                        cout << "Stalemate! " << endl;
                        usleep(9999999);
                        wplayer->Endgame("Stalemate");
                    }
                   setup="Not done";
                   Player::setturn("white");
                }


            }


   Player::printresults();
            
        }




