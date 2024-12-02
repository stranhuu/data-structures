#pragma once

/* Create a class to hold the row and column headers that holds an integer value
 * (either the row or column) and has a down pointer to a node and a right
 * pointer to a node. */
class Node {
protected:
  int value;
  Node *down, *right;

public:
  // Constructor
  Node(int v) : value(v), down(nullptr), right(nullptr) {}

  // Getters and Setters
  int getValue() const { return value; }
  Node *getDown() const { return down; }
  Node *getRight() const { return right; }
  void setValue(int v) { value = v; }
  void setDown(Node *d) { down = d; }
  void setRight(Node *r) { right = r; }
};
