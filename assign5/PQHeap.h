// PQHeap.cpp - wdg 2008
#ifndef PQHeap_H
#define PQHeap_H

#include "PQ.h"

class PQHeap: public PQ 
{
public:
	static const int KIDS = 2;
	
	PQHeap(string name, int size);
	void insert(ItemType & x);  //    virtual void insert(ItemType & x )=0 ;
	ItemType deleteMax();
	int getCount() const;
	void merge(PQ *h);  // merges h into current heap  
	string toString(int size) const;
private:
	ItemType * heap;   // Heap Array
	int physicalSize;  // Physical size of heap

	int getBestKid(int bestVal,int curr, int size );
};


#endif


