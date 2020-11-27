#include "avl.h"
#include "Board.h"
#include "Queue.h"
#include "GameState.h"
#include "HistoryBoard.h"

using namespace std;

int max(int a,int b);
//preset puzzle to solve
void puzzleFirstAStar();
//another preset puzzle to solve
void puzzleSecondAStar();
//specific puzzle to be solved
void puzzleThirdAStar();
//random puzzle to be solved, the jumble value is defined in main
void solvePuzzleAStarBrute(int jumble);
//very specifc operations on an AVL tree to ensure it is working properly
void AVLTreeTestingFunction();
//solves a 3x3 puzzle and prints the history
//uses a queue to try every possibility
//can pass a second value to randomize the board
//exits after 3 million tries -- 10 million would be a better value
void solvePuzzleBruteForce(HistoryBoard b, int a=0);
//solves a 3x3 puzzle and prints the history using an AVL tree
//can pass a second value to randomize the board
void solvePuzzleAStarSearch(GameState g, int a=0);

int main(){
	srand(time(NULL));
	static const int JUMBLECT=50;
	
	try{
//		AVLTreeTestingFunction();
//		puzzleFirstAStar();
//		puzzleSecondAStar();
//		puzzleThirdAStar();
		solvePuzzleAStarBrute(JUMBLECT);
	}
	catch(string errorMessage){
		cout<<errorMessage<<endl;
	}

	return 0;
}


int max( int lhs, int rhs ){ return lhs > rhs ? lhs : rhs; }

void AVLTreeTestingFunction()
{
	AvlTree<int> tree;
	int arrayForInitializingTree[14]={1,3,5,7,9,11,2,4,8,50,30,15,18,17};

	for(int i=0;i<9;i++){
		tree.insert(arrayForInitializingTree[i]);
	}
	cout<<tree.toString("Inserted 9 values\n")<<endl;
	tree.remove(7);
	tree.remove(9);
	cout<<tree.toString("Removed 2 values\n")<<endl;

	for(int i=9;i<13;i++){
		tree.insert(arrayForInitializingTree[i]);
	}
	cout<<tree.toString("Inserted 4 values\n")<<endl;
	tree.removeMin();
	cout<<tree.toString("Removed min\n")<<endl;
	tree.removeMin();
	cout<<tree.toString("Removed min for two (2)\n")<<endl;
	tree.removeMin();
	cout<<tree.toString("Removed min for three (3)\n")<<endl;
	tree.insert(arrayForInitializingTree[13]);
	cout<<tree.toString("Inserted 1 value\n");
}

void solvePuzzleAStarSearch(GameState theGame, int jumble){
	const int POSMOVES=12;					//possible number of moves from any position
	const unsigned int TIRED=1000000;		//max number of boards that will be queued
	unsigned int ID=0;
	AvlTree<GameState> priorityQueue;
	GameState winningGame,
	tempGame;
	bool doneQueueing=false;

	if(jumble != 0){
		theGame.jumble(jumble);
		theGame.clearHistory();
	}

	tempGame=theGame;	
	priorityQueue.insert(tempGame);
	if(tempGame==winningGame){ doneQueueing=true; }
		while(!doneQueueing){
			if(ID>TIRED){ cout<<"Too many boards attempted, A* search was not useful for that board\n"; return;}
			theGame=priorityQueue.removeMin();
//			cout<<"ID: "<<theGame.idNumber<<endl;
//			cout<<"Expected work to solve: "<<theGame.expectedWork<<endl;
//			cout<<"Board move history:\n"<<theGame.moveHistory<<endl;
//			cout<<theGame.toString()<<endl;
			tempGame=theGame;
				for(int i=0;i<POSMOVES && !doneQueueing;i++){
					tempGame.moveBoard(i,ID++);
					if(tempGame.board==winningGame.board)doneQueueing=true;
					if(!doneQueueing){
						priorityQueue.insert(tempGame);				
						tempGame=theGame;
					}
				}
		}
	if(doneQueueing){
		theGame=tempGame;
		cout<<"Puzzle Solved by A* Search Algorithm!\n"<<theGame.getHistory()
		<<"\nTotal moves: "<<theGame.getMoves()
		<<endl<<endl<<endl;
	}
}


void solvePuzzleBruteForce(HistoryBoard theGame, int jumble){
	const int POSMOVES=12;					//possible number of moves from any position
	const unsigned int TIRED=3000000;		//max number of boards that will be queued
	HistoryBoard winningGame,				//the ideal position of the board
	tempGame; 								//board place holder
	Queue q;								//the queue for holding boards
	bool doneQueueing=false;				//variable to determine when to end the loop
	unsigned int ID=0;						//keeps track of how many boards we have looked at

	if(jumble != 0){
		theGame.jumble(jumble);
		theGame.clearHistory();
	}

	tempGame=theGame;
	q.Enqueue(tempGame);
	if(tempGame==winningGame)doneQueueing=true;
	while(!doneQueueing){
		if(ID>TIRED){ cout<<"That board requires more than 6 moves, brute force was not useful for that board\n"; return; }
		theGame=q.Dequeue();
		tempGame=theGame;
			for(int i=0;i<POSMOVES && !doneQueueing;i++){
				tempGame.moveBoard(i,ID++);
				if(tempGame==winningGame)doneQueueing=true;
				if(!doneQueueing){
					q.Enqueue(tempGame);
					tempGame=theGame;
				}
			}
	}

	if(doneQueueing){
		theGame=tempGame;
		cout<<"Puzzle Solved by brute force!\n"<<theGame.getHistory()
		<<"\nTotal moves: "<<theGame.getMoves()
		<<endl<<endl<<endl;
	}
}

void puzzleFirstAStar(){
	Board boardFirst;
	GameState solvePuzzle;

	boardFirst.board[0][0]=5;
	boardFirst.board[0][1]=6;
	boardFirst.board[0][2]=4;
	boardFirst.board[1][0]=8;
	boardFirst.board[1][1]=2;
	boardFirst.board[1][2]=9;
	boardFirst.board[2][0]=1;
	boardFirst.board[2][1]=7;
	boardFirst.board[2][2]=3;

	solvePuzzle.board = boardFirst;
	solvePuzzleAStarSearch(solvePuzzle);
}

void puzzleSecondAStar(){
	Board boardSecond;
	GameState solvePuzzle;

	boardSecond.board[0][0]=2;
	boardSecond.board[0][1]=1;
	boardSecond.board[0][2]=8;
	boardSecond.board[1][0]=9;
	boardSecond.board[1][1]=4;
	boardSecond.board[1][2]=7;
	boardSecond.board[2][0]=3;
	boardSecond.board[2][1]=6;
	boardSecond.board[2][2]=5;

	solvePuzzle.board = boardSecond;
	solvePuzzleAStarSearch(solvePuzzle);

}

void puzzleThirdAStar(){
	Board boardThird;
	GameState solvePuzzle;

	boardThird.board[0][0]=1;
	boardThird.board[0][1]=3;
	boardThird.board[0][2]=9;
	boardThird.board[1][0]=6;
	boardThird.board[1][1]=2;
	boardThird.board[1][2]=7;
	boardThird.board[2][0]=4;
	boardThird.board[2][1]=5;
	boardThird.board[2][2]=8;

	solvePuzzle.board = boardThird;
	solvePuzzleAStarSearch(solvePuzzle);

}

void solvePuzzleAStarBrute(int jumble){
	GameState solvePuzzle;
	HistoryBoard histBoard;
	Board boardRandom;

	boardRandom.jumble(jumble);

	solvePuzzle.board = boardRandom;
	solvePuzzle.moveHistory="Original Board:\n" + solvePuzzle.toString();
	solvePuzzleAStarSearch(solvePuzzle);

	histBoard.board = boardRandom;
	histBoard.moveHistory = "Original Board:\n" + histBoard.toString();
	solvePuzzleBruteForce(histBoard);
}

