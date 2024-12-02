#include "ArgumentManager.h"
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned char square;

const int dx[] = {-2, -2, -1, 1, 2, 2, 1, -1};
const int dy[] = {-1, 1, 2, 2, 1, -1, -2, -2};

bool solve_helper(int x, int y, int w, int h, vector<vector<square>> &board,
                  int moves) {
  // Base case: all squares have been visited
  if (moves == w * h) {
    // Check if the last move leads back to the starting position
    for (int i = 0; i < 8; i++) {
      int nx = x + dx[i];
      int ny = y + dy[i];
      if (nx == 0 && ny == 0) {
        return true; // Found a closed tour
      }
    }
    return false; // Last move doesn't lead back to the starting position
  }

  // Try all possible moves from the current position
  for (int i = 0; i < 8; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (nx >= 0 && nx < w && ny >= 0 && ny < h && board[ny][nx] == 0) {
      // Move to the next square
      board[ny][nx] = moves + 1;
      if (solve_helper(nx, ny, w, h, board, moves + 1)) {
        return true; // Found a solution
      }
      // Backtrack
      board[ny][nx] = 0;
    }
  }

  return false; // No solution found
}

bool solve(int w, int h, ofstream &fout) {
  vector<vector<square>> board(h, vector<square>(w));
  int x = 0;
  int y = 0;
  board[y][x] = 1; // Start at the top-left corner

  if (solve_helper(x, y, w, h, board, 1)) {
    // Found a solution
    fout << "A closed tour exists!" << endl;
    return true;
  } else {
    // No solution found
    fout << "A closed tour does not exist!" << endl;
    return false;
  }
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);

  // Open input and output files
  ifstream fin(am.get("input"));
  ofstream fout(am.get("output"));

  // Read in the dimensions from the input file
  int m, n;
  fin >> m >> n;
  fin.close();

  // Solve the closed knight's tour problem
  solve(m, n, fout);

  fout.close();
  return 0;
}
