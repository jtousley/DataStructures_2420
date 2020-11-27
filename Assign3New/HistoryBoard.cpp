#include "HistoryBoard.h"

using namespace std;

//copy constructor
HistoryBoard::HistoryBoard(const HistoryBoard & rhs){
	movesSoFar = rhs.movesSoFar;
	moveHistory = rhs.moveHistory;
	board = rhs.board;	
}

//returns if 2 HistoryBoards are equal based on only the actual board it contains
bool HistoryBoard::operator==(const HistoryBoard &rhs) const{
/*
	if(movesSoFar != rhs.movesSoFar){ return false; }
	if(moveHistory != rhs.moveHistory){ return false; }
	if(b == rhs.b){ return true; }
	return true;
*/
	return board == rhs.board;
}

//sets all of the HistoryBoard's member variables equal to another HistoryBoard
HistoryBoard & HistoryBoard::operator=(const HistoryBoard& rhs){
	movesSoFar = rhs.movesSoFar;
	moveHistory = rhs.moveHistory;
	board = rhs.board;

	return *this;
}

//returns if 1 HistoryBoard is less than another based only on the moves so far
bool HistoryBoard::operator<(const HistoryBoard& rhs) const{
	return movesSoFar < rhs.movesSoFar;
}
//returns if 1 HistoryBoard is greater than another based only on the moves so far
bool HistoryBoard::operator>(const HistoryBoard& rhs) const{
	return movesSoFar > rhs.movesSoFar;
}

//uses the Board class move function and updates the HistoryBoard member variables appropriately
void HistoryBoard::moveBoard(int m, int id){
	string s = board.move(m,id);
	setHistory(	s + '\n' + board.toString());
	movesSoFar++;
}
