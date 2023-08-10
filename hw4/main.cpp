/**
 * Title: main.cpp
 * Author: Sumeyye Acar
 * Id: 22103640
 * Section: 1
 * Assignment: 4
 * Description: Tests methods and produces output files
*/

#include "avlTree.h"
using namespace std;


int main(int argc, char* argv[]) {

    // input file to read from
    string inputFile = argv[1];

    // build the Tree
    avlTree Tree; 
    Tree.generateTree( inputFile ); 

    // output files
    string output1 = "wordfreqs.txt";
    string output2 = "statistics.txt";

    // open files to write the outputs
    ofstream outputFile1( output1 );
    ofstream outputFile2( output2 );

    // Check if the files were opened successfully
    if ( !outputFile1.is_open() ) {
        cout << "Error opening the file: " << output1 << endl;
    }
    if ( !outputFile2.is_open() ) {
        cout << "Error opening the file: " << output2 << endl;
    }

    // write into "wordfreqs.txt"
    Tree.printWordFrequencies( outputFile1 );

    // write into "statistics.txt"
    Tree.printTotalWordCount( outputFile2 );
    Tree.printHeight( outputFile2 );
    Tree.printMostFrequent( outputFile2 );
    Tree.printLeastFrequent( outputFile2 );
    Tree.printStandardDeviation( outputFile2 );


    // Close after writing
    outputFile1.close();
    outputFile2.close();

    return 0;
}
