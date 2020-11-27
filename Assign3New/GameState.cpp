#include "GameState.h"

using namespace std;

//Create board from another board
GameState::GameState(const GameState & rhs){
	movesSoFar = rhs.movesSoFar;
	moveHistory = rhs.moveHistory;
	expectedWork = rhs.expectedWork;
	idNumber = rhs.idNumber;
	board = rhs.board;
}

//checks if 2 GameStates are equal based only on their board values
bool GameState::operator==(const GameState & rhs) const{
/*
	if(movesSoFar != rhs.movesSoFar){ return false ; }
	if(moveHistory != rhs.moveHistory){ return false; }
	if(expectedWork != rhs.expectedWork){ return false; }
	if(idNumber != rhs.idNumber){ return false; }
	if(board == rhs.board){ return true; }
	return false;
*/
	return board == rhs.board;
}

//returns a copy of rhs
GameState & GameState::operator=(const GameState& rhs){
	movesSoFar = rhs.movesSoFar;
	moveHistory = rhs.moveHistory;
	expectedWork = rhs.expectedWork;
	idNumber = rhs.idNumber;
	board = rhs.board;

	return *this;
}

//checks if a GameState is less than another based off of expected work
//if work is equivalent, return the older board
bool GameState::operator<(const GameState& rhs) const
{
	return (expectedWork < rhs.expectedWork || 
		(expectedWork == rhs.expectedWork && 
			idNumber < rhs.idNumber));
}

//checks if a GameState is greater than another based off of expected work
//if work is equivalent, return the older board
bool GameState::operator>(const GameState& rhs) const
{
	return (expectedWork > rhs.expectedWork || 
		(expectedWork == rhs.expectedWork && 
			idNumber > rhs.idNumber));
}

//calls the Board member's move function and update GameState's functions appropriately
void GameState::moveBoard(int m, int id){
	string s = board.move(m,id);
	setHistory(	s + '\n' + board.toString());

	if(id!=-1){	idNumber=id; }
	movesSoFar++;
	calculateRemainingMoves();
}

//calculate and set the expected work to solve
void GameState::calculateRemainingMoves()
{
	int offset=0;
	for(int i=0;i<board.SIZE;i++){
		for(int j=0;j<board.SIZE;j++){
			if((board.board[i][j]-1) % board.SIZE!=j){
	 			offset++;
			}
			if((board.board[i][j]-1) / board.SIZE!=i){
				offset++;
			}
		}
	}
	expectedWork = (offset/board.SIZE) + movesSoFar;
}
