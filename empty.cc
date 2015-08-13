#include <iostream>
#include "empty.h"
#include <unistd.h>
using namespace std;
//these are incomplete just wrote the constructors to do testing
Empty::Empty():Piece(' '){
//cerr << "empty ctor called ";
}
Empty::~Empty(){}
 bool Empty::canmove(int r, int c){
 return false; //empty spaces can't move
 }
 
void Empty::draw(){
Piece::undraw();
}


