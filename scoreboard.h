#ifndef __SCOREBOARD_H__
#define __SCOREBOARD_H__
#include <string>


class Scoreboard{
float white; 
float black;
 public:
void Startgame(); //starts a game
void Endgame(std::string winner); //ends the game increments the score of who won
void PrintResults(); //prints the final results
Scoreboard();
};

#endif
