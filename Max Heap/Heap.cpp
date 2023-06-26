#include <iostream>
#include <stdexcept>
#include "Heap.h"
#include "PrintJob.h"
using namespace std;

Heap::~Heap(){
    while(numItems > 0){ //reiterate till no items left
        //delete last item decrement  array size
        delete arr[numItems - 1]; 
        --numItems;
    }
}
 

void Heap::enqueue (PrintJob* itemToAdd){
    if(numItems >= MAX_HEAP_SIZE){ //edge case for adding beyond max heap
        // throw runtime_error("out of range");
    }
    else{
        // add item in the array and then call percolate up private helper to fix order of priority
        arr[numItems] = itemToAdd;
        percolateUp(numItems, arr);
        ++numItems;
    }
}   


void Heap::percolateUp(int nodeIndex, PrintJob* heapArray[]) { // zybooks code
    while (nodeIndex > 0) {
        int parentIndex = (nodeIndex - 1) / 2;
        if(heapArray[nodeIndex]->getPriority() <= heapArray[parentIndex]->getPriority()){ //edge case for when priority is correct
            return;
        }
        else{
            //else swap the two contents in the array and indices
        swap(heapArray[nodeIndex],heapArray[parentIndex]);
        nodeIndex = parentIndex;
        }
   }
}

PrintJob* Heap::highest() const{
    if(numItems > 0){ //if more than 0 items return the first
        return arr[0];
    }
    else{ //edge case
        return nullptr;
    }
}

void Heap::print(){
    //edge case for printing less than 0 items in array
    if(numItems <= 0){
        throw runtime_error("empty");
    }
    else{
    //print object's data fields
        cout << "Priority: " << highest()->getPriority() << ", "
            << "Job Number: " << highest()->getJobNumber() << ", "
            << "Number of Pages: " << highest()->getPages() << endl;
    }
}

void Heap::dequeue(){
    if(numItems < 1 ){ // edge case if less than 1 item
        // throw runtime_error("attempting to remove less than 1 item");
    }
    if(numItems == 1){// edge case if one item just remove
        arr[0] = nullptr;
        --numItems;
    }
    if(numItems > 1){ //more than one
        int lastIndex = numItems - 1; 
        swap(arr[0], arr[lastIndex]); 
        --numItems; 
        trickleDown(0); // trickle down to fix order of max heap afer swapping max and last index
    }
}

void Heap::trickleDown(int nodeIndex){ // zybooks code
    int childIndex = 2 * nodeIndex + 1;
    PrintJob* value = arr[nodeIndex];

    while (childIndex < numItems) {
        // Find the max among the node and all the node's children
        PrintJob* maxValue = value;
        int maxIndex = -1;
        for (int i = 0; i < 2 && i + childIndex < numItems; i++) {
            if (arr[i + childIndex] > maxValue) {
                maxValue = arr[i + childIndex];
                maxIndex = i + childIndex;
            }
        }
        //exit if already sorted
        if (maxValue == value) {
            return;
        }
        //else swap to maintain max heap property.
        else {
            swap (arr[nodeIndex],arr[maxIndex]);
            nodeIndex = maxIndex;
            childIndex = 2 * nodeIndex + 1;
        }
    }

}
