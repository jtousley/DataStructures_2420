/*
Jonathan Tousley
CS2420
Dr. Vicki Allan
Program 1 - Rotation Puzzle
*/

#ifndef STATE_H
#define STATE_H
#include "Board.h"

//data structure that is going to be enqueued and dequeued
class State{
public:
	State *nextState;
	Board board;

	//create a node with board b
	State(Board b){
		board=Board(b);
		nextState=NULL;
	}

	State(){
		nextState=NULL;
	}
	
};

#endif