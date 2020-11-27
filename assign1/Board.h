/*
Jonathan Tousley
CS2420
Dr. Vicki Allan
Program 1 - Rotation Puzzle
*/

#ifndef BOARD_H
#define BOARD_H
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <sstream>
#include <cmath>
#include <ctime>

using namespace std;

class Board {
public:
	static const int SIZE = 3;
	int board[SIZE][SIZE];  // Values of board
	string history;			//remembers previous boards
	int moves;				//remembers how many moves
	
	Board(const Board & b);  //Create board from another board
	string move(int m,int id=-1);  //m is which move.  Returns string describing move
	void makeBoard(int jumbleCt = 0);  //Starting from a perfect board, do jumbleCt moves to alter it
	string toString();  //return a string which represents the contents of the board
	bool operator==(Board &b);   //Return true if two boards are equal
	Board & operator=(const Board& b);	//Sets two boards equal to each other
	Board(){ makeBoard(); };
	void rotateEast(int row);
	void rotateWest(int row);
	void rotateNorth(int col);
	void rotateSouth(int col);
	void jumble(int ct);  //Do jumble moves to alter board
	
	int getMoves(){return moves;}
	string getHistory(){return history;}
	void setHistory(string s){history+=s;moves++;}
	void clearHistory(){history="Original Board:\n"+toString();moves=0;}
};
#endif