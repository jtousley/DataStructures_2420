// PQDHeap.cpp - wdg 2008
#ifndef PQDHeap_H
#define PQDHeap_H

#include "PQ.h"

class PQDHeap: public PQ 
{
public:
	static const int KIDS = 8;
	PQDHeap(string name, int size);
	void insert(ItemType & x);  //    virtual void insert(ItemType & x )=0 ;
	ItemType deleteMax();
	int getCount() const;
	void merge(PQ *h);  // merges h into current heap  
	string toString(int size) const;
private:
	int getBestKid(int bestVal,int curr, int size );
	ItemType * heap;   // Heap Array
	int physicalSize;  // Physical size of heap
};


#endif


