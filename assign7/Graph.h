#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <sstream>
#include "GraphNode.h"
#include "EdgeNode.h"
#include "Dijkstra.h"
#include "Prim.h"

class Graph
{
protected:
	GraphNode* G;				//dynamically allocated array to store the graph
	int nodeCt;					//number of nodes in the graph

	string DFS(int a);			//depth first traversal of graph
	void Insert(int a, int b, int c);		//used by BuildGraph function to create the graph
public:
	Graph(int size);			//non-default constructor
	~Graph(){
		for(int i = 0; i < nodeCt; i ++){
			delete G[i].adj;
		}
		G = NULL;
	}
	//creates a graph based on specific rules from a txt file
	void BuildGraph(istream& fin, int graphSize, int edgeSize);	
	string orderTopological();				//returns a topological order of the graph
	string DFSPublic();						//returns a depth first traversal of the graph
	//returns the shortest path from the start node to all other nodes using Dijkstra's algorithm
	string pathShortestDistanceDijkstra(int);
	//returns a list of the edges of a minimal spanning tree, plus the total weight
	string minimalSpanningTreePrim(int);
};

#endif