#pragma once
#include "Node.h"

/* Create a class to represent the inside nodes for the sparse matrix. You will
 * need a constructor that contains parameters for the data value and the row
 * and column numbers. It should also contain pointers up, down, left, and right
 * to maintain the doubly-linked structure in both directions. */

class Internal : public Node {
private:
  int row, col;
  Node *up, *left;

public:
  // Constructor
  Internal(int r, int c, int v)
      : Node(v), row(r), col(c), up(nullptr), left(nullptr) {}

  // Getters and Setters
  int getRow() const { return row; }
  int getCol() const { return col; }
  Node *getUp() const { return up; }
  Node *getLeft() const { return left; }
  void setRow(int r) { row = r; }
  void setCol(int c) { col = c; }
  void setUp(Node *u) { up = u; }
  void setLeft(Node *l) { left = l; }
};
