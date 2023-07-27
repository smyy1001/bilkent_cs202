/**
 * Title: Trees
 * Author Sumeyye Acar
 * Id: 22103640
 * Section: 01
 * Assignment: 2
 * Description: Header file of NgramTree ( contains the node class )
*/

#include <iostream>
using namespace std;


 // "node" header
class node {
public:
    node();
    ~node();

private:
    string str;
    int count;
    node* right;
    node* left;

    friend class NgramTree;
};


// "NgramTree" header
class NgramTree {
public:
    NgramTree();
    ~NgramTree();

    void addNgram( const string& );
    int getTotalNgramCount() const;
    bool isComplete() const;
    bool isFull() const;
    void generateTree( const string&, const int );

protected:
    void getTotalNgramCount( node*, int& ) const;
    bool isComplete( node* ) const;
    bool isFull( node* ) const;
    int getHeight( node* ) const;
    void deleteTree( node* );
    void inOrderTraversal( node*, ostream& ) const;

private:
    node* root;
    friend ostream& operator<<( ostream&, const NgramTree& );
};