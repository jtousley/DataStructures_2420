#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include "Graph.h"
#include "EdgeNode.h"

using namespace std;

class GraphNode
{
public:
	int NodeID;					//numerical ID of node, same as the name but stored as int for use in array
	char name;					//character ID of node, same as ID but stored as char for identification purposes
	int predecessorCt;			//number of nodes that point to this node
	EdgeNode* adj;				//successor list
	EdgeNode* predList;			//predecessor list
	bool visited;				//used for algorithms to prevent infinite loops

	//constructor
	GraphNode(int id = -1, char nameEle = 'x', EdgeNode* adjList = NULL){
		NodeID = id;
		name = nameEle;
		predecessorCt = 0;
		adj = adjList;
		predList = NULL;
		visited = false;
	}
};

#endif