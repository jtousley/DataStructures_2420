#ifndef EDGENODE_H
#define EDGENODE_H

#include "GraphNode.h"

using namespace std;

class EdgeNode
{
public:
	int toNode;			//node the edge points to
	int fromNode;		//node the edge start at
	int distance;		//edge weight
	EdgeNode* next;		//recursive method for storing graphnode successors

	//constructor
	EdgeNode(int from = -1, int to = -1, int dist = 0, EdgeNode* nextEdge = NULL){
		fromNode = from;
		toNode = to;
		distance = dist;
		next = nextEdge;
	}
};

#endif