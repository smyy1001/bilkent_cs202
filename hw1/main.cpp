/**
 * Title: Sorting and Algorithm Efficiency
 * Author: Sümeyye ACAR
 * Id: 22103640
 * Section: 001
 * Assignment: 1
 * Description: Testing the Sorting methods
*/

#include "sorting.h"
#include "cstdlib"
int main() {
    
    long arr[] = {10, 5, 9, 16, 17, 7, 4, 12, 19, 1, 15, 18, 3, 11, 13, 6};
    long arr2[] = {10, 5, 9, 16, 17, 7, 4, 12, 19, 1, 15, 18, 3, 11, 13, 6};
    long arr3[] = {10, 5, 9, 16, 17, 7, 4, 12, 19, 1, 15, 18, 3, 11, 13, 6};
    const long size = 16;
    std::cout << std::endl << std::endl << "Question 2 (c): " << std::endl << "--- --- --- --- Unsorted Array --- --- --- ---" << std::endl;
    displayArray(arr, size);

    // Bubble Sort
    long compCount, moveCount = 0;
    bubbleSort(arr, size, compCount, moveCount);
    std::cout << std::endl << "--- --- --- --- Bubble Sort --- --- --- ---" << std::endl;
    std::cout << "Number of Comparisons: " << compCount << "\t\t" << "Number of Moves: " << moveCount << std::endl;
    displayArray(arr, size);
    std::cout << std::endl;

    // Quick Sort
    std::cout << std::endl << "--- --- --- --- Quick Sort --- --- --- ---" << std::endl;
    compCount = 0, moveCount = 0;
    quickSort(arr2, size, compCount, moveCount);
    std::cout << "Number of Comparisons: " << compCount << "\t\t" << "Number of Moves: " << moveCount << std::endl;
    displayArray(arr2, size);
    std::cout << std::endl;

    // Merge Sort
    std::cout << std::endl << "--- --- --- --- Merge Sort --- --- --- ---" << std::endl;
    compCount = 0, moveCount = 0;
    mergeSort(arr3, size, compCount, moveCount);
    std::cout << "Number of Comparisons: " << compCount << "\t\t" << "Number of Moves: " << moveCount << std::endl;
    displayArray(arr3, size);
    std::cout << std::endl;
    

    std::cout << std::endl << std::endl << std::endl << "Question 2(d)";
    std::cout << std::endl << "Performance Analysis (Random Generated Array)" << std::endl;
    performanceAnalysis(0); // random

    // std::cout << std::endl << std::endl << std::endl << "--- --- --- --- Performance Analysis (Ascending Array) --- --- --- ---" << std::endl;
    // performanceAnalysis(1); // ascending

    // std::cout << std::endl << std::endl << std::endl << "--- --- --- --- Performance Analysis (Descending Array) --- --- --- ---" << std::endl;
    // performanceAnalysis(2); // descending

    return 0;
}