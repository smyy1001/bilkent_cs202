/**
 * Title: avlTree.h
 * Author: Sumeyye Acar
 * Id: 22103640
 * Section: 1
 * Assignment: 4
 * Description: AVL Tree and it's node's Header
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <string>
#include <cctype>
#include <regex>
#include <locale>
#include <codecvt>

using namespace std;


// AVL Tree Node
class avlTreeNode {
public:
    avlTreeNode();
    avlTreeNode( string );
    ~avlTreeNode();
    
private:
    string word;
    int count;
    int height;
    avlTreeNode* right;
    avlTreeNode* left;

    friend class avlTree;
};


// AVl Tree
class avlTree {
public:
    avlTree();
    ~avlTree();

    void addWord( const string );
    void generateTree( const string );
    
    void printHeight( ostream& );
    void printTotalWordCount( ostream& );
    void printWordFrequencies( ostream& );
    void printMostFrequent( ostream& );
    void printLeastFrequent( ostream& );
    void printStandardDeviation( ostream& );

    void deleteTree( avlTreeNode*& );
    
protected:
    // helper of addWord()
    avlTreeNode* addWord( avlTreeNode*&, const string ) const;
    int calcBalanceFactor( avlTreeNode* ) const; 
    avlTreeNode* rotateL( avlTreeNode*& ) const;
    avlTreeNode* rotateR( avlTreeNode*& ) const;

    // helper of generateTree()
    string toLowerCase(const string& );

    // helper of printHeight()
    int calcHeight( avlTreeNode* ) const;

    // helper of printTotalWordCount()
    void calcTotalWordCount( avlTreeNode*, int& ) const;

    // helper of printWordFrequencies()
    void calcWordFrequencies( avlTreeNode*, ostream& ) const;

    // helper of printMostFrequent()
    void findMostFreq( avlTreeNode*, string&, string& ) const;
    void assignMostFreq( avlTreeNode*, string&, string& ) const;

    // helper of printLeastFrequent()
    void findLeastFreq( avlTreeNode*, string&, string& ) const;
    void assignLeastFreq( avlTreeNode*, string&, string& ) const;

    // helper of printStandardDeviation()
    double calcDeviation( avlTreeNode* ) const;
    void getAllFreq( avlTreeNode* , vector<int>& ) const;
    double meanValue( const vector<int>& ) const;
    double varianceValue( const vector<int>&, double ) const;


private:
    avlTreeNode* root;
};
