#include "Queue.h"

using namespace std;

bool solvePuzzle(Board theGame, int jumble=0); //solves a 3x3 "Board" type, randomly shuffling it 'jumble' times. Returns true when it is solved
void puzzle1();
void puzzle2();
void puzzle3();

int main(){
	int jumbleCount=0;
	Board theGame;

/*
	cout<<"First puzzle to solve: \n";
	puzzle1();
	cout<<"Second puzzle to solve: \n";
	puzzle2();
	cout<<"Third puzzle to solve: \n";
	puzzle3();
*/

	cout<<"Last puzzle to solve (random): \n";
	if(!solvePuzzle(theGame,1000)){
		cout<<"Uh oh, that wasn't supposed to happen.\nExiting...";
		return 0;
	}

	return 0;
}

bool solvePuzzle(Board theGame,int jumble){
	const int POSMOVES=12;					//possible number of moves from any position
	const unsigned int TIRED=10000000;		//max number of boards that will be queued
	Board winningGame,						//the ideal position of the board
	tempGame; 								//board place holder
	Queue q;								//the queue for holding boards
	bool doneQueueing=false;				//variable to determine when to end the loop
	unsigned int ID=0;						//keeps track of how many boards we have looked at

	srand(time(NULL));
	theGame.jumble(jumble);
	
	q.Enqueue(theGame);
	cout<<theGame.toString()<<endl;
	if(theGame==winningGame)doneQueueing=true;

	while(!doneQueueing){
		if(ID>TIRED)return false;

		theGame=q.Dequeue();
		tempGame=theGame;
			for(int i=0;i<POSMOVES && !doneQueueing;i++){
				cout<<"ID: "<<ID<<endl;
				cout<<theGame.move(i,ID++)<<endl;
				cout<<theGame.toString()<<endl;
				if(theGame==winningGame)doneQueueing=true;
				if(!doneQueueing){
					q.Enqueue(theGame);
					theGame=tempGame;
				}
			}
	}

	cout<<"Puzzle Solved!\n"<<theGame.getHistory()
	<<"\nTotal moves: "<<theGame.getMoves()
	<<endl<<endl<<endl;
	return true;
}

void puzzle1(){
	Board firstPuzzle;

	firstPuzzle.board[0][0]=1;
	firstPuzzle.board[0][1]=2;
	firstPuzzle.board[0][2]=3;
	firstPuzzle.board[1][0]=6;
	firstPuzzle.board[1][1]=4;
	firstPuzzle.board[1][2]=5;
	firstPuzzle.board[2][0]=9;
	firstPuzzle.board[2][1]=7;
	firstPuzzle.board[2][2]=8;
	solvePuzzle(firstPuzzle);

	return;
}

void puzzle2(){
	Board secondPuzzle;

	secondPuzzle.board[0][0]=1;
	secondPuzzle.board[0][1]=8;
	secondPuzzle.board[0][2]=3;
	secondPuzzle.board[1][0]=5;
	secondPuzzle.board[1][1]=2;
	secondPuzzle.board[1][2]=4;
	secondPuzzle.board[2][0]=7;
	secondPuzzle.board[2][1]=6;
	secondPuzzle.board[2][2]=9;
	solvePuzzle(secondPuzzle);

	return;
}

void puzzle3(){
	Board thirdPuzzle;

	thirdPuzzle.board[0][0]=6;
	thirdPuzzle.board[0][1]=7;
	thirdPuzzle.board[0][2]=2;
	thirdPuzzle.board[1][0]=1;
	thirdPuzzle.board[1][1]=5;
	thirdPuzzle.board[1][2]=9;
	thirdPuzzle.board[2][0]=3;
	thirdPuzzle.board[2][1]=4;
	thirdPuzzle.board[2][2]=8;
	solvePuzzle(thirdPuzzle);

	return;
}
