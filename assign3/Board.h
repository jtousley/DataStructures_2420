#ifndef BOARD_H
#define BOARD_H

#include "avl.h"

using namespace std;

class Board {
public:
	static const int SIZE = 3;
	int board[SIZE][SIZE];  // Values of board
	
	Board(const Board & b);  //Create board from another board
	string move(int m,int id=-1);  //m is which move.  Returns string describing move
	void makeBoard(int jumbleCt = 0);  //Starting from a perfect board, do jumbleCt moves to alter it
	string toString();  //return a string which represents the contents of the board

	bool operator==(const Board &b) const;   //Return true if two boards are equal
	Board & operator=(const Board& b);	//Sets two boards equal to each other
	Board(){ makeBoard(); };
	void rotateEast(int row);
	void rotateWest(int row);
	void rotateNorth(int col);
	void rotateSouth(int col);
	void jumble(int ct);  //Do jumble moves to alter board
};

#endif