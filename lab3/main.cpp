#include "ArgumentManager.h"
#include <fstream>
#include <iostream>

using namespace std;

class Heap {
public:
  Heap(int capacity, bool isMaxHeap) {
    this->capacity = capacity;
    this->size = 0;
    this->isMaxHeap = isMaxHeap;
    this->elements = new int[capacity];
  }

  ~Heap() { delete[] elements; }

  void insert(int value) {
    if (size == capacity) {
      cout << "Heap is full!" << endl;
      return;
    }
    elements[size] = value;
    int i = size;
    while (i > 0 && compare(elements[i], elements[parent(i)])) {
      swap(i, parent(i));
      i = parent(i);
    }
    size++;
  }

  int extract() {
    if (size == 0) {
      cout << "Heap is empty!" << endl;
      return -1;
    }
    int result = elements[0];
    elements[0] = elements[size - 1];
    size--;
    heapify(0);
    return result;
  }

  void extractK(int k, ofstream &fout) {
    for (int i = 0; i < k; i++) {
      int value = extract();
      if (value == -1) {
        cout << "Error extracting from heap!" << endl;
        return;
      }
      fout << value << endl;
    }
    fout.close();
  }

private:
  int *elements;
  int capacity;
  int size;
  bool isMaxHeap;

  int parent(int i) { return (i - 1) / 2; }

  int leftChild(int i) { return 2 * i + 1; }

  int rightChild(int i) { return 2 * i + 2; }

  bool compare(int a, int b) {
    if (isMaxHeap) {
      return a > b;
    } else {
      return a < b;
    }
  }

  void swap(int i, int j) {
    int temp = elements[i];
    elements[i] = elements[j];
    elements[j] = temp;
  }

  void heapify(int i) {
    int left = leftChild(i);
    int right = rightChild(i);
    int largestOrSmallest = i;
    if (left < size && compare(elements[left], elements[largestOrSmallest])) {
      largestOrSmallest = left;
    }
    if (right < size && compare(elements[right], elements[largestOrSmallest])) {
      largestOrSmallest = right;
    }
    if (largestOrSmallest != i) {
      swap(i, largestOrSmallest);
      heapify(largestOrSmallest);
    }
  }
};

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);

  // Open input and output files
  ifstream fin(am.get("input"));
  ofstream fout(am.get("output"));

  // Read in the seed and count from the input file
  int seed, count, k;
  string type;
  fin >> seed >> count >> type >> k;
  fin.close();

  // Seed the random number generator
  srand(seed);

  // Generate random values and insert them into the heap
  Heap heap(count, type == "largest");
  for (int i = 0; i < count; i++) {
    int value = rand();
    heap.insert(value);
  }

  // Extract the k largest or smallest values and output them to a file
  heap.extractK(k, fout);

  return 0;
}
