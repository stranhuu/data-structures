#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
using namespace std;

const int numRows = 13; // 13 Ranks
const int numCols = 4; // 4 Suits

int getRow(char rank) {
  switch (rank) {
    case '0':
        return 9; // 10
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return int(rank) - 49; // 1-9
    case 'J':
        return 10; // Jack
    case 'Q':
        return 11; // Queen
    case 'K':
        return 12; // King
  }
  return -1;
}

int getCol(char suit) {
  switch (suit) {
    case 'S':
        return 0; // Spades
    case 'H':
        return 1; // Hearts
    case 'C':
        return 2; // Clubs
    case 'D':
        return 3; // Diamonds
  }
  return -1;
}

int main(int argc, char* argv[]) {
  // Initialize 2D array to 0
  int deck[numRows][numCols] = {};
  ArgumentManager am(argc, argv);
  string input;
  
  //Open input and output files
  ifstream fin(am.get("input"));
  ofstream fout(am.get("output"));

  getline(fin, input);

  int pos = input.find(", ");

  // Mark card as received in 2D array
  while (pos != string::npos) {
    deck[getRow(input[pos - 2])][getCol(input[pos - 1])] = 1;
    input = input.substr(pos + 2);
    pos = input.find(", ");
  }

  // Check the final card not followed by ", "
  deck[getRow(input[0])][getCol(input[1])] = 1;

  // Print 2D array of cards
  for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numCols; j++) {
          fout << deck[i][j] << " ";
      }
      fout << endl;
  }

  // Close input and output files
  fin.close();
  fout.close();
  return 0;
}