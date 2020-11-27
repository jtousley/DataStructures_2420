// SkewHeap.cpp - wdg 2008
#ifndef PQSKEWHEAP_H
#define PQSKEWHEAP_H

#include "PQ.h"

class SkewHeap : public PQ 
{
public:
	static const int KIDS = 2;
	
	SkewHeap(string name = "") : PQ(name)
	{
		this->name = name;
		size=0;
		maxRoot = NULL;
	}

	void insert(ItemType & x);  //    virtual void insert(ItemType & x )=0 ;
	ItemType deleteMax();
	int getCount() const;
	Node* RMerge(Node*, Node*); //merge two heaps recursively
	void merge(PQ *h);  // merges h into current heap 
	string printHeap(Node *, int, string) const;	//recursive helper print function
	string toString(int size) const;	//standard toString print function

private:
	Node* maxRoot;   // Heap root pointer
};


#endif


