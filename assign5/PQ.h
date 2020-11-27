#ifndef PQ_H
#define PQ_H
#include "ItemType.h"
#include "Node.h"
#include  <limits>

class PQ
{
  protected:
    string name;  //Name of queue (for documentation purposes)
  public:
	int size;     // Number of actual items in queue.
	
	PQ(string name="No Name") {this->name = name; size=0;}
	ItemType deleteMax();
	int getSize(){return size;}
	bool isEmpty() {return size==0;}
    virtual string toString(int size) const =0;
    virtual void insert(ItemType & x )=0 ;
	virtual void merge(PQ * second)=0;
	virtual void makeEmpty() {size=0;}
};
#endif
