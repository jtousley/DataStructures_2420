#include "Graph.h"

using namespace std;

int main(){
	ifstream fin;
	int graphSize, edgeSize;
	fin.open("prog7.txt");

	fin >> graphSize >> edgeSize;
	Graph firstGraph(graphSize);

	firstGraph.BuildGraph(fin, graphSize, edgeSize);

	cout << "For prog7.txt:\n";
	cout << firstGraph.orderTopological() << endl;
	cout << firstGraph.DFSPublic() << endl;
	cout << firstGraph.pathShortestDistanceDijkstra(0);
	cout << firstGraph.minimalSpanningTreePrim(0);

	fin.close();

	fin.open("prog7b.txt");

	fin >> graphSize >> edgeSize;
	Graph secondGraph(graphSize);

	secondGraph.BuildGraph(fin, graphSize, edgeSize);

	cout << "For prog7b.txt:\n";
	cout << secondGraph.orderTopological() << endl;
	cout << secondGraph.DFSPublic() << endl;
	cout << secondGraph.pathShortestDistanceDijkstra(0);
	cout << secondGraph.minimalSpanningTreePrim(0);

	fin.close();

	char c;
	cout << "Press any key to continue...";
	cin.get(c);

	return 0;
}