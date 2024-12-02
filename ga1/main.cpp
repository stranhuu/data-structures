#include "ArgumentManager.h"
#include "Internal.h"
#include "Node.h"
#include "SparseMatrix.h"
#include <fstream>
#include <iostream>

using namespace std;

SparseMatrix createMtx(ifstream &fin) {
  int rows, cols;
  fin >> rows >> cols;
  SparseMatrix mtx(rows, cols);
  string input;
  fin.ignore();
  while (getline(fin, input) && !input.empty()) {
    mtx.setValue(input[0] - '0', input[2] - '0', input[4] - '0');
  }
  return mtx;
}

int main(int argc, char *argv[]) {
  // Open the input file
  ArgumentManager am(argc, argv);
  string inputfile = am.get("input");
  string outputfile = am.get("output");

  ifstream fin(inputfile);
  ofstream fout(outputfile);

  // Read the operation symbol
  char operationSymbol;
  fin >> operationSymbol;

  if (operationSymbol == '*') {
    SparseMatrix lhs = createMtx(fin);
    SparseMatrix rhs = createMtx(fin);
    if (lhs.getCols() == rhs.getRows()) {
      SparseMatrix mtx = lhs * rhs;
      mtx.saveMatrix(fout);
    } else {
      fout << "Invalid Matrix Operation" << endl;
    }
  } else if (operationSymbol == '+') {
    SparseMatrix lhs = createMtx(fin);
    SparseMatrix rhs = createMtx(fin);
    if (lhs.getRows() == rhs.getRows() && lhs.getCols() == rhs.getCols()) {
      SparseMatrix added_mtx = lhs + rhs;
      added_mtx.saveMatrix(fout);
    } else {
      fout << "Invalid Matrix Operation" << endl;
    }
  } else if (operationSymbol == 'T') {
    SparseMatrix lhs = createMtx(fin);
    SparseMatrix lhs_transpose = lhs.transpose();
    lhs_transpose.saveMatrix(fout);
  }
  // Close the input file
  fin.close();
	fout.close();

  return 0;
}
