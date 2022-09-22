/* 
    queen.cpp
    Grace Nguyen 
    09/17/22
*/


#include "queen.h"


// constructors
Queen::Queen() {
    Queen::position[0] = 0;
    Queen::position[1] = 0;
} // end constuctor

Queen::Queen(int xPos, int yPos) {
    Queen::position[0] = xPos; 
    Queen::position[1] = yPos;
} // end constructor


// getters and setters
int Queen::getXPosition() {
    return(position[0]);
} // end getter

int Queen::getYPosition() {
    return(position[1]);
} // end getters 

void Queen::setXPosition(int xPos) {
    Queen::position[0] = xPos;
} // end setter

void Queen::setYPosition(int yPos) {
    Queen::position[1] = yPos;
} // end setter



