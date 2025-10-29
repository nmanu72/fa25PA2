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
        weightArr[(size)-1] = idx;
        upheap(size-1, weightArr);
    }

    int pop(int weightArr[]) {
        if (size > 0) {
            int popElement = weightArr[0];
            // Replace first element (root) with last element
            weightArr[0] = weightArr[size-1];
            // Decrement size of array
            size--;
            // Call downheap
            downheap(0, weightArr);
            return popElement;
        }
        // Replace root with last element, then call downheap()
        return -1; // placeholder
    }

    // Non std arrays passed by reference in c++
    void upheap(int pos, int weightArr[]) {
        // While parent is greater than child
        // (improper min heap structure)
        while(pos > 0 && weightArr[(pos-1)/2] > weightArr[pos]) {
            // Swap parent and child
            // Save parent value to temp
            int temp = weightArr[(pos-1)/2];
            // Set parent index equal to child value
            weightArr[(pos-1)/2] = weightArr[pos];
            // Set child index equal to parent value
            weightArr[pos] = temp;
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
               smallerChild =  weightArr[leftChild] < weightArr[rightChild] ? leftChild : rightChild;
            }
            // If smallerChild is still greater than parent, break.
            if (weightArr[smallerChild] >= weightArr[pos]) {
                break;
            }
            // Swap pos with smallerChild
            int temp = weightArr[pos];
            weightArr[pos] = weightArr[smallerChild];
            weightArr[smallerChild] = temp;
            // Set pos to smallerChild
            pos = smallerChild;
        }
    }
};

#endif