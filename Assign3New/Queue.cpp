#include "Queue.h"

using namespace std;

//constructor
Queue::Queue(){
	front=back=NULL;
	count=0;
}

//destructor
Queue::~Queue(){
	while(front!=NULL){
		Dequeue();
	}
}

//place board s onto the queue
void Queue::Enqueue(HistoryBoard s){
	if(Empty()){
		front=back=new State(s);
	}
	else{
		State *ptr=back->nextState=new State(s);
		back=ptr;
	}
	count++;
}

//returns the front HistoryBoard from off the queue
HistoryBoard Queue::Dequeue(){
	if(Empty()){
		throw "Queue Empty!\n";
	}
		HistoryBoard b=front->board;
		State *ptr=front->nextState;
		delete front;
		front=ptr;
		count--;

		return b;
}

//returns false if there is something on the queue, otherwise returns true
bool Queue::Empty(){
	if(count)
		return false;
	else return true;
}
