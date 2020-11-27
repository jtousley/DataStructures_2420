#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Board.h"

using namespace std;

struct GameState{
	int movesSoFar;
	string moveHistory;
	int expectedWork;
	int idNumber;
	Board board;

	GameState()
	{
		board=Board();
		movesSoFar=0;
		expectedWork=0;
		moveHistory="";
		idNumber=0;
	}

	GameState(const GameState & b);  //Create board from another board
	bool operator==(const GameState &b) const;
	GameState & operator=(const GameState& b);
	//comparison based on the expected remaining moves
	bool operator<(const GameState& rhs) const;
	//comparison based on the expected remaining moves
	bool operator>(const GameState& rhs) const;

	void moveBoard(int m, int id=-1);				//calls the board class move function and updates GameState member variables
	string toString(){ return board.toString(); }  //return a string which represents the contents of the board
	void calculateRemainingMoves();					//calculate how much estimated work it will cost to solve the board
	void jumble(int ct){ board.jumble(ct); }		//gives GameState access to Board class' jumble function

	int getMoves(){return movesSoFar;}
	string getHistory(){return moveHistory;}
	//updates the history of the board -- that is, what moves I've done and what that caused the board to look like
	void setHistory(string s){ moveHistory += s; }
	//clear member variables - this should only be used after jumbling the board
	void clearHistory(){
		moveHistory="Original Board:\n"+toString(); 
		movesSoFar=0;
		expectedWork=0;
	}
};

#endif