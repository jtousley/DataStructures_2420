#include "PQLeftistHeap.h"

// insert element and re-heapify
void LeftistHeap::insert(ItemType &newVal)
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
ItemType LeftistHeap::deleteMax( )
{
	if(maxRoot == NULL){ return ItemType("error", -1); }
	ItemType toReturn = maxRoot->element;
	size--;

	maxRoot = RMerge(maxRoot->left, maxRoot->right);

	return toReturn;
}

Node* LeftistHeap::RMerge(Node* heapA, Node* heapB)
{
	static int mergeCount = 0;
	Node* toReturn = NULL;
	if(heapA == NULL) return heapB;
	if(heapB == NULL) return heapA;
	if(heapA->element.priority > heapB->element.priority){
		heapA->right = RMerge(heapA->right, heapB);
		heapA->npl = 1 + min(getNPL(heapA->left), getNPL(heapA->right));
		toReturn = heapA;
	}
	else{
		heapB->right = RMerge(heapB->right, heapA);
		heapB->npl = 1 + min(getNPL(heapB->left), getNPL(heapB->right));
		toReturn = heapB;
	}
	mergeCount++;
	//swap kids
	if(getNPL(toReturn->left) < getNPL(toReturn->right)){
		Node* temp = toReturn->left;
		toReturn->left = toReturn->right;
		toReturn->right = temp;
	}

	return toReturn;
}

// merge second into current heap
void LeftistHeap::merge(PQ * second)
{
	maxRoot = RMerge(maxRoot, dynamic_cast<LeftistHeap*>(second)->maxRoot);
	size += second->size;
	second->makeEmpty();
}

//Recursive helper print function
string LeftistHeap::printHeap(Node* t, int lines, string indent) const
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
string LeftistHeap::toString(int maxSize) const
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

//gets the null path length
int LeftistHeap::getNPL(Node* t)
{
	if(t == NULL) return -1;
	return t->npl;
}

