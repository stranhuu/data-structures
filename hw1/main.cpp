#include <iostream>
#include <fstream>
#include <algorithm>
#include "ArgumentManager.h"

using namespace std;

int repeatedSum(string numStr) {
    // Calculate the repeated sum of the digits in the string
    int sum = 0;
    for (char c : numStr) {
        sum += c - '0';
    }
    if (sum > 9) {
        sum = repeatedSum(to_string(sum));
    }
    return sum;
}

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);

    // Open input and output files
    ifstream fin(am.get("input"));
    ofstream fout(am.get("output"));
    string input;

    while (getline(fin, input)) {
        // Read each line of input from the file, remove any spaces, and check if it is empty
        input.erase(remove(input.begin(), input.end(), ' '), input.end());
        if (input.empty()) {
            continue;
        }

        // Check if the input is valid and skip to the next line of input if it is not
        int hasCharSet = input.find(';');
        int posIdStr = input.find("id:");
        if (posIdStr == string::npos || hasCharSet == string::npos) {
            continue;
        }

        // Extract the character set and ID string from the input
        string charSet = input.substr(0, posIdStr);
        string idStr = input.substr(posIdStr + 3);

        string newIdStr = "";
        for (char c : idStr) {
            if (isalpha(c)) {
                // Replace each letter in the ID string with the corresponding substring from the character set
                int charPos = charSet.find(c);
                int semiPos = charSet.find(';', charPos);
                int length = semiPos - charPos - 2;
                newIdStr += charSet.substr(charPos + 2, length);
            }
            else {
                // Leave non-letter characters unchanged
                newIdStr += c;
            }
        }

        // Replace any '+' character in the decoded ID string with the repeated sum of the digits preceding it
        for (int i = 0; i < newIdStr.length(); i++) {
            if (newIdStr[i] == '+') {
                int sum = repeatedSum(newIdStr.substr(0, i));
                newIdStr[i] = char(sum + 48);
            }
        }

        // Write the translated and modified ID string to the output file
        fout << newIdStr << endl;
    }

    // Close input and output files
    fin.close();
    fout.close();

    return 0;
}