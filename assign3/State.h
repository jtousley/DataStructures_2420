#ifndef STATE_H
#define STATE_H
#include "HistoryBoard.h"

//data structure that is going to be enqueued and dequeued
class State{
public:
	State *nextState;
	HistoryBoard board;

	//create a node with HistoryBoard b
	State(HistoryBoard b){
		board=HistoryBoard(b);
		nextState=NULL;
	}

	State(){
		nextState=NULL;
	}
	
};

#endif