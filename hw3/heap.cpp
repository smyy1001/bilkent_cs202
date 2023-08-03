/**
 * Title: heap.cpp
 * Author: Sumeyye Acar
 * Id: 22103640
 * Section: 1
 * Assignment: 3
 * Description: the heap class's implementation
*/

#include <iostream>
#include "heap.h"
using namespace std;

// constructor
heap::heap() {
    my_heap = new int[MAX_SIZE];
    size = 0;
}

// destructor
heap::~heap() {
    delete[] my_heap;
    size = -1;
}

// insertion method
void heap::insert( const int value ) {

    // in case the heap is full, increase the
    if (size == MAX_SIZE) {
        int* temp = new int[MAX_SIZE+1000];
        for(int i = 0; i < size; i++) {
            temp[i] = my_heap[i];
        }
        my_heap = temp;
    }

    // first insert "value" at the end of my_heap
    my_heap[size] = value;

    // index of current place and its parent
    int current = size;
    int parent = (current - 1)/2;

    // move "value" to its proper position
    while ( (current > 0) && (my_heap[current] > my_heap[parent]) ) {
        int temp = my_heap[parent];
        my_heap[parent] = my_heap[current];
        my_heap[current] = temp;
        current = parent;
        parent = (current - 1)/2;
    }

    // increase the size by 1
    size++;

} // end of insert( const int )

// get the maximum element
int heap::maximum() {
    return (size == 0) ? -1: my_heap[0];
} // end of maximum()

// delete the root of the heap
int heap::popMaximum() {
    int c = 0;
    return popMaximum(c);
}

// helper function
int heap::popMaximum(int& c) {
    if (size==0)
        return -1;
    else {
        my_heap[0] = my_heap[--size];
        heapRebuild(0,c);
    }
    return c;
} // end of popMaximum()


// rebuild the heap after the deletion operation
void heap::heapRebuild( const int root, int& comp ) {   

    // index of left child, if there is one
    int child = 2 * root + 1; 

    if ( child < size ) {  // root has a left child, so it isn't a leaf
    
        int rightChild = child + 1; // index of a right child, if there is on      

        // If right child exists, find larger child
        if ( (rightChild < size) && (my_heap[rightChild] > my_heap[child]) ) {
            child = rightChild; // child is the index of larger child
            comp++; // comparision between right child's value and left child's value
        }

        // If item at index root is smaller than item at index child, swap items
        if ( my_heap[root]< my_heap[child]) {
            int temp = my_heap[root];
            my_heap[root] = my_heap[child];
            my_heap[child] = temp;
            comp++; // comparision between the parent value and the larger child

            // make sure the new subtree is a heap
            heapRebuild(child, comp);
        }
    }
}// end of heapRebuild()