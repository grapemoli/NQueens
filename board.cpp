/*
    board.cpp
    Grace Nguyen
    09/17/22
*/

#include "board.h"


// constructors
Board::Board() {
    std::cout << "Input an integer greater than 3: ";
    std::cin >> Board::n;
} // end null constructor


// getter and setters
void Board::setDimension(int dimension) {
    Board::n = dimension;
} // end setter

int Board::getDimension() {
    return(Board::n);
} // end getter


// other methods
void Board::start() {
    // sort all of the queens until they are placed such that
    // no one queen can directly attack another
    bool keepGoing = true;
    int row = 0;

    while(keepGoing == true) {
        Queen queen;
	queen.setYPosition(row);
	
	// find a free x position
	bool collides = false;
	bool keepMoving = true;
	int xPosition = Board::getFreePosition(row);
	
	if(xPosition == -1) {
	    int queensDisplaced = Board::popUntilFree();
	    row = row - queensDisplaced;
	}else{
	    queen.setXPosition(xPosition);
	    Board::queens.push(queen);
	    row++;
	} // end if-else
	
	// ending conditions: if n queens are placed
	if(Board::queens.getSize() == Board::n) {
	    keepGoing = false;;
	} // end if
	
    } // end while
    

    // and now we format and print
    std::cout << "\n";
    Board::printBoard();

} // end start

void Board::printBoard() {
    // print queen positions by marking each queen place as 1, empty spots as 0
    int positions[Board::n][Board::n];

    // initialize all points
    for(int i = 0; i < Board::n; i++) {
	for(int j = 0; j < Board::n; j++) {
	    positions[i][j] = 0;
	} // end for
    } // end for

    // get all queen positions from stack 
    while(Board::queens.getSize() > 0) {
	Queen currentQueen = Board::queens.peek();
	Board::queens.pop();
	positions[currentQueen.getYPosition()][currentQueen.getXPosition()] = 1;
    } // end while

    // print the board
    for(int i = 0; i < Board::n; i++) {
	for(int j = 0; j < Board::n; j++) {
	    std::cout << positions[i][j] << " ";
	} // end for
	std::cout << "\n";
    } // end for
} // end printBoard

bool Board::collides(int xPos, int yPos) {
    // return true if any queen in the stack collides with the passed point
    bool collides = false;
    bool keepGoing = true;
    Stack<Queen> checkedQueens; // temporary holder of queens

    while(keepGoing == true) {
        // pop the top queen on stack, push to temporary holder
	Queen currentQueen = Board::queens.peek();
	checkedQueens.push(currentQueen);
	Board::queens.pop();

	// check the current queen against passed coordinates
	// 1. check that not in same column
	if(xPos == currentQueen.getXPosition()) {
	    collides = true;
	    keepGoing = false;
	} // end if 

 	// 2. check that not in same row
	if(yPos == currentQueen.getYPosition()) {
	    collides = true;
	    keepGoing = false;
	} // end if

	// 3. check that are not in same main/off diagonals
	int xPosMain = currentQueen.getXPosition(); // main diagonal, in positive direction
	int yPosMain = currentQueen.getYPosition();
	int xNegMain = currentQueen.getXPosition(); // main diagonal, in negative directoin
	int yNegMain = currentQueen.getYPosition();

	int xPosOff = currentQueen.getXPosition(); // off diagonal, in positive direction
	int yPosOff = currentQueen.getYPosition();
	int xNegOff = currentQueen.getXPosition(); // off diagonal, in negative direction
	int yNegOff = currentQueen.getYPosition();

	for(int i = 0; i < Board::n; i++) {
	    // checking main diagonal
	    xPosMain++;
	    yPosMain++;
	    xNegMain--;
	    yNegMain--;

	    if(xPosMain == xPos) {
		if(yPosMain == yPos) {
		    collides = true;
		    keepGoing = false;
		} // end if
	    } // end if

	    if(xNegMain == xPos) {
		if(yNegMain == yPos) {
		    collides = true;
		    keepGoing = false;
		} // end if
	    } // end if

	    // checking off diagonal
	    xPosOff++;
	    yPosOff--;
	    xNegOff--;
	    yNegOff++;

	    if(xPosOff == xPos) {
		if(yPosOff == yPos) {
		    collides = true;
		    keepGoing = false;
		} // end if 
	    } // end if

	    if(xNegOff == xPos) {
		if(yNegOff == yPos) {
		    collides = true;
		    keepGoing = false;
		} // end if
	    } // end if
	} // end for

	// lastly, end while loop if queens stack is empty
	if(Board::queens.getSize() == 0) {
	    keepGoing = false;
	} // end if
    } // end while

    // reload the queens stack to normal
    while(checkedQueens.getSize() > 0) {
	Board::queens.push(checkedQueens.peek());
	checkedQueens.pop();
    } // end while

    return(collides);

} // end collides

int Board::getFreePosition(int yPos) {
    // find a free x position, and return it 
	bool collides = false;
	bool keepGoing = true;
	int xPos = 0;

    // note that 0, 0 is free if there is no queens on the board
    if(Board::queens.getSize() == 0) {
        xPos = 0;
    }else{
        while(keepGoing == true) {
	    // if the current position collides, then increment the x position by 1
	    // else, no collision, push new queen position to stack and exit
	    // other possible exit condition - the x position reaches the end bounds
            collides = Board::collides(xPos, yPos);

            if(collides == true) {
                if(xPos < (Board::n - 1)) {
                    xPos++;
                }else{
                    keepGoing = false;
                    xPos = -1;
                } // end if-else
            }else{
                keepGoing = false;
            } // end if-else
        } // end while
    } // end if-else

    return(xPos);

} // end getFreePosition

int Board::popUntilFree() {
    // pop queen at the top, and move right by +1
    // pop the next queen if the previous queen is at the "end of the board"
    // returns an integer for every queen popped
    bool keepGoing = true;
    int ogSize = Board::queens.getSize();

    while(keepGoing == true) {
	// take into account stack size
	if(Board::queens.getSize() > 1) {
	    // non-empty stack
	    Queen lastQueen = Board::queens.peek();
            Board::queens.pop();

            int xPos = lastQueen.getXPosition();
            int yPos = lastQueen.getYPosition();
        
            // check that x-coordinate is not already at the end
            if(xPos == (Board::n - 1)) {
                // continue and pop the next queen
                keepGoing = true;
            }else{
                // keep the pop of the current top queen if all of her moves right are 'blocked' by other queens
		bool collides = true;

		while(collides == true) {
		    xPos++;
		    collides = Board::collides(xPos, yPos);
		  
		    // check if at the end of board
		    if(xPos > ((Board::n) - 1)){
		        // exit loop and do not push the queen back into the stack
			collides = false;
		    }else{
			// not at the end of the board.. check collision
			if(collides == false) {
			    // pop the newly placed queen in
			    lastQueen.setXPosition(xPos);
			    Board::queens.push(lastQueen);
			    keepGoing = false;
			} // end if
		    } // end if-else
		} // end while
            } // end if-else
	}else if(Board::queens.getSize() == 1){
	    // take the top queen and simply shift her over one
	    Queen lastQueen = Board::queens.peek();
	    Board::queens.pop();
	    int XPos = lastQueen.getXPosition();
	    XPos++; // move right +1
	    lastQueen.setXPosition(XPos);
	    Board::queens.push(lastQueen);\
	    keepGoing = false;
	}else{
	    // stack is empty, nothing to pop
	    keepGoing = false;
	} // end if-else
    } // end while

    return(ogSize - Board::queens.getSize());
	
} // end popUntilFree
