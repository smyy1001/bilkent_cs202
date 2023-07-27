/**
 * Title: Trees
 * Author Sumeyye Acar
 * Id: 22103640
 * Section: 01
 * Assignment: 2
 * Description: Main method ( testing purposes ) 
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#include "NgramTree.h"


int main( int argo, char** argv ) {

    NgramTree tree;
    string fileName( argv[1] );
    int n = atoi( argv[2] );
    tree.generateTree( fileName, n );

    cout << "\nTotal " << n << "-gram count: " << tree.getTotalNgramCount() << endl;
    cout << tree << endl;
    cout << n << "-gram tree is complete: " << ( tree.isComplete() ? "Yes" : "No" ) << endl;
    cout << n << "-gram tree is full: " << ( tree.isFull() ? "Yes" : "No" ) << endl;

    // Before insertion of new n-grams
    cout << "\nTotal " << n << "-gram count: " << tree.getTotalNgramCount() << endl;

    tree.addNgram( "samp" );
    tree.addNgram( "samp" );
    tree.addNgram( "zino" );
    tree.addNgram( "aatt" );

    cout << "\nTotal " << n << "-gram count: " << tree.getTotalNgramCount() << endl;
    cout << tree << endl;
    cout << n << "-gram tree is complete: " << ( tree.isComplete() ? "Yes" : "No" ) << endl;
    cout << n << "-gram tree is full: " << ( tree.isFull() ? "Yes" : "No" ) << endl;
    
    return 0;
}
