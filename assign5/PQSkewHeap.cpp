#include "PQSkewHeap.h"

// insert element and re-heapify
void SkewHeap::insert(ItemType &newVal)
{
	if(maxRoot == NULL){
		maxRoot = new Node(newVal);
		size++;
		return;
	}
	Node* second = new Node(newVal);
	maxRoot = RMerge(maxRoot, second);
	size++;
}


// Delete maximum value, re-heapify, and return max element
ItemType SkewHeap::deleteMax( )
{
	if(size == 0){ return ItemType("error", -1); }
	ItemType toReturn = maxRoot->element;
	size--;

	maxRoot = RMerge(maxRoot->left, maxRoot->right);

	return toReturn;
}

//Recursive merge function
Node* SkewHeap::RMerge(Node* heapA, Node* heapB)
{
	Node* toReturn = NULL;
	if(heapA == NULL) return heapB;
	if(heapB == NULL) return heapA;
	if(heapA->element.priority > heapB->element.priority){
		heapA->right = RMerge(heapA->right, heapB);
		toReturn = heapA;
	}
	else{
		heapB->right = RMerge(heapB->right, heapA);
		toReturn = heapB;
	}
	//swap kids
	Node* temp = toReturn->left;
	toReturn->left = toReturn->right;
	toReturn->right = temp;

	return toReturn;
}

// merge second into current heap
void SkewHeap::merge(PQ * second)
{
	maxRoot = RMerge(maxRoot, dynamic_cast<SkewHeap*>(second)->maxRoot);
	size += second->size;
	second->makeEmpty();
}

//recursively print the heap
string SkewHeap::printHeap(Node* t, int lines, string indent) const
{
	if( t == NULL ){ return ""; }
	if(lines <= 0){ return ""; }	
	stringstream out;

	out << printHeap(t->right, lines - 1, indent + "   ");
	out << indent << t->element.toString() << endl;
	out << printHeap(t->left, lines - 1, indent + "   ");

	return out.str();
}

// Convert first "size: elements of PQ to a string.
string SkewHeap::toString(int maxSize) const
{   
	const int PERLINE = 5;
	stringstream out;
	out <<  name << "  current size=" << size << endl;

	if (maxSize > size)
		maxSize = size;

	if(maxSize == 0){ out<<endl; return out.str(); }

	out << printHeap(maxRoot, maxSize, "") << endl;

	return out.str();
}

