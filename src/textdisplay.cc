#include "textdisplay.h"
using namespace std;

void TextDisplay::notify(char letter, int row, int col)
{
    (theDisplay[row])[col]=letter;


}

TextDisplay::TextDisplay()
{
    theDisplay = new char*[BoardSize];
    for (int i=0; i<BoardSize; i++)
    {
        theDisplay[i]=new char[BoardSize];
    }
}

TextDisplay::~TextDisplay()
{


    for (int i=0; i<BoardSize; i++)
    {
        delete [] theDisplay[i];
    }
    delete [] theDisplay;

}

ostream &operator<<(std::ostream &out, const TextDisplay &td)
{


    for (int row=BoardSize-1; row>=0; row--)   //I am printing in reverse row 8 to row 1 but col a to h 
    {

        for (int col=0; col<BoardSize; col++)
        {
     
            if (td.theDisplay[row][col]==' ')
            {
               
                if ((row%2==0&&col%2==0)||(row%2!=0&&col%2!=0))
                {
                    out << "_";
                }
                     else
                {
                    out << " ";
                }
            }

            else
            {
                out << td.theDisplay[row][col];

            }
           
        }
        out << endl;
    }
    

return out;
}





