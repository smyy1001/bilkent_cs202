/**
 * Title: Sorting and Algorithm Efficiency
 * Author: Sümeyye ACAR
 * Id: 22103640
 * Section: 001
 * Assignment: 1
 * Description: The header file with the function prototypes
*/
#ifndef sorting_h
#define sorting_h
#include <iostream>
#include <chrono>
#include <time.h>
#include <stdlib.h>

void mergeSort(long* arr, const long size, long& compCount, long& moveCount);
void merge(long* arr , long first, long mid, long last, long& compCount, long& moveCount);
void mergesort(long* arr, long first, long last, long& compCount, long& moveCount);

void quickSort(long* arr, const long size, long& compCount, long& moveCount);
void partition(long* arr, long first, long last, long &pivotIndex, long& compCount, long& moveCount);
void quicksort(long* arr, long first, long last, long& compCount, long& moveCount);

void bubbleSort(long* arr, const long size, long& compCount, long& moveCount);

void displayArray(long* arr, const long size);

void createRandomArray(long*& arr1, long*& arr2, long*& arr3, const long size);
void createAscendingArray(long*& arr1, long*& arr2, long*& arr3, const long size);
void createDescendingArray(long*& arr1, long*& arr2, long*& arr3, const long size);

void performanceAnalysis(const long size);

#endif