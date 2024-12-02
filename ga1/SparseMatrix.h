#pragma once
#include "Internal.h"
#include "Node.h"
#include <fstream>
#include <iostream>

using namespace std;

/* Create a SparseMatrix class that uses the nodes to hold the non-zero values
 * in nodes stored in a 2D linked matrix. The nodes should be dynamically
 * allocated and doubly-linked in row and column directions. */
class SparseMatrix {
private:
  int rows, cols;
  Node *head;

public:
  /* The constructor should create the header row and column as the entry point
   * in the the rows and columns. It should read in the size of the array and
   * the values to store in the array. It should then construct and link the
   * headers for the rows and columns for entries into the array. */
  SparseMatrix(int r, int c);
  ~SparseMatrix();

  // Include helper methods to allow you to access nodes in the matrix, set
  // values, and create nodes as needed.
  int getRows() const { return rows; }
  int getCols() const { return cols; }
  void setValue(int r, int c, int v);
  int getValue(int r, int c) const;

  /* Create methods to traverse by row and by column as they will support the
   * other operations. If a node is not present in the matrix as a particular
   * location, the value is assumed to be zero (0). */

  // Create helper functions to print the matrices and to save the matrices to a
  // file.
  void printMatrix() const;
  void saveMatrix(ostream& out) const;

  // Overload the operator+ to add two matrices together and return a new matrix
  SparseMatrix operator+(const SparseMatrix &rhs) const;

  // Overload the operator* to multiply two matrices and return a new matrix.
  SparseMatrix operator*(const SparseMatrix &rhs) const;

  // Create a transpose method to create a new sparse matrix that is the
  // transpose of the original matrix.
  SparseMatrix transpose() const;
};

// Constructor
SparseMatrix::SparseMatrix(int r, int c) : rows(r), cols(c), head(nullptr) {
  head = new Node(-1);
  Node *currentRowHeader = head;
  Node *currentColHeader = head;

  // Set all the row headers
  for (int i = 0; i < rows; i++) {
    currentRowHeader->setDown(new Node(i));
    currentRowHeader = currentRowHeader->getDown();
  }

  // Set all the column headers
  for (int i = 0; i < cols; i++) {
    currentColHeader->setRight(new Node(i));
    currentColHeader = currentColHeader->getRight();
  }
}

// Destructor
SparseMatrix::~SparseMatrix() {
  // Delete all the internal nodes
  Node *currentRowHeader = head->getDown();
  while (currentRowHeader != nullptr) {
    Node *currentNode = currentRowHeader->getRight();
    while (currentNode != nullptr) {
      Node *nextNode = currentNode->getRight();
      delete currentNode;
      currentNode = nextNode;
    }
    currentRowHeader = currentRowHeader->getDown();
  }

  // Delete all the column headers
  Node *currentColHeader = head->getRight();
  while (currentColHeader != nullptr) {
    Node *nextColHeader = currentColHeader->getRight();
    delete currentColHeader;
    currentColHeader = nextColHeader;
  }

  // Delete all the row headers
  Node *currentHeader = head->getDown();
  while (currentHeader != nullptr) {
    Node *nextHeader = currentHeader->getDown();
    delete currentHeader;
    currentHeader = nextHeader;
  }

  // Delete the head node
  delete head;
}

// Helper Methods
void SparseMatrix::setValue(int r, int c, int v) {
  // Find the row and column headers
  Node *rowHeader = head;
  while (rowHeader->getDown() != nullptr &&
         rowHeader->getDown()->getValue() <= r) {
    rowHeader = rowHeader->getDown();
  }
  Node *colHeader = head;
  while (colHeader->getRight() != nullptr &&
         colHeader->getRight()->getValue() <= c) {
    colHeader = colHeader->getRight();
  }

  // Find the correct internal node
  Node *currentRowNode = rowHeader;
  while (currentRowNode->getRight() != nullptr &&
         static_cast<Internal *>(currentRowNode->getRight())->getCol() < c) {
    currentRowNode = currentRowNode->getRight();
  }
  Node *currentColNode = colHeader;
  while (currentColNode->getDown() != nullptr &&
         static_cast<Internal *>(currentColNode->getDown())->getRow() < r) {
    currentColNode = currentColNode->getDown();
  }

  // Check if the node exists
  if (currentRowNode->getRight() == currentColNode->getDown() &&
      currentRowNode->getRight() != nullptr) {
    // Update the existing node
    static_cast<Internal *>(currentRowNode->getRight())->setValue(v);
  } else {
    // Create a new internal node and insert it into the matrix
    Internal *newNode = new Internal(r, c, v);
    newNode->setRight(currentRowNode->getRight());
    newNode->setDown(currentColNode->getDown());
    newNode->setLeft(currentRowNode);
    newNode->setUp(currentColNode);
    currentRowNode->setRight(newNode);
    currentColNode->setDown(newNode);
  }
}

int SparseMatrix::getValue(int r, int c) const {
  // Find the row and column headers
  Node *rowHeader = head;
  while (rowHeader->getDown() != nullptr &&
         rowHeader->getDown()->getValue() <= r) {
    rowHeader = rowHeader->getDown();
  }
  Node *colHeader = head;
  while (colHeader->getRight() != nullptr &&
         colHeader->getRight()->getValue() <= c) {
    colHeader = colHeader->getRight();
  }

  // Find the correct internal node
  Node *currentRowNode = rowHeader;
  while (currentRowNode->getRight() != nullptr &&
         static_cast<Internal *>(currentRowNode->getRight())->getCol() < c) {
    currentRowNode = currentRowNode->getRight();
  }
  Node *currentColNode = colHeader;
  while (currentColNode->getDown() != nullptr &&
         static_cast<Internal *>(currentColNode->getDown())->getRow() < r) {
    currentColNode = currentColNode->getDown();
  }

  // Check if the node exists
  if (currentRowNode->getRight() == currentColNode->getDown() &&
      currentRowNode->getRight() != nullptr) {
    // Return the value of the existing node
    return static_cast<Internal *>(currentRowNode->getRight())->getValue();
  } else {
    // Node doesn't exist, return 0
    return 0;
  }
}

// Print and save
void SparseMatrix::printMatrix() const {
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      cout << getValue(r, c);
      if (c < cols - 1) {
        cout << ", ";
      }
    }
    cout << endl;
  }
}

void SparseMatrix::saveMatrix(ostream& out) const {
    for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      out << getValue(r, c);
      if (c < cols - 1) {
        out << ", ";
      }
    }
    out << endl;
  }
}

// Operations
SparseMatrix SparseMatrix::operator+(const SparseMatrix &rhs) const {
	SparseMatrix result(rows, cols);
	int temp;
	for(int r = 0; r < rows; r++) {
        for(int c = 0; c < cols; c++) {
            temp = getValue(r, c)+ rhs.getValue(r, c);
            result.setValue(r, c, temp);
        }
    }
  return result; 
}

SparseMatrix SparseMatrix::operator*(const SparseMatrix &rhs) const {
	SparseMatrix result(rows, rhs.getCols());
  int temp;
		for(int r = 0; r < rows; r++)
		{
			for(int c = 0; c < rhs.getCols(); c++)
				{
					int sum = 0;
					for(int k = 0; k < cols; k++)
						{
							sum += getValue(r, k) * rhs.getValue(k, c);
						}
					result.setValue(r, c, sum);
				}
			
		}
  return result; 
}

SparseMatrix SparseMatrix::transpose() const {
  SparseMatrix result(rows, cols);
  int temp;
  for(int r = 0; r < rows; r++) {
      for(int c = 0; c < cols; c++) {
          temp = getValue(r, c);
          result.setValue(c, r, temp);
        }
    }
  return result; 
}
