/**
 * Title: heapSort.cpp
 * Author: Sumeyye Acar
 * Id: 22103640
 * Section: 1
 * Assignment: 3
 * Description: The heap sort algorithm and main()
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "heap.h"


void heapsort( heap unsortedHeap, int size, string outp) {
    int comp = 0;

    // open the file 
    ofstream outputFile(outp);
    if (!outputFile.is_open()) {
        // if the file opening fails
        cout << "Error occurred while opening the file!" << endl;
    }

    // print the maximum value of the heap each time into the opened
    // as result: receive a descanting ordered output
    for(int i = 0; i < size; i++) {
        outputFile << unsortedHeap.maximum() << endl;
        comp += unsortedHeap.popMaximum(); // total number of comparison
    }

    outputFile << endl << "The total number of comparison: " << comp << endl;
    outputFile.close(); // close ofstream

} // end of heapsort()



// main method
int main(int argc, char *argv[]) {

    // read data from input file into an empty heap
    heap h; // create a empty heap
    string input_File = argv[1];
    ifstream inputFile(input_File);
    if (!inputFile.is_open()) {
        // if the file opening fails
        cout << "Error occurred while opening the file!!" << endl;
    }

    // read each line as integer
    int value;
    while (inputFile >> value) {
        h.insert(value); // insert into the heap
    }
    inputFile.close(); // close ifstream
    // end reading data into heap


    // sort the heap and write into output file
    string output_File = argv[2];
    heapsort(h, h.size, output_File);
    // end writing into output file


    return 0;
} // end of main()