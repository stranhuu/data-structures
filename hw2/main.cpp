#include <iostream>
#include <fstream>
#include "ArgumentManager.h"

using namespace std;

// A helper function to partition the array for quickSelect algorithm
int partition(int arr[], int left, int right, int &count) {
  int pivot = arr[right];
  int i = left - 1;

  // Iterate through the array and swap elements if they are less than or equal to pivot
  for (int j = left; j < right; j++) {
    if (arr[j] <= pivot) {
      i++;
      swap(arr[i], arr[j]);
    }
  }

  // Swap the pivot with the element at the (i + 1)th position and increment count
  swap(arr[i+1], arr[right]);
  count++;

  // Return the index of the pivot
  return i + 1;
}

// A recursive function to find the kth smallest element using quickSelect algorithm
int quickSelect(int arr[], int left, int right, int k, int &count) {
  // If there is only one element, return that element
  if (left == right) {
    return arr[left];
  }
  // Partition the array and get the index of the pivot
  int pivotIndex = partition(arr, left, right, count);
  // If k is equal to the index of the pivot, return the pivot
  if (k == pivotIndex) {
    return arr[k];
  } else if (k < pivotIndex) {
    // If k is less than the index of the pivot, recurse on the left side of the pivot
    return quickSelect(arr, left, pivotIndex - 1, k, count);
  } else {
    // If k is greater than the index of the pivot, recurse on the right side of the pivot
    return quickSelect(arr, pivotIndex + 1, right, k, count);
  }
}

int main(int argc, char* argv[]) {
  ArgumentManager am(argc, argv);

  // Open input and output files
  ifstream fin(am.get("input"));
  ofstream fout(am.get("output"));

  // Read in the seed and count from the input file
  int seed, count;
  fin >> seed >> count;

  // Set the random seed using the seed value
  srand(seed);

  // Create a dynamic array of integers of size count and fill it with random numbers
  int* arr = new int[count];
  for (int i = 0; i < count; i++) {
    arr[i] = rand();
  }

  // Declare and initialize countPartitionSteps variable to keep track of the number of partition steps
  int countPartitionSteps = 0;
  int median;

  // If count is even, find the element at (count / 2 - 1)th position using quickSelect
  if (count % 2 == 0) {
    median = quickSelect(arr, 0, count - 1, count / 2 - 1, countPartitionSteps);
  } else {
    // If count is odd, find the element at (count / 2)th position using quickSelect
    median = quickSelect(arr, 0, count - 1, count / 2, countPartitionSteps);
  }

  // Write the median and countPartitionSteps to the output file
  fout << median << endl;
  fout << countPartitionSteps << endl;

  // Free the dynamically allocated memory
  delete[] arr;
  return 0;
}
