#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <string>
#include <iostream>
const int BoardSize=8;
class TextDisplay
{
    char **theDisplay;
public:
    void notify(char letter, int row, int col); // sets the coords to be the piece
    TextDisplay();
    ~TextDisplay();
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif

