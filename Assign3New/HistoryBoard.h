#ifndef HISTORYBOARD_H
#define HISTORYBOARD_H
#include "Board.h"

using namespace std;

struct HistoryBoard{
	int movesSoFar;
	string moveHistory;
	Board board;

	HistoryBoard(){
		board=Board();
		movesSoFar=0;
		moveHistory="";
	}

	HistoryBoard(const HistoryBoard & b);
	bool operator==(const HistoryBoard &b) const;
	HistoryBoard & operator=(const HistoryBoard& b);
	bool operator<(const HistoryBoard& rhs) const;
	bool operator>(const HistoryBoard& rhs) const;

	//calls the board class move function and updates GameState member variables
	void moveBoard(int m, int id=-1);
	//return a string which represents the contents of the board
	string toString(){return board.toString(); }
	//gives HistoryBoard access to Board class' jumble function
	void jumble(int ct){
		board.jumble(ct);
	}

	int getMoves(){return movesSoFar;}
	string getHistory(){return moveHistory;}
	void setHistory(string s){moveHistory+=s;}
	void clearHistory(){
		moveHistory="Original Board:\n"+toString(); 
		movesSoFar=0;
	}
};

#endif