/**
 * Title: Sorting and Algorithm Efficiency
 * Author: Sümeyye ACAR
 * Id: 22103640
 * Section: 001
 * Assignment: 1
 * Description: Bodies of the functions in the header file
 **/

#include "sorting.h"
using namespace std;


void merge(long* arr, long start, long mid, long end, long& compCount, long& moveCount){

    // first half
    long first1 = start;
    // second half
    long first2 = mid+1;

    long *temp = new long[end-start+1];
    long pos = 0;

    while (first1 <= mid && first2 <= end) {
        if (arr[first2] < arr[first1]) {
            temp[pos++] = arr[first2];
            first2 += 1;
            compCount++;
            moveCount++;
        } else {
            temp[pos++] = arr[first1];
            first1 += 1;
            moveCount++;
        }
        compCount+=2;
    }

    while (first1 <= mid) {
        temp[pos++] = arr[first1];
        first1 += 1;
        compCount++;
        moveCount++;
    }

    while (first2 <= end) {
        temp[pos++] = arr[first2];
        first2 += 1;
        compCount++;
        moveCount++;
    }

    for (long i = 0; i < (pos); i++) {
        arr[i + start] = temp[i];
        compCount++;
        moveCount+=2;
    }

    // deallocate temp
    delete[] temp;
    moveCount++;
} 

void mergesort( long* arr, long first, long last, long& compCount, long& moveCount) {
    compCount++;
    if (first != last) {
        long mid = (first + last)/2;

        mergesort(arr, first, mid, compCount, moveCount);

        mergesort(arr, mid+1, last, compCount, moveCount);

        // merge the two halves
        merge(arr, first, mid, last, compCount, moveCount);
    }
}  

void mergeSort(long* arr, const long size, long& compCount, long& moveCount) {
    mergesort(arr, 0, size-1, compCount, moveCount);
}


void partition(long* arr, long first, long last, long& pivotIndex, long& compCount, long& moveCount) {

    long p_pivot = arr[first];

    long lastS1 = first; 
    long firstUnknown = first + 1; 
    
    for (  ; firstUnknown <= last; ++firstUnknown) {
        if (arr[firstUnknown] < p_pivot) {  	
            ++lastS1;
            swap(arr[firstUnknown], arr[lastS1]);
            moveCount += 3;
        }
        compCount += 2;
    }
    swap(arr[first], arr[lastS1]);
    pivotIndex = lastS1;
    moveCount += 3;
}

void quicksort(long* arr, long first, long last, long& compCount, long& moveCount) {

	long pivotIndex = 0;
    compCount++;
    if (first < last) {

        partition(arr, first, last, pivotIndex, compCount, moveCount);
        
        quicksort(arr, first, pivotIndex-1, compCount, moveCount);
        quicksort(arr, pivotIndex+1, last, compCount, moveCount);
    }
}

void quickSort(long *arr, const long size, long& compCount, long& moveCount) {
    quicksort(arr, 0, size-1, compCount, moveCount);
}


void bubbleSort(long* arr, const long size, long &compCount, long &moveCount) {
    bool sorted = false;
    for (long pass = 1; (pass < size) && !sorted; ++pass) {
        sorted = true;
        for (long index = 0; index < size - pass; ++index) {
            long nextIndex = index + 1;
            if (arr[index] > arr[nextIndex]) {
                swap(arr[index], arr[nextIndex]);
                sorted = false;
                moveCount += 3;
            }
            compCount += 2;
        }
        compCount += 2;
    }
}


void displayArray( long* arr, const long size ) {
    for(long i = 0; i < size-1; i++) {
        cout << arr[i] << ", ";
    } cout << arr[size-1] << endl;
}


void createRandomArray( long*& arr, long*& arr_2, long*& arr_3, const long size ) {
    arr = new long[size];
    for(long i = 0; i < size; i++) {
        long r = rand();
        arr[i] = r;
    }
    arr_2 = arr;
    arr_3 = arr;
}


void createAscendingArray( long*& arr1, long*& arr2, long*& arr3, const long size ) {
    arr1 = new long[size];
    if(size != 0) {
        long r = rand();
        arr1[0] = r;
    }
    for(long i = 1; i < size; i++) {
        long r = rand();
        while(r < arr1[i-1]) {
            r = rand();
        }
        arr1[i] = r;
    }
    arr2 = arr1;
    arr3 = arr1;
}


void createDescendingArray( long*& arr1, long*& arr2, long*& arr3, const long size ) {
    arr1 = new long[size];
    if(size != 0) {
        long r = rand();
        arr1[0] = r;
    }
    for(long i = 1; i < size; i++) {
        long r = rand();
        while(r > arr1[i-1]) {
            r = rand();
        }
        arr1[i] = r;
    }
    arr2 = arr1;
    arr3 = arr1;
}


void performanceAnalysis(long type) {
    chrono::time_point< chrono::system_clock > startTime;
    chrono::duration< double, milli > elapsedTime;

    for(long i = 4000; i < 40001; i+=4000) {
        cout << "-----------------------------------------------" <<endl<<endl;
        cout << "Array Size: " << i << endl;
        cout << "Elapsed Time\tcompCount\tmoveCount" << endl;
        const long size = i;
        long* arr1;
        long* arr2;
        long* arr3;
        if(type == 0) { createRandomArray(arr1,arr2,arr3,size); }
        else if(type == 1) { createAscendingArray(arr1,arr2,arr3,size); }
        else { createDescendingArray(arr1,arr2,arr3,size); }

        long result[3][3];

        for(long j = 0; j < 3; j++) {
            long c1 = 0;
            long c2 = 0;
            if(j == 0) {
                startTime = std::chrono::system_clock::now();
                bubbleSort(arr1,size,c1,c2);
                elapsedTime = std::chrono::system_clock::now() - startTime;
                result[j][0] = elapsedTime.count();
                result[j][1] = c1;
                result[j][2] = c2;
            }
            else if(j == 1) {
                startTime = std::chrono::system_clock::now();
                mergeSort(arr2,size,c1,c2);
                elapsedTime = std::chrono::system_clock::now() - startTime;
                result[j][0] = elapsedTime.count();
                result[j][1] = c1;
                result[j][2] = c2;
            }
            else {
                startTime = std::chrono::system_clock::now();
                quickSort(arr3,size,c1,c2);
                elapsedTime = std::chrono::system_clock::now() - startTime;
                result[j][0] = elapsedTime.count();
                result[j][1] = c1;
                result[j][2] = c2;
            }
        }

        string alg[3] = {"Bubble Sort", "Merge Sort", "Quick Sort"};
        for(long a = 0; a < 3; a++) {
            cout << alg[a] << ": " << endl;
            cout << result[a][0] << "\t" << result[a][1] << "\t" << result[a][2] << endl << endl;
        }
    }                     
} // end
