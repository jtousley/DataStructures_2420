/*
Jonathan Tousley
A01908436
Assignment 2 - Binary Search Tree
*/

#ifndef BST_H
#define BST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <assert.h>
#include "node.h"
using namespace std;

template <class Etype>
class BinarySearchTree
{
protected:
	TreeNode<Etype> *root;

	bool insert(Etype & x, TreeNode<Etype> * & t, TreeNode<Etype>*  p);		//recursive insert function of type Etype
	string toString(TreeNode<Etype> * t, string indent) const;				//returns a string of the tree sideways, parent nodes are in "< >"
	string traverse(TreeNode<Etype> * t) const;								//returns a string of of the tree 'in order'
	TreeNode<Etype> * minimumEle(TreeNode<Etype> * & t);					//returns a pointer to the smallest element in the tree
	TreeNode<Etype> * maximumEle(TreeNode<Etype> * & t);					//returns a pointer to the largest element in the tree
	TreeNode<Etype> * predecessor(TreeNode<Etype> * & t);					//returns a pointer to the next smallest element from t
	TreeNode<Etype> * findKthInOrder(TreeNode<Etype> * t, int &k);			//returns a pointer to the node of the 'k'th smallest element
	TreeNode<Etype> * find(TreeNode<Etype> * curr, Etype value);			//returns a pointer to the node which contains 'value'
	TreeNode<Etype> * leastCommonAncestor(TreeNode <Etype>* r, Etype a, Etype b);	//returns a pointer to the least common ancestor of values a and b

	int nodesInLevel(TreeNode<Etype> * & t, int level);		//returns the number of nodes on level 'level'
	int count(TreeNode<Etype> *t);		//returns the number of nodes in the tree
	int width(TreeNode<Etype> * t, int &height); 	//returns the longest distance between any two nodes in the tree
	int countFringe(TreeNode<Etype> *t) const;		//returns the number of nodes on the tree with no children - the 'fringes'
	
	bool isIsomorphic(TreeNode<Etype> *t1, TreeNode<Etype> *t2);	//returns whether or not t1 is isomorphic with t2
	bool isQuasiIsomorphic(TreeNode<Etype> *t1, TreeNode<Etype> *t2);	//returns whether or not t1 is quasi-isomorphic with t2
	
	void makeEmpty(TreeNode<Etype> *&t);	//empties tree t
	
public:
	BinarySearchTree() : root(NULL) { }	//constructor
	bool isIsomorphic(BinarySearchTree<Etype> t) { return isIsomorphic(root, t.root); }		//public member function that allows the user access to this ability
	bool isQuasiIsomorphic(BinarySearchTree<Etype> t) { return isQuasiIsomorphic(root, t.root); }	//and so on...
	void makeEmpty() { makeEmpty(root); return; }	
	int countFringe() { return countFringe(root); }
	int count() { return count(root); }
	int width() { int height=0; return width(root, height); }
	int nodesInLevel(int level) { return nodesInLevel(root, level); }
	void makeTree(vector<Etype> all);	//creates a binary search tree with the vector

	TreeNode<Etype> * minimumEle(){ return minimumEle(root);} //public member function that allows the user access to this ability
	TreeNode<Etype> * maximumEle(){return maximumEle(root);}	//and so on...
	TreeNode<Etype> * successor(){ return minimumEle();}
	string toString(string msg = "") const {return msg + "\n" + toString(root, "  ");}	//allows the user to display a message with the tree
	string traverse(string msg) const {return msg + "\n" + traverse(root);	}	//allows the user to display a message with the tree

	virtual int insert(Etype & x) { return insert(x, root, NULL); }	//public member function that allows the user access to this ability
	TreeNode<Etype> * clone(TreeNode<Etype> *t, TreeNode<Etype> *p) const;	//returns a pointer to the root of a new tree, cloned from 'p'

	TreeNode<Etype>* leastCommonAncestor(Etype a, Etype b) {  // order the elements so we know which is smaller
		if (a < b) return leastCommonAncestor(root, a, b);
		return leastCommonAncestor(root, b, a);
	}

	//public member function for private function 'predecessor'
	Etype predecessor(Etype value)
	{
		TreeNode<Etype> *curr = find(root, value);
		TreeNode<Etype> * p = predecessor(curr);
		if (p != NULL) return p->element;
		else return 0;
	}

	//public member function for private function 'findKthInOrder'
	int findKthInOrder(int k) {
		TreeNode<Etype>* t = findKthInOrder(root, k);
		if (t == NULL) return -999;
		return t->element;
	}
};

template <class Etype>
TreeNode<Etype>*  BinarySearchTree<Etype>::leastCommonAncestor(TreeNode<Etype>* t, Etype a, Etype b)
{
	if (t == NULL || a>b) { return NULL; }
	if (a <= t->element && b >= t->element) return r;
	if (b <= t->element) return leastCommonAncestor(t->left, a, b);

	return leastCommonAncestor(t->right, a, b);
}

//returns whether or not the tree is isomorphic
//complexity O(n)
template <class Etype>
bool BinarySearchTree<Etype>::isIsomorphic(TreeNode<Etype>* t1, TreeNode<Etype>* t2)
{
	if(t1==NULL && t2==NULL)return true;
	if(t1==NULL || t2==NULL)return false;
	return isIsomorphic(t1->left,t2->left) && isIsomorphic(t1->right,t2->right);
}

//returns whether or not the tree is quasi-isomorphic
//complexity O(n)
template <class Etype>
bool BinarySearchTree<Etype>::isQuasiIsomorphic(TreeNode<Etype>* t1, TreeNode<Etype>* t2)
{
	if(t1==NULL && t2==NULL)return true;
	if(t1==NULL || t2==NULL)return false;

	return (isQuasiIsomorphic(t1->right,t2->right) && isQuasiIsomorphic(t1->left,t1->right)) || 
			(isQuasiIsomorphic(t1->left,t2->right) && isQuasiIsomorphic(t1->right,t2->left));
}

//returns the longest distance between the farthest nodes on the tree (diameter)
//complexity O(n)
template <class Etype>
int BinarySearchTree<Etype>::width(TreeNode<Etype> *t, int &height)
{
	if(t==NULL)return 0;
	int widthl,widthr,htr=0,htl=0;

	widthl=width(t->left,htl);
	widthr=width(t->right,htr);
	height=max(widthl,widthr)+1;
	return max(htr+htl+1,max(widthl,widthr));
}

//returns the number of nodes on the tree
//complexity O(n)
template <class Etype>
int BinarySearchTree<Etype>::count(TreeNode<Etype>* t)
{
	if(t==NULL)return 0;
	return 1+count(t->left)+count(t->right);
}

//returns a pointer to the 'kth' element from the smallest value, NULL if none
//complexity O(log n)
template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::findKthInOrder(TreeNode<Etype>* t, int& k)
{
	if(t==NULL)return NULL;
	TreeNode<Etype>* result = findKthInOrder(t->left,k);
	if(result!=NULL) return result;
	--k;
	if(k < 1)return t;
	return findKthInOrder(t->right,k);
}

//returns the number of nodes on level 'level'
//complexity O(1)
template <class Etype>
int BinarySearchTree<Etype>::nodesInLevel(TreeNode<Etype>*& t, int level)
{
	if(t==NULL)return 0;
	if(level==0)return 1;
	return nodesInLevel(t->left,level-1)+nodesInLevel(t->right,level-1);
}

//returns a pointer to the smallest element on the tree
//complexity O(n)
template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::minimumEle(TreeNode<Etype> * & t)
{
	if (t->left != NULL)
		return minimumEle(t->left);
	return t;

}

//returns a string of the nodes' elements in ascending order
//complexity O(n)
template <class Etype>
string BinarySearchTree<Etype>::traverse(TreeNode<Etype> *t) const
{
	stringstream ss;
	if (t == NULL) return "";
	ss << traverse(t->left);
	ss << t->element << " ";
	ss << traverse(t->right);
	return ss.str();
}

//returns a pointer to the largest element on the tree
//complexity O(n)
template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::maximumEle(TreeNode<Etype> * & t)
{
	if (t->right != NULL) return maximumEle(t->right);
	return t;
}

//returns a pointer to the node just smaller than me
//complexity O(1)
template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::predecessor(TreeNode<Etype> * & t)
{
	if(t==NULL)return NULL;
	TreeNode<Etype>* result=t->left;
	if(result!=NULL){
		while(result->right!=NULL){result=result->right;}
		return result;
	}

	result=t->parent;
	while(result!=NULL){
		if(result->parent!=NULL){
			if(result==result->parent->right)
				return result->parent;
		}
		result=result->parent;
	}
	return result;
}

//returns a string of the tree on it's side
//complexity O(n)
template <class Etype>
string BinarySearchTree<Etype>::toString(TreeNode<Etype> *t, string indent) const
{
	if(t==NULL)return "";
	stringstream ss;

	ss<<toString(t->left,indent+"  ");
	ss<<indent<<t->element;

	if(t->parent!=NULL){
		ss<<"<"<<t->parent->element<<">";
	}
	else{
		ss<<"<no parent>";
	}

	ss<<endl;
	ss<<toString(t->right,indent+"  ");
	
	return ss.str();
}

// Return true if insertion is successful
template <class Etype>
bool BinarySearchTree<Etype>::insert(Etype & x, TreeNode<Etype> * & t, TreeNode<Etype> *  p)
{
	if (t == NULL)
	{  // cout << "inserting " << x << endl;
		t = new TreeNode<Etype>(x, NULL, NULL, p);
		if (t == NULL) return false;
		return true;
	}
	if (x < t->element) return insert(x, t->left, t);
	if (x > t->element) return insert(x, t->right, t);
	// cout << "Warning, duplicate ignored " << x << endl;

	return false;  // does not allow duplicate insertions
}

template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::find(TreeNode<Etype> * curr, Etype value)
{
	if (curr == NULL) return NULL;
	if (curr->element == value)
		return curr;
	if (value < curr->element) return find(curr->left, value);
	return find(curr->right, value);
}

template <class Etype>
void BinarySearchTree<Etype>::makeTree(vector<Etype> all)
{
	makeEmpty(root);
	for (unsigned i = 0; i < all.size(); i++)
		insert(all[i]);
	return;
}

//removes all elements of the tree
//complexity O(n)
template <class Etype>
void BinarySearchTree<Etype>::makeEmpty(TreeNode<Etype> *&t)
{
	if(t==NULL)return;
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
	t=NULL;
	return;
}

template <class Etype>
TreeNode<Etype> * BinarySearchTree<Etype>::clone(TreeNode<Etype> *t, TreeNode<Etype> *parent) const
{
	if (t == NULL)
		return NULL;
	TreeNode<Etype>* newNode = new TreeNode <Etype> { t->element, NULL, NULL, parent };
	newNode->left = clone(t->left, newNode);
	newNode->right = clone(t->right, newNode);
	return newNode;
}

//returns a count of the nodes with no children (orphans)
//complexity O(n)
template <class Etype>
int BinarySearchTree<Etype>::countFringe(TreeNode<Etype> *t) const
{
	if(t==NULL)return 0;
	int count=0;
	if(t->left==NULL && t->right==NULL)count++;
	return count+countFringe(t->left)+countFringe(t->right);
}

#endif