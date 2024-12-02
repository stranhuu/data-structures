// Include necessary libraries
#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
using namespace std;

// Check function that uses recursion to check if a string can be constructed from characters in the matrix
bool wordSearch(int x, int y, int curr, int numRows, int numCols, char** matrix, string word, bool** visited) {
    // Base cases for if the current position is out of bounds or if the current character does not match the current letter in the word
    if (x < 0 || y < 0 || x >= numRows || y >= numCols) {
        return false;
    }
    if (visited[x][y] || matrix[x][y] != word[curr]) {
        return false;
    }

    // If the entire word has been found, return true
    if (curr == word.length() - 1) {
        return true;
    }

    // Mark the current position as visited
    visited[x][y] = true;

    // Recursive calls to check the adjacent positions (up, down, left, right)
    if (wordSearch(x + 1, y, curr + 1, numRows, numCols, matrix, word, visited) || wordSearch(x - 1, y, curr + 1, numRows, numCols, matrix, word, visited) || wordSearch(x, y + 1, curr + 1, numRows, numCols, matrix, word, visited) || wordSearch(x, y - 1, curr + 1, numRows, numCols, matrix, word, visited)) {
        return true;
    }

    // If the word is not found, mark the current position as unvisited and return false
    visited[x][y] = false;
    return false;
}

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);

    //Open input and output files
    ifstream fin(am.get("input"));
    ofstream fout(am.get("output"));

    // Read in the dimensions of the character matrix
    int numRows = 0, numCols = 0;
    fin >> numRows >> numCols;

    // Dynamically allocate a 2D - array for the character matrix and a 2D - array for visited positions
    char** matrix = new char*[numRows];
    bool** visited = new bool*[numRows];

    // Initialize each element in the arrays
    for (int row = 0; row < numRows; row++) {
        matrix[row] = new char[numCols];
        visited[row] = new bool[numCols];
    }
    
    // Read in the characters for the matrix from the input file and initialize the visited positions array to false
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            fin >> matrix[row][col];
            visited[row][col] = false;
        }
    }

    // Read in the word to search for from the input file and close the input file
    string word;
    fin >> word;
    fin.close();

    // Initialize a boolean variable to track if the word has been found
    bool found = false;

    // Loop through each element of the matrix and check if the word can be found starting at that position
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            // Call the check function and pass in the current position, the dimensions of the matrix, the matrix itself, the word, and the visited positions array
            if (wordSearch(row, col, 0, numRows, numCols, matrix, word, visited)) {
                // If the word is found, set found to true and break out of the loop
                found = true;
                break;
            }
        }
    }

    // Check if the word was found and output the result to the file
    if (found) {
        fout << "true";
    } else {
        fout << "false";
    }

    // Close output file
    fout.close();

    // Loop through and delete each element of the dynamically allocated arrays to free up memory
    for (int row = 0; row < numRows; row++) {
        delete[] matrix[row];
        delete[] visited[row];
    }
    delete[] matrix;
    delete[] visited;
    return 0;
}