/*
    board.h
    Grace Nguyen
    09/17/22
*/


#ifndef BOARD_H_EXISTS
#define BOARD_H_EXISTS

#include <stdlib.h>
#include <iostream>
#include "queen.h" // aggregated class
#include "stack.h" // aggregated class


class Board {
    private:
        int n;
	Stack<Queen> queens;
    public:
        // constructors
        Board();
        
        // getters and setters
        int getDimension();
        void setDimension(int dimension);

        // sorting related methods
        bool collides(int xPos, int yPos);
        void start();
	int getFreePosition(int yPos);
	int popUntilFree();

        // printing methods
        void printBoard();
}; //end class def

#endif
