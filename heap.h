//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // Increase size, insert idx to end index
        size++;
        data[size-1] = idx;
        // Call upheap function.
        upheap(size-1, weightArr);
    }

    int pop(int weightArr[]) {
        if (size > 0) {
            int popElement = data[0];
            // Replace first element (root) with last element
            data[0] = data[size-1];
            // Decrement size of array
            size--;
            // Call downheap function.
            downheap(0, weightArr);
            return popElement;
        }
        // Replace root with last element, then call downheap().
        return -1; // placeholder
    }

    // Non std arrays passed by reference in c++
    void upheap(int pos, int weightArr[]) {
        // While parent is greater than child
        // (improper min heap structure)
        while(pos > 0 && weightArr[data[(pos-1)/2]] > weightArr[data[pos]]) {
            // Swap parent and child
            // Save parent value to temp
            int temp = data[(pos-1)/2];
            // Set parent index equal to child value
            data[(pos-1)/2] = data[pos];
            // Set child index equal to parent value
            data[pos] = temp;
            // Set pos equal to parent index
            pos = (pos-1)/2;
        }
    }

    void downheap(int pos, int weightArr[]) {
        // While pos does not reach past size
        // And pos is greater than either of its children
        while (pos < size-1) {
            int leftChild = pos*2+1;
            int rightChild = pos*2+2;
            // If leftChild does not exist, exit loop
            if (leftChild >= size) {
                break;
            }
            // Set smallerChild to leftChild, unless rightChild exists and is smaller.
            int smallerChild = leftChild;
            if (rightChild < size) {
               smallerChild =  weightArr[data[leftChild]] < weightArr[data[rightChild]] ? leftChild : rightChild;
                // Makes sure that heap is consistent.
                // If both left and right child are the same weight, they are compared by indices.
                if (weightArr[data[leftChild]] == weightArr[data[rightChild]]) {
                    smallerChild = data[leftChild] < data[rightChild] ? leftChild : rightChild;
                }
            }
            // If smallerChild is still greater than parent, break.
            if (weightArr[data[smallerChild]] >= weightArr[pos]) {
                break;
            }
            // Swap pos with smallerChild
            int temp = data[pos];
            data[pos] = data[smallerChild];
            data[smallerChild] = temp;
            // Set pos to smallerChild
            pos = smallerChild;
        }
    }
};

#endif