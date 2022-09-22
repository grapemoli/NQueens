/*  
    queen.h
    Grace Nguyen 
    09/17/22
*/


#ifndef QUEEN_H_EXISTS
#define QUEEN_H_EXISTS

#include <stdlib.h>

class Queen {
    private:
        int position[2]; // standard (x, y) format
    public:
        // constructors
        Queen();
        Queen(int xPos, int yPos); 
        
        // getters and setters
        int getXPosition();
	int getYPosition();
	void setXPosition(int xPos);
	void setYPosition(int yPos);
}; // end class def


#endif
