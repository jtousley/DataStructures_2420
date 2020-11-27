// LeftistHeap.cpp - wdg 2008
#ifndef PQLeftistHeap_H
#define PQLeftistHeap_H

#include "PQ.h"

class LeftistHeap : public PQ 
{
public:
	static const int KIDS = 2;
	
	LeftistHeap(string name = "") : PQ(name)
	{
		this->name = name;
		size=0;
		maxRoot = NULL;
	}

	void insert(ItemType & x);  //    virtual void insert(ItemType & x )=0 ;
	ItemType deleteMax();
	int getCount() const;
	Node* RMerge(Node*, Node*); //merge two heaps
	void merge(PQ *h);  // merges h into current heap 
	string printHeap(Node *, int, string) const; //print heap recursively
	string toString(int size) const; //generic toString function
    int getNPL(Node* t); //get the null path length

private:
	Node* maxRoot;   // Heap root pointer
};


#endif


