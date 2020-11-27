#include "Graph.h"

using namespace std;

//non-default constructor
Graph::Graph(int size)
{
	G = new GraphNode[size];
	nodeCt = size;
}

//protected insertion function used only by BuildGraph
void Graph::Insert(int nodeA, int nodeB, int weight)
{
	//build successor list
	EdgeNode* tempSucc = G[nodeA].adj;
	G[nodeA].adj = new EdgeNode(nodeA, nodeB, weight);
	G[nodeA].adj->next = tempSucc;

	G[nodeB].predecessorCt++;

	//build a predecessor list, for use when ignoring direction
	EdgeNode* tempPred = G[nodeB].predList;
	G[nodeB].predList = new EdgeNode(nodeB, nodeA, weight);
	G[nodeB].predList->next = tempPred;
}

//Builds a graph from a txt file, requires strict spacing rules
void Graph::BuildGraph(istream& fin, int graphSize, int edgeSize)
{
	char nodeA, nodeB;
	int firstNode, secondNode;
	int edgeWeight;

	for(int i = 0; i < graphSize; i++){
		G[i].NodeID = i;
		G[i].name = i + 'A';
	}	
	for(int i = 0; i < edgeSize; i++){
		fin >> nodeA >> nodeB >> edgeWeight;
		firstNode = nodeA - 'A';
		secondNode = nodeB - 'A';

		Insert(firstNode, secondNode, edgeWeight);
	}
}

//returns a string of a topological order
//uses a queue and puts all elements with no in degree on, else returns that none exists
string Graph::orderTopological()
{
	queue<int> Q;
	int i = 0;
	int inDegree[nodeCt];

	//find a node to start with, otherwise no ordering exists
	for(; i < nodeCt; i++){
		inDegree[i] = G[i].predecessorCt;
		if(inDegree[i] == 0){ Q.push(G[i].NodeID); }
	}
	if(Q.empty()) { return "No topological ordering exists!\n"; }

	//set the visited flag -- still O(n)
	for(int j = 0; j < nodeCt; j++){
		G[j].visited = false;
	}


	//Find the ordering
	string ordering = "Topological ordering:\n";
	while(!Q.empty()){
		int dequeued = Q.front();
		Q.pop();

		ordering = ordering + G[dequeued].name + " ";
		G[dequeued].visited = true;

		for(EdgeNode* e = G[dequeued].adj; e != NULL; e=e->next){
			if(!G[e->toNode].visited && --inDegree[e->toNode] == 0){ 
				Q.push(G[e->toNode].NodeID);
			}
		}
	}

	return ordering + '\n';
}

//public access function to create a string of the graph, depth first traversal
//gives priority to nodes with no indegree
string Graph::DFSPublic(){
	stringstream ss;
	bool hasBegun = false;

	ss << "Depth First Traversal of node ";

	//clear visited flags
	for(int i = 0; i < nodeCt; i++){
		G[i].visited = false;
	}

	//perform a depth first traversal starting with nodes without predeccessors
	for(int j = 0; j < nodeCt; j++){
		if(G[j].predecessorCt == 0){
			if(!hasBegun){
				ss << G[j].name << endl;
				hasBegun = true;
			}
			ss << DFS(j);
		}
	}

	//in case this is a cyclic graph, or there are unconnected nodes
	for(int i = 0; i < nodeCt; i++){
		if(!G[i].visited){ 
			if(!hasBegun){
				ss << G[i].name << endl;
				hasBegun = true;
			}
			ss << DFS(i); 
		}
	}

	ss << endl;
	return ss.str();
}

//protected depth first traversal using recursion and preorder
string Graph::DFS(int node){
	
	string toReturn;
	if(G[node].visited){ return ""; }
	G[node].visited = true;

	toReturn = toReturn + G[node].name + " ";
	for(EdgeNode* e = G[node].adj; e != NULL; e=e->next){
		if(!G[e->toNode].visited){ toReturn += DFS(e->toNode); }
	}

	return toReturn;
}

//find the shortest path from node 'N' to all other nodes, listing the node name, total weight, and the path taken
string Graph::pathShortestDistanceDijkstra(int N)
{
	int numberFound = 0;
	priority_queue<Dijkstra> PQ;
	Dijkstra queue(N, 0, G[N].name);
	stringstream ss;

	ss << "Shortest distance from node " << G[N].name << " to:\n";

	//clear visited flags
	for(int i = 0; i < nodeCt; i++){
		G[i].visited = false;
	}

	PQ.push(queue);
	while(numberFound < nodeCt && !PQ.empty()){
		queue = PQ.top();
		PQ.pop();

		if(!G[queue.node].visited){ 
			G[queue.node].visited = true;
			numberFound++;
			ss << "Node: " << G[queue.node].name
				<< " Cost: " << queue.cost 
				<< " Path: " << queue.history << endl;

			//check the nodes this node points to
			for(EdgeNode* e = G[queue.node].adj; e != NULL; e = e->next){
				if(!G[e->toNode].visited){ 
					PQ.push(Dijkstra(e->toNode, queue.cost + e->distance, queue.history + "->" + G[e->toNode].name)); 
				}
			} // for each successor

			//check all predecessors, since direction is unimportant
			for(EdgeNode* e = G[queue.node].predList; e != NULL; e = e->next){
				if(!G[e->toNode].visited){
					PQ.push(Dijkstra(e->toNode, queue.cost + e->distance, queue.history + "->" + G[e->toNode].name));
				}
			} // for each predecessor
		} // if not visited
	} // while

	ss << endl;
	return ss.str();
}

//returns a minimal spanning tree with all edges listed, plus the total weight
string Graph::minimalSpanningTreePrim(int start){
	priority_queue<Prim> PQ;
	stringstream ss;
	Prim dequeued;
	int totalWeight = 0;

	ss << "Spanning tree starting at node " << G[start].name << endl;

	for(int i = 0; i < nodeCt; i++){
		G[i].visited = false;
	}

	PQ.push(Prim(start, start, 0));
	while(!PQ.empty()){
		dequeued = PQ.top();
		PQ.pop();

		if(!G[dequeued.node].visited){
			G[dequeued.node].visited = true;			
			
			if(dequeued.node != start){
				ss << "Edge: " << G[dequeued.from].name 
					<< " to " << G[dequeued.node].name 
					<< " Weight: " << dequeued.cost << endl;
				totalWeight += dequeued.cost;
			}

			for(EdgeNode* e = G[dequeued.node].adj; e != NULL; e = e->next){
				if(!G[e->toNode].visited){
					PQ.push(Prim(e->toNode, e->fromNode, e->distance));
				} // if
			} // for each successor

			for(EdgeNode* e = G[dequeued.node].predList; e != NULL; e = e->next){
				if(!G[e->toNode].visited){
					PQ.push(Prim(e->toNode, e->fromNode, e->distance));
				} // if
			} // for each predecessor

		} // if not visited
	}

	ss << "Total weight: " << totalWeight << endl << endl;

	return ss.str();
}
