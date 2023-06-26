#include <iostream>
#include <string>

using namespace std;

const int NUMBERS_SIZE = 10;


int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}
void InsertionSort(int numbers[], int numbersSize);
void Quicksort_midpoint(int numbers[], int i, int k);
void Quicksort_medianOfThree(int numbers[], int i, int k);


void InsertionSort(int numbers[], int numbersSize){
    for(int i = 0; i < numbersSize; ++i){ // loop through all of the numbers
        for(int j = i; j < numbersSize; ++j){ // for each of the numbers, compare with sorted portion and swap if lower
            if(numbers[j] < numbers[i]){
                int temp = numbers[j];
                numbers[j] = numbers[i];
                numbers[i] = temp;
            }
        }
    }
}

void partition(int numbers[], int lowIndex, int highIndex){
    
}
void Quicksort_midpoint(int numbers[], int i, int k){
    if(i >= k){ //base case
        return;
    }
    int pivot = numbers[i + (k - i) / 2]; //pivot is the middle index
    int lowIndex = i;
    int highIndex = k;

    bool done = false;
    
    while(!done){ // loop until one or no elements left,
        //increment while the numbers are less than the pivot
        while(numbers[lowIndex] < pivot){
            ++lowIndex;
        }
        //decrement while numbers are more than the pivot
        while(numbers[highIndex] > pivot){
            --highIndex;
        }
        //partitioning is done so break 
        if(lowIndex >= highIndex){
            done = true;
            break;
        }
        else{
            //else swap low and high index 
            int temp = numbers[highIndex];
            numbers[highIndex] = numbers[lowIndex];
            numbers[lowIndex] = temp;

            ++lowIndex;
            --highIndex; 
        }
    }
    //recursively sort lower and higher partition
    Quicksort_midpoint(numbers,i,highIndex);
    Quicksort_midpoint(numbers,highIndex + 1, k);

}
//helper function to find median
int median(int a, int b, int c){
    if(a < b){
        if(b < c){
            return b;
        }
        else if(a < c){
            return c;
        }
        else{
            return a;
        }
    }
    else{
        if(a < c){
            return a;
        }
        else if(b < c){
            return c;
        }
        else{
            return b;
        }
    }
}

void Quicksort_medianOfThree(int numbers[], int i, int k){
    if(i >= k){ //base case, if array is sorted or none to sort
        return;
    }
    int pivot = median(numbers[i], numbers[i + ((k - i) / 2)], numbers[k]);
    int lowIndex = i;
    int highIndex = k;

    bool done = false;
    
    while(!done){ //loop until one or none elements left
        //increment while the numbers are less than the pivot
        while(numbers[lowIndex] < pivot){
            ++lowIndex;
        }
        //decrement while numbers are more than the pivot
        while(numbers[highIndex] > pivot){
            --highIndex;
        }
        //then partitioning is done so break 
        if(lowIndex >= highIndex){
            done = true;
            break;
        }
        else{
            //else swap low and high index 
            int temp = numbers[highIndex];
            numbers[highIndex] = numbers[lowIndex];
            numbers[lowIndex] = temp;

            ++lowIndex;
            --highIndex; 
        }
    }
    //recursively sort lower and higher partition
    Quicksort_medianOfThree(numbers,i,highIndex);
    Quicksort_medianOfThree(numbers,highIndex + 1, k);

}
