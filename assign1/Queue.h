/*
Jonathan Tousley
CS2420
Dr. Vicki Allan
Program 1 - Rotation Puzzle
*/

#ifndef QUEUE_H
#define QUEUE_H
#include "State.h"

//Queue to sort thru all possible game boards
class Queue{
private:
	int count; //how many items in queue
	State *front, *back; //Queue pointers

public:
	Queue(); //constructor
	~Queue(); //destructor
	void Enqueue(Board); //put a board onto the queue
	Board Dequeue(); //pull a board off the queue
	int Size(){return count;} //find out how many items are on the queue
	bool Empty(); //check to see if the queue is empty
};

#endif