#include <iostream>
#include "scoreboard.h"
using namespace std;

void Scoreboard::Startgame() {} //not sure we need

void Scoreboard::Endgame(string winner)
{

    if (winner =="white")white++;
    else if (winner =="black")black++;
    else
    {
        black+=.5;
        white+=.5;
    }
}

void Scoreboard::PrintResults()
{

    cout << "Final Score:" << endl;
    cout << "White:" << white << endl;
    cout << "Black:" << black << endl;
}

Scoreboard::Scoreboard()
{
    white=0;
    black=0;
}



