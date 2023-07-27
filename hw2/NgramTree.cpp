/**
 * Title: Trees
 * Author Sumeyye Acar
 * Id: 22103640
 * Section: 01
 * Assignment: 2
 * TDescription: Implementation of NgramTree and node class
*/

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>

using namespace std;

#include "NgramTree.h"

// Constructor of node class
node::node() {
    str = "";
    count = 0;
    left = NULL;
    right = NULL;
}

node::~node() {}

// Constructor of NgramTree class
NgramTree::NgramTree() {
    root = NULL;
}


// Destructor of NgramTree class
NgramTree::~NgramTree() {
    // delete the whole tree
    deleteTree( root );
}


void NgramTree::deleteTree( node* sTree ) {

    // deletes all nodes via preorder traversal
    if ( sTree != NULL) {
        deleteTree(sTree-> left);
        deleteTree(sTree-> right);

        delete sTree;
        sTree = NULL;
    }
} // end of deleteTree(node*)


void NgramTree::addNgram( const string& ngram ) {
    /*
     * If the Tree is empty, add directly
     * If not, find its place and check whether is it exists or not
     * If it does exist, increase the count; else, add the node
    */

    node** parent = NULL;
    node* current = root;

    bool exists = false;

    // empty tree
    if(current == NULL) {
        root = new node();
        root->str = ngram;
        root->count = 1;
    }
    // tree with at least one node
    else {
        while ( current != NULL ) {
            // the ngram already exists
            if( current->str.compare(ngram) == 0 ) {
                (current->count)++;
                exists = true;
                break;
            }
            else if( current->str.compare(ngram) < 0 ) {
                parent = &(current-> right);
                current = current -> right;
            }
            else {
                parent = &(current->left);
                current = current->left;
            }
        }

        // first occurrence of the ngram
        if(!exists) {
            (*parent) = new node();
            (*parent)->str = ngram;
            (*parent)->count = 1;

        }
    }

} // end of addNgram(string&)


int NgramTree::getTotalNgramCount() const {

    /*
     * calculates the number of nodes
     * By calling helper function getTotalNgramCount(node*, const int)
    */
    
    // total number of ngrams
    int total = 0;

    // call to helper function  
    getTotalNgramCount(root, total);

    // return total number of ngrams
    return total;

} // end of getTotalNgramCount()


void NgramTree::getTotalNgramCount( node* sTree, int& total) const{

    /*
     * counts the nodes via recursive preorder traversal
    */

    if(sTree != NULL ) {
        total++;
        getTotalNgramCount(sTree->left, total);
        getTotalNgramCount(sTree->right, total);
    }

} // end of getTotalNgramCount(node*, int&)


int NgramTree::getHeight( node* sTree ) const {

    /*
     * The height of a tree is equal to the maximum height of its subtrees +1
    */

    int height = 0;

    // assessing maximum height of the subtrees recursively
    if( sTree != NULL ) {
        height = 1+ max( getHeight( sTree->right ), getHeight( sTree->left ) );
    }

    return height;

} // end of getHeight(node*)


bool NgramTree::isComplete() const {

    /*
     * calls the helper function isComplete( node* ) const
    */

    return isComplete( root );
    
} // end of isComplete()


bool NgramTree::isComplete(node* sTree ) const {
    /*
    * A complete binary tree is a binary tree where; 
        * Every level is filled in completely (except maybe the last level)
        * Any missing node can be only in the last level and must be toward the right side
    */

   if( sTree != NULL ) {
        int l_height = getHeight( sTree->left );
        int r_height = getHeight( sTree->right );

        if(l_height != r_height && l_height != r_height+1) {
            return false;
        }

        if( l_height == r_height ){
            if(isFull( sTree->left )) { return isComplete(sTree->right); }
            return false;
        } else {
            if( isFull( sTree->right ) ) { return isComplete( sTree->left ); }
            return false;
        }

        return true;
    }

} // end of isComplete(node*)


bool NgramTree::isFull() const {

    /*
     * calls the helper function isFull( node* ) const
    */

    return isFull( root );

} // end of isFull()


bool NgramTree::isFull( node* sTree) const {
    /*
     * The total number of nodes in a full tree:
     * 2^(height)-1
    */

    if( sTree != NULL ) {

        int node_count = 0;
        getTotalNgramCount( sTree, node_count );

        return (node_count == (pow( 2, getHeight(sTree)) - 1));
    }

    // a tree is full if it is empty
    return true;
} // end of isFull(node*)


void NgramTree::generateTree( const string& fileName, const int n ) {

    /*
     * First, read from the given file
     * Then, add the ngrams to the tree using addNgram( string& ) method
    */

    ifstream infile;
    infile.open( fileName.c_str() );
    string lexis;

    while( infile >> lexis ) {
        
        // the length of any ngram can not be greater than the word's length itself
        if( lexis.length() >= n ) {
            for( int i = 0; i < lexis.length() - n +1; i ++ ) {
                addNgram( lexis.substr(i, n) );
            }
        }
    }
   
} // end of generateTree(string&, int)


void NgramTree::inOrderTraversal(node* sTree, ostream& o) const {

    /*
     * performs recursive inOrderTraversal and prints nodes' items and frequencies
    */

    if (sTree == nullptr) {
        return;
    }

    inOrderTraversal(sTree->left, o);
    o << "\"" << sTree->str << "\" appears " << sTree->count << " time(s)" << endl;
    inOrderTraversal(sTree->right, o);
    
} // end of inOrderTraversal(node*, ostream&)


ostream& operator<<( ostream& o, const NgramTree& tree) {
    /*
     * Traverses the all node items in alphabetic order (inOrderTraversal)
    */

    tree.inOrderTraversal(tree.root, o);
    return o;

} // end of operator<<(ostream&, NgramTree&)

// end of NgramTree.cpp class