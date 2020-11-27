#ifndef QUEUE_H
#define QUEUE_H
#include "State.h"
#include "HistoryBoard.h"

//Queue to sort thru all possible game boards
class Queue{
private:
	int count; //how many items in queue
	State *front, *back; //Queue pointers

public:
	Queue(); //constructor
	~Queue(); //destructor
	void Enqueue(HistoryBoard); //put a board onto the queue
	HistoryBoard Dequeue(); //pull a board off the queue
	int Size(){return count;} //find out how many items are on the queue
	bool Empty(); //check to see if the queue is empty
};

#endif