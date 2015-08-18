#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];
  int width, height;

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown,Gray}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);
 
  void fillArc(int x, int y, int width, int height,int angle1, int angle2, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg, int colour=Black);
  
  void drawLine(int x1, int y1, int x2,int y2, int colour=Black);
  void drawRectangle(int x, int y, int width, int height ,int colour=Black);
  void drawArc(int x, int y, int width, int height, int angle1 , int angle2,int colour=Black);
  void fillPolygon(XPoint* points, int npoints ,int shape,int colour=Black);
  void drawSegments(XSegment *segments, int nsegments,int colour=Black);
  void drawPoints(XPoint* points, int npoints,int colour=Black);
  void drawLines(XPoint* points, int npoints,int colour=Black);
  
    // Draws a string
  void drawBigString(int x, int y, std::string msg, int colour=Black);

  // Prints the first 10000 available fonts
  void showAvailableFonts();

};

#endif
