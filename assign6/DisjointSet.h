#ifndef DISJOINTSET_H
#define DISJOINTSET_H
#include <vector>
#include <iostream>

class DisjointSet{
private:
	std::vector<int> groupArray;
	std::vector<int> antiGroupArray;

public:
	DisjointSet(int size);

	void setAntiValue(int where, int value){ antiGroupArray[where] = value; }

	int getGroupValue(int where){ return groupArray[where]; }
	int getAntiValue(int where){ return antiGroupArray[where]; }

	int getSizeGroup(){ return groupArray.size(); }
	int getSizeAnti(){ return antiGroupArray.size(); }

	void Union(int a, int b);
	int Find(int a);
};

#endif