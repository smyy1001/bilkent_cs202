/**
 * Title: avlTree.cpp
 * Author: Sumeyye Acar
 * Id: 22103640
 * Section: 1
 * Assignment: 4
 * Description: AVL Tree Implementation
 */

#include "avlTree.h"
using namespace std;


// Node Constructor 1
avlTreeNode::avlTreeNode() {
    word = "";
    count = 0;
    height = 0;
    right = nullptr;
    left = nullptr;
}
// Node Constructor 2
avlTreeNode::avlTreeNode( string w ) {
    word = w;
    count = 1;
    height = 1;
    right = nullptr;
    left = nullptr;
}
// Node Destructor
avlTreeNode::~avlTreeNode() {}


// Node Constructor
avlTree::avlTree() {
    root = nullptr;
}
// AVL Tree Destructor
avlTree::~avlTree() {
    deleteTree( root );
}



int avlTree::calcHeight(avlTreeNode* node) const {
    if (node == nullptr) return 0;
    return node->height;
}
void avlTree::printHeight( ostream& o ) {
    o << "Tree Height: " << calcHeight( root ) << endl << endl;
}// end of printHeight()



int avlTree::calcBalanceFactor( avlTreeNode* node) const {
    if (node == nullptr) { return 0; }
    return calcHeight(node->left) - calcHeight(node->right);
}
avlTreeNode* avlTree::rotateL( avlTreeNode*& n ) const {
    avlTreeNode* t1 = n->right;
    avlTreeNode* t2 = t1->left;

    t1->left = n;
    n->right = t2;

    n->height = 1 + max(calcHeight(n->left), calcHeight(n->right));
    t1->height = 1 + max(calcHeight(t1->left), calcHeight(t1->right));

    return t1;
}
avlTreeNode* avlTree::rotateR( avlTreeNode*& n ) const {
    avlTreeNode* t1 = n->left;
    avlTreeNode* t2 = t1->right;

    t1->right = n;
    n->left = t2;

    n->height = 1 + max(calcHeight(n->left), calcHeight(n->right));
    t1->height = 1 + max(calcHeight(t1->left), calcHeight(t1->right));

    return t1;
}
avlTreeNode* avlTree::addWord( avlTreeNode*& node, const string key ) const {
    if (node == nullptr) {
        return new avlTreeNode(key);
    }
    if (key < node->word) {
        node->left = addWord(node->left, key);
    } 
    else if (key > node->word) {
        node->right = addWord(node->right, key);
    } 
    else {
        node->count++;
        return node;
    }

    node->height = 1 + max(calcHeight(node->left), calcHeight(node->right));

    int balance = calcBalanceFactor(node);

    // Left-Left Case
    if (balance > 1 && key < node->left->word) {
        return rotateR(node);
    }

    // Right-Right Case
    if (balance < -1 && key > node->right->word) {
        return rotateL(node);
    }

    // Left-Right Case
    if (balance > 1 && key > node->left->word) {
        node->left = rotateL(node->left);
        return rotateR(node);
    }

    // Right-Left Case
    if (balance < -1 && key < node->right->word) {
        node->right = rotateR(node->right);
        return rotateL(node);
    }

    return node;
}
void avlTree::addWord( const string key ) {
    root = addWord( root, key );
} // end of addWord(const string)



string avlTree::toLowerCase(const string& str) {
    string result = str;
    for (char& ch : result) {
        ch = tolower(static_cast<unsigned char>(ch));
    }
    return result;
}
void avlTree::generateTree( const string fileName ) {

    /*
     * First, read from the given file
     * Then, separate each word 
     * Finally, add the words to the tree using addWord method
    */

    ifstream infile;
    infile.open( fileName.c_str() );
    
    infile.imbue(locale(infile.getloc(), new codecvt_utf8<wchar_t>));

    if ( !infile.is_open() ) {
        cout << "Error occurred while opening " << fileName << endl;
    }
    string token;
    while ( infile >> token ) {
        
        string currentToken = "";
        for (char ch : token) {
            if ( isalnum( ch ) ) {
                currentToken += ch;
            }
            else {
                if(!currentToken.empty()) {
                    addWord( toLowerCase( currentToken ) );
                }
                currentToken = "";
            }
        }

        if (!currentToken.empty()) {
            addWord( toLowerCase( currentToken ) );
        }
    }

    infile.close();
   
} // end of generateTree(string)



void avlTree::calcTotalWordCount( avlTreeNode* t, int& total) const{

    /*
     * counts the nodes via recursive preorder traversal
    */

    if(t != nullptr ) {
        total++;
        calcTotalWordCount(t->left, total);
        calcTotalWordCount(t->right, total);
    }

}
void avlTree::printTotalWordCount( ostream& o ) {

    /*
     * print the number of nodes
     * calculates the node code by calling helper function
    */
    
    // total number of nodes
    int total = 0;

    // call to helper function  
    calcTotalWordCount(root, total);

    o << "Total Word Count: " << total << endl << endl;


} // end of printTotalWordCount(ostream&)




void avlTree::calcWordFrequencies( avlTreeNode* t, ostream& o ) const {

    /*
     * performs recursive inOrderTraversal and prints nodes' items and frequencies
    */

    if (t == nullptr) {
        return;
    }

    calcWordFrequencies( t->left, o );
    o  << t->word << ": " << t->count << endl;
    calcWordFrequencies( t->right, o );
    
}
void avlTree::printWordFrequencies( ostream& o ) {
    calcWordFrequencies( root, o );
} // end of printWordFrequencies(ostream&)




void avlTree::findMostFreq( avlTreeNode* t, string& output, string& output2 ) const {
    if( t == nullptr ) {return;}

    findMostFreq( t->left, output, output2 );
    assignMostFreq( t, output, output2 );
    findMostFreq( t->right, output, output2 );
}
void avlTree::assignMostFreq( avlTreeNode* t, string& output, string& output2 ) const {
    if( atoi(output2.c_str()) < t->count ) {
        output = t->word + ": ";
        output2 = to_string(t->count);
    }
    else if( atoi(output2.c_str()) == t->count ) {
        output = (output.compare("") != 0) ? output.substr(0, (output.size() - 2)) : output;
        output += (output.compare("") == 0) ? t->word + ": " : ", " + t->word + ": ";
    }
}
void avlTree::printMostFrequent( ostream& o )  {
    string o1 = "";
    string o2 = "1";
    findMostFreq( root , o1, o2);
    o << "Most Frequent: " << o1 << " " << o2 << " time(s)" << endl << endl;
} // end of printMostFrequent(ostream&)




void avlTree::findLeastFreq( avlTreeNode* t, string& output, string& output2 ) const {
    if( t == nullptr ) { return; }

    findLeastFreq( t->left, output, output2 );
    assignLeastFreq( t, output, output2 );
    findLeastFreq( t->right, output, output2 );
}
void avlTree::assignLeastFreq( avlTreeNode* t, string& output, string& output2 ) const {
    if( atoi(output2.c_str()) > t->count ) {
        output = t->word + ": ";
        output2 = to_string(t->count);
    }
    else if( atoi(output2.c_str()) == t->count ) {
        output = (output.compare("") != 0) ? output.substr(0, (output.size() - 2)) : output;
        output += (output.compare("") == 0) ? t->word + ": " : ", " + t->word + ": ";
    }
}
void avlTree::printLeastFrequent( ostream& o ) {
    string o1 = "";
    string o2 = "1";
    findLeastFreq( root , o1, o2);
    o << "Least Frequent: " << o1 << " " << o2 << " time(s)" << endl << endl;
} // end of printLeastFrequent(ostream&)




double avlTree::calcDeviation( avlTreeNode* t ) const {
    vector<int> frequencies;
    getAllFreq( root, frequencies );
    double mean = meanValue( frequencies );
    double variance = varianceValue( frequencies, mean );
    return variance;
}
void avlTree::getAllFreq( avlTreeNode* t, vector<int>& frequencies ) const {
    if (t) {
        getAllFreq( t->left, frequencies );
        frequencies.push_back( t->count );
        getAllFreq( t->right, frequencies );
    }
}
double avlTree::meanValue( const vector<int>& frequencies ) const{
    int sum = 0;
    for ( int f : frequencies ) {
        sum += f;
    }
    return static_cast<double>( sum / frequencies.size() );
}
double avlTree::varianceValue( const vector<int>& frequencies, double meanVal ) const {
    double sum = 0.0;
    for ( int f : frequencies ) {
        double d = abs( f - meanVal );
        sum += (d * d);
    }
    double v = sum / static_cast<double>(frequencies.size());
    return sqrt( v );
}
void avlTree::printStandardDeviation( ostream& o ) {
    o << "Standard Deviation: " << calcDeviation( root ) << endl << endl;
} // end of printStandardDeviance(ostream&)



void avlTree::deleteTree( avlTreeNode*& t ) {

    // deletes all nodes via preorder traversal
    if ( t != nullptr) {
        deleteTree(t-> left);
        deleteTree(t-> right);

        delete t;
        t = nullptr;
    }
} // end of deleteTree(node*)
