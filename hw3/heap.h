/**
 * Title: heap.h
 * Author: Sumeyye Acar
 * Id: 22103640
 * Section: 1
 * Assignment: 3
 * Description: The heap class's header file
*/

int const MAX_SIZE = 5000;

class heap {
public:
    heap();
    ~heap();
    int size;
    void insert( const int );
    int maximum();
    int popMaximum();
    void heapRebuild( const int, int& );
    int* my_heap; // array containing the values

protected:
    // helper function
    int popMaximum(int& c); // c is the number of comparision made in reBuild() function
};
