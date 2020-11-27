#ifndef PRIM_H
#define PRIM_H

struct Prim
{
	int node;
	int from;
	int cost;

	Prim(){
		node = 0;
		from = 0;
		cost = 0;
	}

	Prim(int n, int f, int c){
		node = n;
		from = f;
		cost = c;
	}

	bool operator<(const Prim& rhs)const
	{
		return !(cost < rhs.cost);
	}

	bool operator>(const Prim& rhs)const
	{
		return !(cost > rhs.cost);
	}

};

#endif