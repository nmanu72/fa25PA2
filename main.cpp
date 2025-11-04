//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    MinHeap heap;

    // Pushing all leaf node indices to the heap.
    for (int i = 0; i < nextFree; ++i) {
        heap.push(i, weightArr);
    }

    int index = nextFree;

    while (heap.size > 1) {
        // Popping topmost (smallest) nodes from min heap.
        int node1 = heap.pop(weightArr);
        int node2 = heap.pop(weightArr);

        // Combining two popped values and adding them back to WeightArr
        weightArr[index] = weightArr[node1]+weightArr[node2];

        // Assigning smaller value to left child and larger to right child.
        // We know node1 is smaller since it was popped from min heap before node2.
        leftArr[index] = node1;
        rightArr[index] = node2;

        // Pushing index of combined value into heap.
        heap.push(index, weightArr);

        // Incrementing index.
        index++;
    }
    // Return the root node of the heap.
    return heap.pop(weightArr);
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.
    stack<pair<int, string>> codeStack;
    // Initial push (root)
    codeStack.push({root, ""});
    while (!codeStack.empty()) {
        // Update the index and the currentCode by saving data from past nodes then popping
        pair<int, string> topStack = codeStack.top();
        int index = topStack.first;
        string currCode = topStack.second;
        codeStack.pop();

        // If no child nodes exist (leaf).
        if (leftArr[index] == -1) {
            // Takes char at index, subtracts by 'a' to convert ASCII number
            // into valid array index (0-25) for codes.
            codes[charArr[index]-'a'] = currCode;
        }
        // If children exist push child indices into stack, add respective code
        // (0 or 1 depending on right or left path) to currCode.
        else {
            if (rightArr[index] != -1) {
                codeStack.push({rightArr[index], currCode + "1"});
            }
            codeStack.push({leftArr[index], currCode + "0"});
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}