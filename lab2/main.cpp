#include <iostream>
#include <fstream>
#include "ArgumentManager.h"
#include "LinkedList.h"

using namespace std;

// A helper function to remove extra punctuation from a word
string removePunctuation(const string& word) {
    string result = "";
    for (const char& c : word) {
        if (isalpha(c) || c == '\'' || c == '-') {
            result += toupper(c);
        }
    }
    return result;
}

// A helper function to sort the linked list in descending order
void sortLinkedList(LinkedList& list) {
    for (int i = 0; i < list.GetSize() - 1; i++) {
        Node* curr = list.GetHead();
        for (int j = 0; j < list.GetSize() - i - 1; j++) {
            if (curr->count < curr->next->count ||
                (curr->count == curr->next->count && curr->data > curr->next->data)) {
                swap(curr->data, curr->next->data);
                swap(curr->count, curr->next->count);
            }
            curr = curr->next;
        }
    }
}

int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);

    //Open input and output files
    ifstream fin(am.get("input"));
    ofstream fout(am.get("output"));

    // Read in each word and add it to the linked list
    string word;
    LinkedList list;
    while (fin >> word) {
        word = removePunctuation(word);
        if (!word.empty()) {
            Node* curr = list.GetHead();
            bool found = false;
            while (curr != nullptr) {
                if (curr->data == word) {
                    curr->count++;
                    found = true;
                    break;
                }
                curr = curr->next;
            }
            if (!found) {
                list.AddAtHead(word);
            }
        }
    }
    fin.close();

    // Sort the linked list and print the results to the output file
    sortLinkedList(list);
    Node* curr = list.GetHead();
    while (curr != nullptr) {
        fout << curr->count << " " << curr->data << endl;
        curr = curr->next;
    }
    fout.close();

    return 0;
}
