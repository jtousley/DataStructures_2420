#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <iostream> 
#include <assert.h>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>


using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x  
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// Comparable  removeMin  -->  You are not allowed simply to do a find 
//                              Min and then a remove on that value.  
//                              That would require that you traverse the 
//                              tree twice  (once to find and once to delete).  
//                              We want a true removeMin that 
//                              only traverses in order to delete.
// ******************ERRORS********************************


//HINT:   The class you use as Comparable must have overloaded operators 
//for > == and <.
//        nullptr is another way of saying NULL.  It has some 
//        interesting properties for implicit conversions.
//        && is an "rvalue reference".  They are beyond the scope of 
//        this class.  A good explanation is at 
//        http://thbecker.net/articles/rvalue_references/section_01.html

template <typename Comparable>
class AvlTree
{
  public:
    AvlTree( ) : root{ nullptr }
      { }
    
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    AvlTree( AvlTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    ~AvlTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    AvlTree & operator=( AvlTree && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        assert(! isEmpty( ) );
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.

     */
    const Comparable & findMax( ) const
    {
        assert( !isEmpty( ) );
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & value ) const
    {
        return contains( value, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & value )
    {
        insert( value, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     * && is termed an rvalue reference. 
     * a good explanation is at 
http://thbecker.net/articles/rvalue_references/section_01.html
     */
    void insert( Comparable && value )
    {
        insert( std::move( value ), root );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    Comparable remove( const Comparable & value )
    {
        return remove( value, root );
    }

    string toString(string msg = "") const
    {
        return msg+'\n'+ toString(root,"");
    }

    //public member version of removing the smallest element in the tree, for user access
    Comparable removeMin(){ return removeMin(root);}
  
  private:
    struct AvlNode
    {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        
        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0)
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    }; //end struct class

    AvlNode *root;
    static const int ALLOWED_IMBALANCE = 1;

    //returns a string of the tree sideways, parent nodes are in "< >"
    string toString(AvlNode * t, string indent) const;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, AvlNode * & t );

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, AvlNode * & t );    

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */    
    Comparable remove( const Comparable & x, AvlNode * & t );

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t );

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode * findMin( AvlNode *t ) const;

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode * findMax( AvlNode *t ) const;

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, AvlNode *t ) const;

/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & item, AvlNode *t ) const
    {
        while( t != nullptr )
            if( item < t->element )
                t = t->left;
            else if( t->element < item )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( AvlNode * & t );

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( AvlNode *t ) const;

    /**
     * Internal method to clone subtree.
     */
    AvlNode * clone( AvlNode *t ) const;

    // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( AvlNode *t ) const;

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( AvlNode * & k1 );

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( AvlNode * & k2 );

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }

    Comparable removeMin(AvlNode* & t);           //remove the smallest element in the tree
};

    /**
     * Internal method to insert into a subtree.
     * item is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    template <typename Comparable>
    void AvlTree<Comparable>::insert( const Comparable & item, typename AvlTree<Comparable>::AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ item, nullptr, nullptr };
        else if( item < t->element || item == t->element )
            insert( item, t->left );
        else if( t->element < item )
            insert( item, t->right );
        
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * item is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    template <typename Comparable>
    void AvlTree<Comparable>::insert( Comparable && item, typename AvlTree<Comparable>::AvlNode * & t )
    {
        if( t == nullptr )
            t = new AvlNode{ std::move( item ), nullptr, nullptr };
        else if( item < t->element || item == t->element )
            insert( std::move( item ), t->left );
        else if( t->element < item )
            insert( std::move( item ), t->right );
        
        balance( t );
    }


    /**
     * Internal method to remove from a subtree.
     * item is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    template <typename Comparable>
    Comparable AvlTree<Comparable>::remove( const Comparable & item, typename AvlTree<Comparable>::AvlNode * & t )
    {
        Comparable temp;

        if( t == nullptr )
            return temp;   // Item not found; do nothing
        
        if( item < t->element )
            return remove( item, t->left );
        else if( t->element < item )
            return remove( item, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            return remove( t->element, t->right );
        }
        else
         {
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            temp=oldNode->element;
            delete oldNode;
        }
        
        balance( t );

        return temp;
    }

    // Assume t is balanced or within one of being balanced
    template <typename Comparable>
    void AvlTree<Comparable>::balance( typename AvlTree<Comparable>::AvlNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
                
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    template <typename Comparable>
    typename AvlTree<Comparable>::AvlNode * AvlTree<Comparable>::findMin( typename AvlTree<Comparable>::AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    template <typename Comparable>
    typename AvlTree<Comparable>::AvlNode * AvlTree<Comparable>::findMax( typename AvlTree<Comparable>::AvlNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }

    /**
     * Internal method to test if an item is in a subtree.
     * item is item to search for.
     * t is the node that roots the tree.
     */
    template <typename Comparable>
    bool AvlTree<Comparable>::contains( const Comparable & item, typename AvlTree<Comparable>::AvlNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( item < t->element )
            return contains( item , t->left );
        else if( t->element < item )
            return contains( item, t->right );
        else
            return true;    // Match
    }

    /**
     * Internal method to make subtree empty.
     */
    template <typename Comparable>
    void AvlTree<Comparable>::makeEmpty( typename AvlTree<Comparable>::AvlNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    template <typename Comparable>
    void AvlTree<Comparable>::printTree( typename AvlTree<Comparable>::AvlNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    template <typename Comparable>
    typename AvlTree<Comparable>::AvlNode * AvlTree<Comparable>::clone( typename AvlTree<Comparable>::AvlNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }

    // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    template <typename Comparable>
    int AvlTree<Comparable>::height( typename AvlTree<Comparable>::AvlNode *t ) const
    {
        return t == nullptr ? -1 : t->height;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    template <typename Comparable>
    void AvlTree<Comparable>::rotateWithLeftChild( typename AvlTree<Comparable>::AvlNode * & grandChild )
    {
        AvlNode *child = grandChild->left;
        grandChild->left = child->right;
        child->right = grandChild;
        grandChild->height = max( height( grandChild->left ), height( grandChild->right ) ) + 1;
        child->height = max( height( child->left ), grandChild->height ) + 1;
        grandChild = child;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    template <typename Comparable>
    void AvlTree<Comparable>::rotateWithRightChild( typename AvlTree<Comparable>::AvlNode * & child )
    {
        AvlNode *grandChild = child->right;
        child->right = grandChild->left;
        grandChild->left = child;
        child->height = max( height( child->left ), height( child->right ) ) + 1;
        grandChild->height = max( height( grandChild->right ), child->height ) + 1;
        child = grandChild;
    }

    //print the tree sideways (root is farthest left)
    template <typename Comparable>
    string AvlTree<Comparable>::toString(typename AvlTree<Comparable>::AvlNode *t, string indent) const
    {
        if(t==NULL)return "";
        stringstream ss;

        ss<<toString(t->left,indent+"  ");
        ss<<indent<<t->element;

        ss<<endl;
        ss<<toString(t->right,indent+"  ");
        
        return ss.str();
    }

    //remove the smallest element in the tree
    template <typename Comparable>
    Comparable AvlTree<Comparable>::removeMin(typename AvlTree<Comparable>::AvlNode* & rootNode)
    {
        AvlNode* parent;
        AvlNode* t=rootNode;
        Comparable temp;

        if(rootNode==NULL){
            string s="This tree was empty and you tried to remove the minimum value.\n";
            throw s;
        }

        if(rootNode->left==NULL)
            {
                temp=rootNode->element;
                rootNode=t->right;
                delete t;
                return temp;
            }

        while(t->left!=NULL){
            parent=t;
            t=t->left;
        }

        temp=t->element;
        parent->left=t->right;
        delete t;

        balance(rootNode);
        return temp;
    }

#endif
