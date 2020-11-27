#include "DisjointSet.h"

using namespace std;

DisjointSet::DisjointSet(int size)
{
	for(int i = 0; i < size + 1; i++){
		groupArray.push_back(-1);
		antiGroupArray.push_back(-1);
	}
}

//merges the groups of first and second
void DisjointSet::Union(int first, int second)
{
	int groupA = Find(first);
	int groupB = Find(second);

	if(groupA == groupB){ return; }

	if(groupArray[groupA] < groupArray[groupB]){
		groupArray[groupB] = groupA;
	}
	else{
		groupArray[groupA] = groupB;
	}
}

//returns the parent of the group value is in
int DisjointSet::Find(int value)
{
	if(groupArray[value] < 0 ) { return value; }
	groupArray[value] = Find(groupArray[value]);

	return groupArray[value];
}

