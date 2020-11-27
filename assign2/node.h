#ifndef NODE_H
#define NODE_H

#include "bst.h"

using namespace std;

template <class Etype>
class TreeNode
{
public:
	Etype element;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
	TreeNode(Etype e = 0, TreeNode *l = NULL, TreeNode *r = NULL, TreeNode *p = NULL) :
		element(e), left(l), right(r), parent(p) { }
};

#endif