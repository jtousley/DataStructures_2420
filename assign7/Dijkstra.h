#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <string>

//structure used only for Dijkstra's algorithm
struct Dijkstra
{
	int node;				//int to represent the node
	int cost;				//weight to move between nodes
	std::string history;	//appended to remember the path taken

	Dijkstra(){
		node = 'x';
		cost = 0;
		history = "";
	}

	Dijkstra(int n, int c, std::string s){
		node = n;
		cost = c;
		history = s;
	}

	//this was created solely to allow the creation of an element starting with only one character
	Dijkstra(int n, int c, char s){
		node = n;
		cost = c;
		history = s;
	}

	//opposite to make stl heap a min heap
	bool operator<(const Dijkstra& rhs)const
	{
		return !(cost < rhs.cost);
	}

	//opposite to make stl heap a min heap
	bool operator>(const Dijkstra& rhs)const
	{
		return !(cost > rhs.cost);
	}

};

#endif