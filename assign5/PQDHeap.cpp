#include "PQDHeap.h"

//Create a heap with maximum size "physicalSize" 
PQDHeap::PQDHeap(string name,int physicalSize ) 
{  
	this->name = name;
	size=0;
	heap = new ItemType[physicalSize];
	this->physicalSize = physicalSize;
}



// insert element and re-heapify
void PQDHeap::insert(ItemType &newVal)
{  
	int curr = size;
	assert(size < physicalSize);
	int parent = (curr-1)/KIDS; // round down
	while( curr > 0 && newVal.priority > heap[parent].priority ) {
		heap[curr] = heap[parent];
		curr = parent;
		parent = (curr-1)/KIDS;
	}
	heap[curr] = newVal;
	size++;
}


// Delete maximum value, re-heapify, and return max element
ItemType PQDHeap::deleteMax( )
{  	
	if (size==0)
		return ItemType("error", -1);
	ItemType toReturn = heap[0];
	size--;
	ItemType currVal = heap[size];
	int curr = 0;
	int left = 1;
	int right = left+1;
	int child1=0;
	int child2 = child1 +1;
	int child3 = child2 + 1;
	int child4 = child3 + 1;
	int child5 = child4 + 1;
	int child6 = child5 + 1;
	int child7 = child6 + 1;
	int child8 = child7 + 1;
	while( ( child1 < size && currVal.priority < heap[child1].priority) ||
		( child2 < size && currVal.priority < heap[child2].priority ) ||
		( child3 < size && currVal.priority < heap[child3].priority ) ||
		( child4 < size && currVal.priority < heap[child4].priority ) ||
		( child5 < size && currVal.priority < heap[child5].priority ) ||
		( child6 < size && currVal.priority < heap[child6].priority ) ||
		( child7 < size && currVal.priority < heap[child7].priority ) ||
		( child8 < size && currVal.priority < heap[child8].priority ) ){
			
			int bestChild = child1;

			if( child2 < size && heap[child2].priority > heap[child1].priority ){ bestChild = child2; }
			if( child3 < size && heap[child3].priority > heap[child2].priority && 
				heap[bestChild].priority < heap[child3].priority ){ bestChild = child3; }
			if( child4 < size && heap[child4].priority > heap[child3].priority &&
				heap[bestChild].priority < heap[child4].priority ){ bestChild = child4; }
			if( child5 < size && heap[child5].priority > heap[child4].priority &&
				heap[bestChild].priority < heap[child5].priority ){ bestChild = child5; }
			if( child6 < size && heap[child6].priority > heap[child5].priority &&
				heap[bestChild].priority < heap[child6].priority ){ bestChild = child6; }
			if( child7 < size && heap[child7].priority > heap[child6].priority &&
				heap[bestChild].priority < heap[child7].priority ){ bestChild = child7; }
			if( child8 < size && heap[child8].priority > heap[child7].priority &&
				heap[bestChild].priority < heap[child8].priority ){ bestChild = child8; }

			heap[curr] = heap[bestChild];
			curr = bestChild;
			child1 = KIDS * bestChild + 1;
			child2 = child1 + 1;
			child3 = child2 + 1;
			child4 = child3 + 1;
			child5 = child4 + 1;
			child6 = child5 + 1;
			child7 = child6 + 1;
			child8 = child7 + 1;
	} // endwhile

	heap[curr] = currVal;
	return toReturn;
}


// merge second into current  heap
void PQDHeap::merge(PQ * second)
{  
	for (int i = 0; i < second->getSize(); i++)
		insert(dynamic_cast<PQDHeap*>(second)->heap[i]);
	second->makeEmpty();
}

// Convert first "size: elements of PQ to a string.
string PQDHeap::toString(int maxSize) const
{   const int PERLINE = 5;
	stringstream out;
	out <<  name << "  current size=" << size;
	if (maxSize > size)
		maxSize = size;

	for (int i=0; i <maxSize; i ++)
	{  
		if (i%PERLINE==0) out << endl;
		out << heap[i].toString() << "\t";
	}
	out << endl;

	return out.str();
}